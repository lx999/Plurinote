#ifndef NOTEXTUALNOTE_H
#define NOTEXTUALNOTE_H

#include "notes/note.h"

/*! Classe NoTextualNote, classe fille de Note */
class NoTextualNote: public Note{

protected:
    QString filename;
    QString description; /**< Courte description de la Note */

public:
    //NoTextualNote(QUuid identifier = QUuid::createUuid()); /**< Constructeur */
    //NoTextualNote(QUuid identifier,QDateTime c);
    const QString& getDescription() const; /**< Accesseur de l'attribut description */
    void setDescription(const QString& d); /**< Méthode modifiant l'attribut description */
    const QString& getFilename() const;
    virtual void setFilename(const QString& f);
    virtual const QString getEveryText() const;
    virtual ~NoTextualNote(); /**< Desctructeur virtuel, la classe est à spécialiser */
};

#endif // NOTEXTUALNOTE_H
