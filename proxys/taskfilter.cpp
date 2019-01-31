#include "taskfilter.h"
#include <QSortFilterProxyModel>

TaskFilter::TaskFilter(const NotesManager& manager, QObject *parent) : NotesProxy(manager, parent){
    connect(&manager, SIGNAL(noteUpdated(NoteHolder)), this, SLOT(invalidate()));
    sort(0, Qt::DescendingOrder);
}

const Task& TaskFilter::getTask(const QModelIndex& index) const{
    return static_cast<const Task&>(getManager().getModelHolder().findByIndex(index).getLastVersion());
}

bool TaskFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{

    Q_UNUSED(sourceParent)
    if(!getManager().getModelHolder().hasIndex(sourceModel()->index(sourceRow, 0))) return true;
    const NoteHolder& note = getManager().getModelHolder().findByIndex(sourceModel()->index(sourceRow, 0));
    return note.getState() == 0 && note.getLastVersion().getType() == "Task";

}

QVariant TaskFilter::data(const QModelIndex &index, int role) const{
    if(role == Qt::DisplayRole){
        return QSortFilterProxyModel::data(index, role).toString() + " (" + getTask(mapToSource(index)).getExpired().toString("dd/MM/yyyy") + ")";
    }else if(role == Qt::DecorationRole){
        unsigned int priority = getTask(mapToSource(index)).getPriority();

        switch(priority){
            case 1:
                return QIcon(":/icons/priority-high");
            case 2:
                return QIcon(":/icons/priority-medium");
            case 3:
                return QIcon(":/icons/priority-low");
            default:
                return QSortFilterProxyModel::data(index, role);
        }
    }else if(role == Qt::ForegroundRole){
        QDateTime time = getTask(mapToSource(index)).getExpired();
        if(time.date() < QDate::currentDate()){
            return QVariant(QColor(Qt::red));
        }else{
            return QSortFilterProxyModel::data(index, role);
        }
    }else{
       return QSortFilterProxyModel::data(index, role);
    }
}

bool TaskFilter::lessThan(const QModelIndex & left, const QModelIndex & right) const {
    const Task& t1 = getTask(left);
    const Task& t2 = getTask(right);

    if(t1.getPriority() != t2.getPriority()) return t1.getPriority() > t2.getPriority();
    else return t1.getExpired() > t2.getExpired();
}

