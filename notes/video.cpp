#include "video.h"

const QString Video::type = QString("Video");

NoteInterface* Video::getUI() const{
    return new VideoInterface(*this);
}

const QMovie& Video::getVideo() const{
    return *videoFile;
}

void Video::setFilename(const QString& name){
    NoTextualNote::setFilename(name);
    videoFile->setFileName(filename);
}

const QString& Video::getType() const{
    return type;
}
