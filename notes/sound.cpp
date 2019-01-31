#include "sound.h"

const QString Sound::type = QString("Sound");

/*
Sound::Sound(QUuid identifier):NoTextualNote(identifier){}
Sound::Sound(QUuid identifier, const QString& filename):NoTextualNote(identifier),soundFile(new QSound(filename)),soundFileName(filename){}
Sound::Sound(QUuid identifier, QDateTime c,const QString& filename):NoTextualNote(identifier,c),soundFile(new QSound(filename)),soundFileName(filename){}
*/

NoteInterface* Sound::getUI() const{
    return new SoundInterface(*this);
}


const QSound& Sound::getSound() const{
    return *soundFile;
}
void Sound::setFilename(const QString& name){
    NoTextualNote::setFilename(name);
    soundFile = new QSound(filename);
}

const QString& Sound::getType() const{
    return type;
}
