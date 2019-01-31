#include "notes/noteholder.h"

void NoteHolder::update(const Note &newVersion){
    lastVersion = &newVersion;
}

void NoteHolder::setState(NoteState state){
    status = static_cast<int>(state);
}
