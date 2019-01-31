#include "versionsdockview.h"
#include <QDialogButtonBox>

VersionsDockView::VersionsDockView(Database * database, NoteFrameView * noteview, QWidget *parent) : QWidget(parent), currentNote(0), database(database), noteview(noteview)
{
    initUI();
}

void VersionsDockView::initUI(){
    layout = new QVBoxLayout(this);

    QHBoxLayout* btnsLayout = new QHBoxLayout;

    restoreButton = new QPushButton(QIcon(":/icons/restore"), "Rétablir");
    cleanButton = new QPushButton(QIcon(":/icons/clean"), "Nettoyer");
    btnsLayout->addWidget(restoreButton);
    btnsLayout->addWidget(cleanButton);

    model = new QStringListModel;

    versionList = new QListView;
    versionList->setModel(model);
    versionList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    versionList->setAlternatingRowColors(true);


    layout->addLayout(btnsLayout);
    layout->addWidget(versionList);

    cleanDialog = new QMessageBox(this);
    cleanDialog->setIcon(QMessageBox::Warning);
    cleanDialog->setText("Voulez-vous vraiment nettoyer cette note ?");
    cleanDialog->setInformativeText("Toutes les anciennes versions de la note seront effacés définitivement. Seule la version actuelle sera conservée.");
    cleanDialog->setModal(true);
    cleanDialog->setWindowModality(Qt::WindowModal);
    cleanDialog->addButton("Annuler", QMessageBox::RejectRole);
    cleanDialog->addButton("Nettoyer", QMessageBox::AcceptRole);

    restoreButton->setDisabled(true);
    cleanButton->setDisabled(true);

    connect(versionList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selectionChanged()));
    connect(restoreButton, SIGNAL(released()), this, SLOT(restore()));
    connect(cleanButton, SIGNAL(released()), cleanDialog, SLOT(exec()));
    connect(cleanDialog, SIGNAL(accepted()), this, SLOT(clean()));
    connect(database, SIGNAL(versionInserted(NoteHolder,int)), this, SLOT(versionInserted(NoteHolder,int)));
}

QString VersionsDockView::label(int version_nb, QDateTime datetime){
    return "Version " + QString::number(version_nb) + " (" + datetime.toString("dd MMMM à hh:mm") + ")";
}

void VersionsDockView::refresh(){
    restoreButton->setDisabled(!currentNote->isActive() || versionList->selectionModel()->selectedIndexes().empty());
    cleanButton->setDisabled(!currentNote->isActive() || versionsMapping.size() < 2);
}

void VersionsDockView::setCurrentNote(const NoteHolder * note){
    currentNote = note;
    QStringList list;

    if(note){

        QMap<QDateTime, int>* map = database->fetchVersionsList(*note);
        QList<QDateTime> dates = map->keys();

        int i = dates.size();
        for(QList<QDateTime>::const_iterator d = dates.constEnd()-1; d != dates.constBegin()-1; d--){
            list << label(i, *d);
            i--;
        }

        versionsMapping = map->values();
        delete map;
    }

    model->setStringList(list);
    refresh();
}

void VersionsDockView::noteStatusChanged(const NoteHolder& note){
    if(note == *currentNote){
        refresh();
    }
}

void VersionsDockView::restore(){
    if(versionList->selectionModel()->hasSelection()){
        int list_index = versionList->selectionModel()->currentIndex().row();
        int db_id = versionsMapping.at(versionsMapping.size() - list_index - 1);

        const Note& note = database->loadContent(db_id, currentNote->getLastVersion().getType());
        noteview->setNoteContent(note);
    }

}

void VersionsDockView::clean(){
    if(currentNote){
        int leaveId = versionsMapping.last();
        database->clean(*currentNote, leaveId);
        versionsMapping.clear();
        versionsMapping.append(leaveId);

        QStringList list;
        list.append(label(1, currentNote->getLastVersion().getEdited()));
        model->setStringList(list);

        refresh();
    }

}

void VersionsDockView::versionInserted(const NoteHolder& note, int db_id){
    if(currentNote && note == *currentNote){
        // Insertion de la nouvelle version dans l'historique

        versionsMapping.append(db_id);
        QStringList list = model->stringList();
        list.insert(0, label(list.size()+1, note.getLastVersion().getEdited()));

        model->setStringList(list);

        refresh();
    }
}

void VersionsDockView::selectionChanged(){
    refresh();
}
