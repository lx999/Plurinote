#ifndef NOTESTATEFILTER_H
#define NOTESTATEFILTER_H

#include "notesproxy.h"

class NoteStateFilter : public NotesProxy
{
    int status;

public:
    explicit NoteStateFilter(const NotesManager& manager, NoteState status, QObject *parent = 0) : NotesProxy(manager, parent), status(static_cast<int>(status)) {}
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // NOTESTATEFILTER_H
