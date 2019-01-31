#ifndef SOUND_H
#define SOUND_H

#include "notes/notextualnote.h"
#include <QSound>
#include "interfaces/content-editor/soundinterface.h"
class SoundInterface;

/*! Classe Sound, classe fille de NoTextualNote*/
class Sound: public NoTextualNote{
    QSound* soundFile;  /**< Fichier audio */
    static const QString type; /**< Attribut static qui correspond au type de Note */
public:

    Sound() : soundFile(new QSound(filename)){}

    const QSound& getSound() const; /**<  Accesseur de l'attribut soundFile */
    const QString& getType() const; /**< Méthode permettant d'obtenir le type de Note */
    void setFilename(const QString&);/**< Méthode permettant de modifier le fichier son */
    NoteInterface* getUI() const;  /**< Méthode permettant d'obtenir l'interface de la note son */
};

#endif // SOUND_H
