#ifndef NOTEIDENTIFIER_H
#define NOTEIDENTIFIER_H

#include <QUuid>
#include <QDateTime>

#include "notes/note.h"
#include "utils.h"

typedef enum {ACTIVE, ARCHIVED, DELETED} NoteState;// active=0, non_editable=1, sursis=2

/*! Classe NoteHolder, classe qui représente une note et toutes ses versions */
class NoteHolder
{
    const QUuid identifier; /**< Identifiant de la Note (identique pour toutes ses versions) */
    const QDateTime created; /**< Date de création de la première Note */
    const Note * lastVersion = nullptr; /**< Pointeur vers la dernière version de la Note */
    int status = 0; /**< Status de la note {ACTIVE, ARCHIVED, DELETED} */


public:
    NoteHolder() : identifier(QUuid::createUuid()){} /**< Contructeur de la Note */
    NoteHolder(QString uuid, QDateTime created, int status) : identifier(QUuid(uuid)), created(created), status(static_cast<NoteState>(status)){} /**< Contructeur 2 de la Note */

    const QUuid getId() const{ return identifier; } /**< Accesseur à l'attribut identifier  */
    const QDateTime getCreated() const { return created; } /**< Accesseur à l'attribut created (QDateTime)  */
    const Note& getLastVersion() const{ return *lastVersion; } /**< Accesseur à à la dernière version de la note  */
    int getState() const { return status; } /**< Accesseur au status de la note (dernière version)  */
    bool isActive() const { return status == NoteState::ACTIVE; } /**< Méthode permettant de savoir si la note est active (renvoye vrai si ACTIVE faux)*/
    bool isDeleted() const { return status == NoteState::DELETED; } /**< Méthode permettant de savoir si la note est supprimé (renvoye vrai si DELETED faux)*/
    void setState(NoteState state); /**< Méthode permettant de modifier le status d'une note  */

    void update(const Note& newVersion); /**< Méthode permettant de mettre à jour la dernière version pointé par la classe */

    bool operator==(const NoteHolder& id2) const { return identifier == id2.identifier; } /**< Rédéfinition de l'opérateur ==  */
    bool operator<(const NoteHolder& id2) const { return identifier < id2.identifier; } /**< Rédéfinition de l'opérateur <  */
    operator QString() const {

        return lastVersion ? lastVersion->getTitle() : "";
    }

};

#endif // NOTEIDENTIFIER_H
