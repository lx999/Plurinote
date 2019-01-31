#include "mainframe.h"
#include "notesmanager.h"
#include <QHBoxLayout>

void Mainframe::initUI(){

    sidebar = new Sidebar(data, this);
    noteView = new NoteFrameView(this);
    //CorbeilleView=new CorbeilleListView(cb,this);//pour corbeille

    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(sidebar);
    layout->addWidget(noteView);

    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    connect(sidebar, SIGNAL(noteSelected(const NoteHolder*)), noteView, SLOT(setNote(const NoteHolder*)));
}

Mainframe::Mainframe(NotesManager& nm,QWidget *parent): QWidget(parent), data(nm){
    initUI();
    show();
}
