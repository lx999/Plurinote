#include "createlinkdialog.h"
#include "interfaces/mainwindow.h"
#include <QDebug>

CreateLinkDialog::CreateLinkDialog(RelationsManager<NoteHolder>& relationsManager, ManageRelationsDialog& manageDialog, QWidget *parent) : QDialog(parent, Qt::Sheet), relationsManager(relationsManager), manageDialog(manageDialog)
{
    initUI();
    populate();

}


void CreateLinkDialog::initUI(){
    glblLayout = new QVBoxLayout;
    formLayout = new QFormLayout;
    relatedCombo = new QComboBox;
    relationCombo = new QComboBox;
    labelField = new QLineEdit;
    btnsLayout = new QDialogButtonBox;

    QPushButton* linkBtn = btnsLayout->addButton("Lier", QDialogButtonBox::AcceptRole);
    QPushButton* cancelBtn = btnsLayout->addButton("Annuler", QDialogButtonBox::RejectRole);
    QPushButton* manageBtn = btnsLayout->addButton("Gérer les relations", QDialogButtonBox::ActionRole);


    formLayout->addRow("Relation :", relationCombo);
    formLayout->addRow("Destination :", relatedCombo);
    formLayout->addRow("Label :", labelField);


    glblLayout->addWidget(new QLabel("Spécifiez les caractéristiques du lien à créer pour cette note."));
    glblLayout->addLayout(formLayout);
    glblLayout->addWidget(btnsLayout);

    connect(linkBtn, SIGNAL(released()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(released()), this, SLOT(reject()));
    connect(manageBtn, SIGNAL(released()), this, SLOT(openManage()));

    setLayout(glblLayout);
    setModal(true);
}

void CreateLinkDialog::populate(){

    relatedCombo->setModel(&notesManager.getModelHolder().getModel());
    relationCombo->setModel(relationsManager.getModel());
}

void CreateLinkDialog::setCurrentNote(const NoteHolder &n){
    currentNote = &n;
}

void CreateLinkDialog::accept(){

        Relationship<NoteHolder>& rel = relationsManager.getRelation(relationCombo->currentText());

        if(rel.getName() == REFERENCE){
            QMessageBox::warning(this, "Liaison impossible",
                                           "Les liaisons de type Référence ne peuvent être crées manuellement.",
                                           QMessageBox::Ok,
                                           QMessageBox::Ok);
        }else{
            int idx = relatedCombo->currentIndex();
            QModelIndex qidx = relatedCombo->model()->index(idx, 0);
            const NoteHolder& nh = notesManager.getModelHolder().findByIndex(qidx);

            if(relationsManager.areLinked(rel, *currentNote, nh)){
                QMessageBox::warning(this, "Liaison impossible",
                                               "Les notes sélectionnés sont déjà liés par cette relation.",
                                               QMessageBox::Ok,
                                               QMessageBox::Ok);
            }else{
                relationsManager.link(rel, *currentNote, nh, labelField->text());
                QDialog::accept();

                emit linkCreated(rel.getName(), *currentNote, nh, labelField->text());
            }
        }

}

void CreateLinkDialog::openManage(){
    ManageRelationsDialog* mrd = new ManageRelationsDialog(relationsManager, this);
    mrd->show();
}
