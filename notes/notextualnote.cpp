#include "notextualnote.h"

/*NoTextualNote::NoTextualNote(QUuid identifier):Note(identifier){}

NoTextualNote::NoTextualNote(QUuid identifier, QDateTime c):Note(identifier,c){}*/
const QString& NoTextualNote::getDescription() const{
    return description;
}

void NoTextualNote::setDescription(const QString& d){
    description=d;
    setEdited();
}

const QString& NoTextualNote::getFilename() const{
    return filename;
}

void NoTextualNote::setFilename(const QString& n){
    filename=n;
    setEdited();
}

const QString NoTextualNote::getEveryText() const{
    return Note::getEveryText() + " " + description;
}


NoTextualNote::~NoTextualNote(){}
