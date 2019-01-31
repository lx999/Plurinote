#ifndef NOTE_H
#define NOTE_H

#include "interfaces/content-editor/noteinterface.h"
#include <QString>
#include <QDateTime>
#include "utils.h"
#include <QStandardItem>

class NoteInterface;

/*! Classe Note, classe mère  */
class Note {
    //NoteHolder * const holder; /**< identifiant unique qui caractérise chaque objet Note, unique pour chaque objet Note  */
    QString title; /**< titre de la Note  */
    QDateTime edited = QDateTime::currentDateTime(); /**< date de dernière mise à jour de la Note  */
    static const QString type; /**< Attribut static qui correspond au type de Note */

public:
    //NoteHolder& getHolder() const; /**< Accesseur de l'attribut identifier */
    const QString& getTitle() const; /**< Accesseur de l'attribut title */
    const QDateTime getEdited() const; /**< Accesseur de l'attribut edited */

    void setTitle(const QString& t); /**< Méthode modifiant l'attribut title */
    //sert à restore
    void setCreated(QDateTime c);  /**< Méthode modifiant l'attribut created */
    void setEdited(QDateTime e); /**< Méthode modifiant l'attribut edited */

    virtual NoteInterface* getUI() const = 0;
    //bool operator==(const Note &other) const{ return holder == other.holder;} /**< Opérateur d'égalité (basé sur l'identifiant de la Note) */
    operator QString() const { return title; }
    // a voir si on peut la mettre en privée
    // a mettre dans la méthode dès que l'on change une valeur d'attribut (sauf pour l'état de la note)
    void setEdited(); /**< Méthode modifiant l'attribut edited */

    void load(const Note& n);

    virtual const QString& getType() const; /**< Méthode permettant d'obtenir le type de Note */

    virtual const QString getEveryText() const;
};

#endif // NOTE_H
