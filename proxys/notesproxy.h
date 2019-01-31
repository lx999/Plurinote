#ifndef NOTESPROXY_H
#define NOTESPROXY_H

#include "notes/noteholder.h"
#include "notesmanager.h"
#include <QSortFilterProxyModel>


class NotesProxy : public QSortFilterProxyModel
{

    Q_OBJECT
    const NotesManager& manager;

public:
    explicit NotesProxy(const NotesManager& manager, QObject *parent = 0);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    const NotesManager& getManager() const { return manager; }


signals:

public slots:
    void noteStatusChanged(const NoteHolder&);
};

#endif // NOTESPROXYFILTER_H
