#include "image.h"

const QString Image::type = QString("Image");

const QImage& Image::getImage() const{
    return image;
}

NoteInterface* Image::getUI() const{
    return new ImageInterface(*this);
}

const QString& Image::getType() const{
    return type;
}


