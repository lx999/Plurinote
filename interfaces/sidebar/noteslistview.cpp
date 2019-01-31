#include "noteslistview.h"

NotesListView::NotesListView(NotesProxy* filter, QWidget *parent) : QListView(parent), filter(filter)
{
    filter->setParent(this);
    setModel(filter);
    //setStyleSheet("background: #fcfcfc; border:0;");
    clearSelection();

}

void NotesListView::selectionChanged(const QItemSelection& cur, const QItemSelection& prev){
    Q_UNUSED(prev);

    if(cur.size()){
        emit noteSelected(&(filter->getManager().getModelHolder().findByIndex(filter->mapSelectionToSource(cur).indexes().first())));
    }
}
