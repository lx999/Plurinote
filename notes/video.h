#ifndef VIDEO_H
#define VIDEO_H

#include "notes/notextualnote.h"
#include <QVideoWidget>
#include <QMovie>
#include "interfaces/content-editor/videointerface.h"


class VideoInterface;

/*! Classe Video, classe fille de NoTextualNote*/
class Video: public NoTextualNote{
    QMovie * videoFile; /**< File vidéo */
    static const QString type; /**< Attribut static qui correspond au type de Note */

public:
    Video() : videoFile(new QMovie){}

    NoteInterface* getUI() const;  /**< Méthode virtuelle renvoyant l'interface de la Video */
    const QMovie& getVideo() const; /**< Accesseur de l'attribut videoFile */
    void setFilename(const QString&); /**< Méthode permettant de changer la vidéo de la Note */
    const QString& getType() const; /**< Méthode permettant d'obtenir le type de Note */
};

#endif // VIDEO_H
