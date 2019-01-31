#ifndef IMAGE_H
#define IMAGE_H

#include <QFile>
#include <QImage>
#include "notextualnote.h"
#include "interfaces/content-editor/imageinterface.h"

class ImageInterface;

/*! Classe Image, classe fille de NoTextualNote */
class Image: public NoTextualNote {
    QImage image; /**< Fichier image */
    static const QString type; /**< Attribut static qui correspond au type de Note */
public:
    const QImage& getImage() const; /**< Accesseur de l'attribut image  */
    NoteInterface* getUI() const; /**< Méthode virtuelle renvoyant l'interface de Image */
    //void setFilename(const QString&);
    const QString& getType() const; /**< Méthode permettant d'obtenir le type de Note */
};

#endif // IMAGE_H
