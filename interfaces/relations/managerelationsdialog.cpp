#include "managerelationsdialog.h"
#include "relations/bidirectionalrelationship.h"
#include "notes/noteholder.h"
#include <QLabel>
#include <QMessageBox>
#include "interfaces/mainwindow.h"

ManageRelationsDialog::ManageRelationsDialog(RelationsManager<NoteHolder>& relationsManager, QWidget *parent) : QDialog(parent), manager(relationsManager)
{
    initUI();

    connect(add_btn, SIGNAL(released()), this, SLOT(addRelation()));
    connect(del_btn, SIGNAL(released()), this, SLOT(requestDeleteRelation()));
    connect(listview->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged(QItemSelection,QItemSelection)));
}

void ManageRelationsDialog::initUI(){
    layout = new QGridLayout(this);
    setWindowTitle("Gérer les relations");

    listview = new QListView;
    listview->setModel(manager.getModel());

    add_btn = new QPushButton("Ajouter");
    del_btn = new QPushButton("Supprimer");
    bi_cbx = new QCheckBox("Bidirectionelle");

    relname_ipt = new QLineEdit;

    QVBoxLayout* groupBoxLayout = new QVBoxLayout;
    insertGroup = new QGroupBox("Nouvelle relation");
    groupBoxLayout->addWidget(new QLabel("Nom de la relation"));
    groupBoxLayout->addWidget(relname_ipt);
    groupBoxLayout->addWidget(bi_cbx);

    groupBoxLayout->addWidget(add_btn);
    insertGroup->setLayout(groupBoxLayout);

    dialog_btns_box = new QDialogButtonBox;

    layout->addWidget(listview, 0, 0);
    layout->addWidget(del_btn, 1, 0);
    layout->addWidget(insertGroup, 0, 1, 2, 1);
    layout->addWidget(dialog_btns_box, 2, 0, 1, 2);

    QPushButton * done_btn = dialog_btns_box->addButton("Terminer", QDialogButtonBox::AcceptRole);

    connect(done_btn, SIGNAL(released()), this, SLOT(accept()));

    listview->setMaximumWidth(220);
    insertGroup->setMinimumWidth(190);
    setMaximumHeight(220);

    setModal(true);
    setWindowModality(Qt::WindowModal);



}

void ManageRelationsDialog::addRelation(){
    if(relname_ipt->text().size() > 0){
        QString name = relname_ipt->text();

        if(manager.getRelationsName().contains(name, Qt::CaseInsensitive)){
            QMessageBox* mbox = new QMessageBox(QMessageBox::Critical, "Cette relation existe déjà", "Cette relation existe déjà", QMessageBox::NoButton, this);
            mbox->setInformativeText("Veuillez choisir un autre nom car une autre relation utilise déjà ce nom.");
            mbox->setWindowModality(Qt::WindowModal);
            mbox->exec();
        }else{
            manager.createRelation(name, bi_cbx->isChecked());
            relname_ipt->clear();
        }
    }
}

void ManageRelationsDialog::requestDeleteRelation(){
    QModelIndexList selection = listview->selectionModel()->selectedIndexes();
    if(selection.size()){
        QString name = listview->model()->data(selection.first()).toString();
        rel_to_delete = &manager.getRelation(name);
        int count = rel_to_delete->countAssociations();

        if(count){
            QMessageBox* warning = new QMessageBox(this);
            warning->setModal(true);
            warning->setWindowModality(Qt::WindowModal);
            warning->setIcon(QMessageBox::Warning);
            warning->setText("La relation « " + name + " » est utilisée. Voulez-vous vraiment la supprimer ?");
            warning->setInformativeText("Cette relation est utilisée par " + QString::number(count) + " association" + (count > 1 ? "s" : "") + " de notes.");
            warning->addButton("Supprimer quand même", QMessageBox::DestructiveRole);
            warning->addButton("Annuler", QMessageBox::RejectRole);
            if(!warning->exec()){
                deleteRelation();
            }
        }else{
            deleteRelation();
        }
    }
}

void ManageRelationsDialog::deleteRelation(){
    manager.deleteRelation(*rel_to_delete);
    rel_to_delete = nullptr;
}

void ManageRelationsDialog::selectionChanged(QItemSelection cur,QItemSelection prev){
    Q_UNUSED(prev);

    if(!cur.size() || cur.indexes().first().data().toString() == REFERENCE){
        del_btn->setDisabled(true);
    }else{
        del_btn->setDisabled(false);
    }
}
