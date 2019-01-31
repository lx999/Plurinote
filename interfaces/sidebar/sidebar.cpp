#include "sidebar.h"
#include "proxys/notestatefilter.h"
#include "proxys/taskfilter.h"

Sidebar::Sidebar(NotesManager& nm, QWidget *parent) : QWidget(parent), nm(nm)
{
    initUI();
    QObject::connect(stdListview, SIGNAL(noteSelected(const NoteHolder*)), this, SLOT(selectActiveNote(const NoteHolder*)));
    QObject::connect(tskListview, SIGNAL(noteSelected(const NoteHolder*)), this, SLOT(selectActiveNote(const NoteHolder*)));
    QObject::connect(binListview, SIGNAL(noteSelected(const NoteHolder*)), this, SLOT(selectDeletedNote(const NoteHolder*)));
    QObject::connect(acvListview, SIGNAL(noteSelected(const NoteHolder*)), this, SLOT(selectDeletedNote(const NoteHolder*)));
    QObject::connect(deleteBtn, SIGNAL(released()), this, SLOT(deleteNote()));
    QObject::connect(restoreBtn, SIGNAL(released()), this, SLOT(restoreNote()));
}

void Sidebar::initUI(){

    layout = new QVBoxLayout(this);

    activeTabs = new QTabWidget();
    inactiveTabs = new QTabWidget();

    stdListview = new NotesListView(new NoteStateFilter(nm, ACTIVE), this);
    binListview = new NotesListView(new NoteStateFilter(nm, DELETED), this);
    acvListview = new NotesListView(new NoteStateFilter(nm, ARCHIVED), this);
    tskListview = new NotesListView(new TaskFilter(nm));

    activeTabs->addTab(stdListview, "Toutes");
    activeTabs->addTab(tskListview, "Tâches");

    inactiveTabs->addTab(binListview, "Corbeille");
    inactiveTabs->addTab(acvListview, "Archive");

    stdListview->useBigIcons();

    inactiveTabs->setMaximumHeight(120);

    deleteBtn = new QPushButton(QIcon(":/icons/corbeille"), "Supprimer");
    restoreBtn = new QPushButton(QIcon(":/icons/restore"), "Restaurer");

    deleteBtn->setDisabled(true);
    restoreBtn->setVisible(false);

    // Barre "nouveau"
    btnsLayout = new QHBoxLayout(this);
    buttons = new QPushButton*[5];

    buttons[0] = new QPushButton(QIcon(":/icons/article"),"");
    buttons[1] = new QPushButton(QIcon(":/icons/task"),"");
    buttons[2] = new QPushButton(QIcon(":/icons/image"),"");
    buttons[3] = new QPushButton(QIcon(":/icons/sound"),"");
    buttons[4] = new QPushButton(QIcon(":/icons/video"),"");

    QObject::connect(buttons[0], SIGNAL(pressed()), &nm, SLOT(createArticle()));
    QObject::connect(buttons[1], SIGNAL(pressed()), &nm, SLOT(createTask()));
    QObject::connect(buttons[2], SIGNAL(pressed()), &nm, SLOT(createImage()));
    QObject::connect(buttons[3], SIGNAL(pressed()), &nm, SLOT(createSound()));
    QObject::connect(buttons[4], SIGNAL(pressed()), &nm, SLOT(createVideo()));

    for(int i = 0; i < 5; i++){
        buttons[i]->setMaximumSize(50, 50);
        buttons[i]->setMinimumSize(50,50);
        buttons[i]->setIconSize(QSize(30, 30));
        buttons[i]->setStyleSheet("QPushButton{background-color: #B9E2F0; border-style: outset; border-radius: 15px; } QPushButton:hover{ background-color:#A2D1E0; } QPushButton:pressed{ background-color:#88BFD1; }");
        btnsLayout->addWidget(buttons[i]);
    }

    QFrame* btnsFrame = new QFrame;
    btnsFrame->setLayout(btnsLayout);

    layout->addWidget(btnsFrame);
    layout->addWidget(activeTabs);
    layout->addWidget(inactiveTabs);
    layout->addWidget(deleteBtn);
    layout->addWidget(restoreBtn);

    layout->setMargin(0);
    this->setLayout(layout);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(41, 128, 185));
    setAutoFillBackground(true);
    setPalette(pal);

    setMaximumWidth(300);

}

void Sidebar::selectNote(const NoteHolder* selectedNote){
    this->selectedNote = selectedNote;

    if(selectedNote){
        deleteBtn->setDisabled(false);
        deleteBtn->setVisible(selectedNote->isActive());
        restoreBtn->setVisible(!selectedNote->isActive());
    }else{
        deleteBtn->setDisabled(true);
        deleteBtn->setVisible(true);
        restoreBtn->setVisible(false);
    }

    emit noteSelected(selectedNote);
}

void Sidebar::selectActiveNote(const NoteHolder* selectedNote){
    selectNote(selectedNote);
    binListview->clearSelection();
}

void Sidebar::selectDeletedNote(const NoteHolder* selectedNote){
    selectNote(selectedNote);
    stdListview->clearSelection();
    tskListview->clearSelection();
}

void Sidebar::deleteNote(){
    if(selectedNote){
        emit noteStatusChangeRequested(*selectedNote, DELETED);
    }
}

void Sidebar::restoreNote(){
    if(selectedNote){
        emit noteStatusChangeRequested(*selectedNote, ACTIVE);
    }
}

