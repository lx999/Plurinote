#ifndef TASK_H
#define TASK_H


#include "notes/note.h"
#include "interfaces/content-editor/taskinterface.h"

class TaskInterface;
typedef enum {en_attente, en_cours,terminee} Status;// en_attente=0, en_cours=1, terminee=2

/*! Classe Task, classe fille de Note*/
class Task: public Note {
    QString actionToBeDone; /**< Action à réaliser pour la Tâche */
    Status status;  /**< Status de la tâche {en_attente, en_cours,terminee} */
    unsigned int priority = 2;  /**< Priorité de la tâche allant de 1:(priorité forte) à 3 (priorité faible) */
    QDateTime expired = QDateTime::currentDateTime(); /**< Date de fin d'une Tâche */
    static const QString type; /**< Attribut statique donnant le type de Note (dérivée) */

public:
    const QString& getActionToBeDone() const; /**< Accesseur de l'attribut l'action à réaliser  */
    QString getStatus() const; /**< Accesseur de l'attribut status  */
    unsigned int getStatusInt() const; /**< Accesseur 2 l'attribut status  */
    Status getStatus_re() const; /**< Accesseur 4 de l'attribut du status  */
    unsigned int getPriority() const; /**< Accesseur de l'attribut priorité */
    const QDateTime& getExpired() const; /**< Accesseur de l'attribut  date de fin */

    void setActionToBeDone(const QString& a); /**< Méthode modifiant l'attribut actionToBeDone  */
    void setPriority(unsigned int p); /**< Méthode modifiant l'attribut de priority  */
    void setStatus(int s); /**< Méthode modifiant l'attribut status  */
    void setExpired(const QDateTime exp); /**< Méthode modifiant l'attribut expired */

    NoteInterface* getUI() const;   /**< Méthode virtuelle renvoyant l'interface de la Tâche */


    const QString& getType() const; /**< Méthode renvoyant le type de Note (dérivée) */
    virtual const QString getEveryText() const;
};

#endif // TASK_H
