#ifndef MEMENTO_H
#define MEMENTO_H
#include "notes/note.h"
#include "relations/association.h"
#include "notes/noteholder.h"
#include <vector>
#include <QString>

/*! Classe Memento, classe mère abstraite de tous les memento de l'application*/
class Memento{
public:
    Memento(){}
    virtual ~Memento() {}
};



/*! Classe MementoRelation, enregistre les éléments nécessaires à la reconstruction d'une relation*/
class MementoRelation: public Memento{
    QString nameLabel;
    QString nameRelation;
    const NoteHolder& note;
    const NoteHolder& note1;


public:
    MementoRelation(const QString& nameR,const NoteHolder& n, const NoteHolder& n1,const QString& nameL):nameLabel(nameL),nameRelation(nameR),note(n),note1(n1){}
    const QString& getNameRelation()const {return nameRelation;}
    const QString& getNameLabel() const {return nameLabel;}
    const NoteHolder& getNote1() const{return note1;}
    const NoteHolder& getNote() const {return note;}



};


/*! Classe MementoNoteState, enregistre les éléments à la recréation d'une Note*/
class MementoNoteState: public Memento{
    const NoteHolder& note;
    NoteState oldState;
    NoteState newState;



public:
    MementoNoteState(const NoteHolder& n,NoteState oldS, NoteState newS): note(n),oldState(oldS),newState(newS){}
    const NoteHolder& getNote()const {return note;}
    const NoteState& getOldState()const {return oldState;}
    const NoteState& getNewState()const {return newState;}

};



/*! Classe MementoCaretaker, classe managère qui gère le controle Z/Y (undo/redo)*/
class MementoCaretaker: public QObject{
   Q_OBJECT
   std::vector<Memento*> m_vecMemento;  /**< Table pour le controle Z: annuler  */
   std::vector<Memento*> m_vecMementoInverse;  /**< Table  pour le controle Y: rétablir  */
   bool stopPropagation;   /**< Attribut permettant l'arrêt d'une boucle sans fin entre les signaux interface/memento  */
   void save(Memento* memento); /**< Méthode permettant de créer une mémento */
   static MementoCaretaker* instance;  /**< Design pattern singleton */
   MementoCaretaker& operator=(const MementoCaretaker&); /**< Empêche la création d'un MementoCaretaker par affection */
   MementoCaretaker(const MementoCaretaker&); /**< Empêche la création d'un MementoCaretaker par recopie */
   ~MementoCaretaker() {
       for (unsigned int i=0; i < m_vecMemento.size(); i++)
           delete m_vecMemento[i];
       for (unsigned int i=0; i < m_vecMementoInverse.size(); i++)
           delete m_vecMementoInverse[i];
   }
public:
    MementoCaretaker() : stopPropagation(false){}
    static MementoCaretaker& getInstance();
    static void freeInstance();

public slots:
    void undo();
    void redo();

    void saveMementoRelation(QString nameR,const NoteHolder& n, const NoteHolder& n1,QString nameL) {

            save(new MementoRelation(nameR,n,n1,nameL)); std::cout<<"Enregistrement ok Relation memento"<<std::endl;

        }

    void saveMementoState(const NoteHolder& n, NoteState oldState) {
        if(!stopPropagation){
            save(new MementoNoteState(n,oldState, static_cast<NoteState>(n.getState()))); std::cout<<"Enregistrement ok State memento"<<std::endl;
        }else stopPropagation = false;
    }


signals:
    void changeNoteState(const NoteHolder& n, NoteState nstate); /**< Signal permettant de mettre à jour les interfaces pour les ListNotesView */
    void DeleteRelation(const QString& nameRelation,const NoteHolder& note,const NoteHolder& note1); /**< Signal permettant de mettre à jour les interfaces pour la supression d'une relation */
    void CreateRelation(const QString& nameRelation,const NoteHolder& note,const NoteHolder& note1,const QString& nameLabel); /**< Signal permettant de mettre à jour les interfaces pour la création d'une relation */

};

#endif // MEMENTO_H
