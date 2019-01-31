#include "notestatefilter.h"


bool NoteStateFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const{

    Q_UNUSED(sourceParent)
    if(!getManager().getModelHolder().hasIndex(sourceModel()->index(sourceRow, 0))) return true;
    const NoteHolder& note = getManager().getModelHolder().findByIndex(sourceModel()->index(sourceRow, 0));
    return note.getState() == status;

}
