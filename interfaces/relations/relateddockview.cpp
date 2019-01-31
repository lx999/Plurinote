#include "relateddockview.h"
#include "interfaces/mainwindow.h"
#include <QDebug>

RelatedDockView::RelatedDockView(RelationsManager<NoteHolder>& relationsManager, MementoCaretaker &mement, QWidget *parent) : QWidget(parent), relationsManager(relationsManager), memento(mement)
{
    initUI();
    setSelectedNote(nullptr);
}

void RelatedDockView::initUI(){
    layout = new QVBoxLayout;

    linkButton = new QPushButton("Lier à...");
    linkButton->setAutoDefault(true);

    manageDialog = new ManageRelationsDialog(relationsManager, this);
    createDialog = new CreateLinkDialog(relationsManager, *manageDialog, this);

    connect(linkButton, SIGNAL(released()), createDialog, SLOT(open()));
    connect(createDialog, SIGNAL(accepted()), this, SLOT(refresh()));
    connect(createDialog, SIGNAL(linkCreated(QString,NoteHolder,NoteHolder,QString)), this, SIGNAL(linkCreated(QString,NoteHolder,NoteHolder,QString)));
    connect(relationsManager.getProxy(), SIGNAL(invalidate()), this, SLOT(refresh()));

    childrenView = new QTreeView;
    parentsView = new QTreeView;

    childrenView->setHeaderHidden(true);
    parentsView->setHeaderHidden(true);
    parentsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    childrenView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    childrenView->installEventFilter(this);
    parentsView->installEventFilter(this);

    childrenView->setModel(&childrenModel);
    parentsView->setModel(&parentsModel);

    layout->addWidget(linkButton);
    layout->addWidget(new QLabel("Descendants"));
    layout->addWidget(childrenView);
    layout->addWidget(new QLabel("Ascendants"));
    layout->addWidget(parentsView);

    deleteConfirm = new QMessageBox(this);
    deleteConfirm->setIcon(QMessageBox::Warning);
    deleteConfirm->setModal(true);
    deleteConfirm->setWindowModality(Qt::WindowModal);
    deleteConfirm->addButton("Supprimer", QMessageBox::DestructiveRole);
    deleteConfirm->addButton("Annuler", QMessageBox::RejectRole);
    deleteConfirm->setText("Souhaitez-vous supprimer cette relation ?");

    setMinimumSize(250, 0);
    setLayout(layout);
}


void RelatedDockView::setSelectedNote(const NoteHolder* n){
    selectedNote = n;

    if(n != nullptr){
        createDialog->setCurrentNote(*n);
    }

    refresh();

}

void RelatedDockView::refresh(){
    if(selectedNote == nullptr){
        childrenModel.clear();
        parentsModel.clear();
        linkButton->setDisabled(true);
    }else{
        linkButton->setDisabled(!selectedNote->isActive());
        relationsManager.fillTree(&childrenModel, &childrenIndexMap, *selectedNote, RelationsManager<NoteHolder>::CHILD);
        relationsManager.fillTree(&parentsModel, &parentsIndexMap, *selectedNote, RelationsManager<NoteHolder>::PARENT);
        childrenView->expandToDepth(1);
        parentsView->expandToDepth(1);
    }
}

bool RelatedDockView::eventFilter(QObject *object, QEvent *event){
    if(event->type() == QEvent::KeyPress && (object == parentsView || object == childrenView)){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Delete || keyEvent->key() == Qt::Key_Backspace){
            bool parents = (object == parentsView);

            QModelIndex idx = (parents ? parentsView->currentIndex() : childrenView->currentIndex());
            const Association<NoteHolder>* assoc = (parents ? parentsIndexMap.value(idx) : childrenIndexMap.value(idx));
            if(assoc){

                if(assoc->getRelation().getName() != REFERENCE){
                    deleteConfirm->setInformativeText("Relation entre " + assoc->getRelatedFrom() + " et " + assoc->getRelatedTo() + " de type " + assoc->getRelation().getName());
                    int code = deleteConfirm->exec();
                    if(code == 0){
                        Relationship<NoteHolder>& rel = assoc->getRelation();
                        const NoteHolder& e1 = assoc->getRelatedFrom();
                        const NoteHolder& e2 = assoc->getRelatedTo();
                        relationsManager.unlink(rel, e1, e2);
                        refresh();

                        emit linkDestroyed(rel.getName(), e1, e2,rel.getDescription());
                    }

                }else{
                    QMessageBox::warning(this, "Supression impossible",
                                                   "Pour supprimer une référence, retirez simplement la mention \ref du texte de la note.",
                                                   QMessageBox::Ok,
                                                   QMessageBox::Ok);
                }
            }

            return true;
        }
    }
    return false;
}

void RelatedDockView::noteStatusChanged(const NoteHolder& note){
    if(selectedNote && note == *selectedNote){
        linkButton->setDisabled(!note.isActive());
    }
}


