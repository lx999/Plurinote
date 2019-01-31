#ifndef TASKFILTER_H
#define TASKFILTER_H

#include "notesproxy.h"


class TaskFilter : public NotesProxy
{
private:
    const Task& getTask(const QModelIndex& index) const;

public:
    TaskFilter(const NotesManager& manager, QObject *parent = 0);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    bool lessThan(const QModelIndex & left, const QModelIndex & right) const;
};

#endif // TASKFILTER_H
