#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
#include "interfaces/sidebar/sidebar.h"
#include "notesmanager.h"
#include "interfaces/editor/noteframeview.h"

class Mainframe : public QWidget
{
    Q_OBJECT

    NotesManager& data;

    Sidebar* sidebar;
    NoteFrameView* noteView;

    void initUI();
public:

    explicit Mainframe(NotesManager& nm,QWidget *parent = 0);
    Sidebar const * getSidebar() const{ return sidebar; }
    NoteFrameView * getNoteView() { return noteView; }


signals:
public slots:

};

#endif // MAINFRAME_H
