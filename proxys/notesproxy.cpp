#include "notesproxy.h"

NotesProxy::NotesProxy(const NotesManager& manager, QObject *parent) : QSortFilterProxyModel(parent), manager(manager){
    setSourceModel(&manager.getModelHolder().getModel());

    setDynamicSortFilter(false);
    QObject::connect(&manager, SIGNAL(noteStatusChanged(NoteHolder, NoteState)), this, SLOT(noteStatusChanged(NoteHolder)));
    QObject::connect(&manager, SIGNAL(noteCreated(NoteHolder)), this, SLOT(noteStatusChanged(NoteHolder)));

}


void NotesProxy::noteStatusChanged(const NoteHolder &){
    invalidate();
}

QVariant NotesProxy::data(const QModelIndex &index, int role) const{
    return QSortFilterProxyModel::data(index, role);
}
