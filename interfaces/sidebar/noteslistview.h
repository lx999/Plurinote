#ifndef NOTESLISTVIEW_H
#define NOTESLISTVIEW_H

#include <QWidget>
#include <QListView>
#include "notesmanager.h"
#include "notes/noteholder.h"
#include "proxys/notesproxy.h"

class NotesListView : public QListView
{
    NotesProxy* filter;

    Q_OBJECT
public:
    explicit NotesListView(NotesProxy* proxy, QWidget *parent = 0);
    void useBigIcons(){ setIconSize(QSize(32, 32)); }

signals:
    void noteSelected(const NoteHolder*);
public slots:
    void selectionChanged(const QItemSelection&, const QItemSelection&);
};

#endif // NOTESLISTVIEW_H
