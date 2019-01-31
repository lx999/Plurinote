#include "note.h"

const QString Note::type = QString("Note");



const QString& Note::getTitle() const{
    return title;
}

const QDateTime Note::getEdited() const{
    return edited;
}

void Note::setTitle(const QString& t){
    title=t;
    setEdited();
}

void Note::setEdited(){
    edited=QDateTime::currentDateTime();
}


void Note::setEdited(QDateTime e){
    edited=e;
}

const QString& Note::getType() const{
    return type;
}

const QString Note::getEveryText() const{
    return title;
}

/*
Note::Note(NoteHolder holder, QDateTime c):holder(holder),created(c),edited(QDateTime::currentDateTime()),state(active){}*/
