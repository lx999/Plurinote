#ifndef RELATION_H
#define RELATION_H

#include <QString>
#include <QVector>
#include <QList>
#include "relationsmanager.h"
#include "association.h"

template <typename> class Association;

template<typename T>
class Relationship
{

protected:
    QString title;
    QString description;

    QVector<Association<T>*> associations;
    Relationship(const QString& title) : title(title){}

private:
    template<typename> friend class RelationsManager;
    template<typename> friend class QVector;

    Relationship(){}


    virtual const Association<T>* getConstAssociation(const T& ref1, const T& ref2) const;
    virtual Association<T>* getAssociation(const T& ref1, const T& ref2);
    virtual void associate(const T& ref1, const T& ref2, const QString& label);
    virtual void dissociate(const T& ref1, const T& ref2);
    bool areAssociated(const T& ref1, const T& ref2) const;

public:
    const QString& getName() const { return title; }
    const QString& getDescription() const { return description; }
    int countAssociations() const;

    virtual QVector<const Association<T>*>* getChildren(const T& ref) const;
    virtual QVector<const Association<T>*>* getParents(const T& ref) const;

    virtual ~Relationship();
};

template <typename T>
Association<T>* Relationship<T>::getAssociation(const T& ref1, const T& ref2) {
    Association<T>** i;
    for(i = associations.begin(); i != associations.end(); i++){
        if(&((*i)->getRelatedFrom()) == &ref1 && &((*i)->getRelatedTo()) == &ref2){
            return *i;
        }
    }

    return nullptr;
}

template <typename T>
const Association<T>* Relationship<T>::getConstAssociation(const T& ref1, const T& ref2) const {
    Association<T>* const * i;
    for(i = associations.constBegin(); i != associations.constEnd(); i++){
        if(&((*i)->getRelatedFrom()) == &ref1 && &((*i)->getRelatedTo()) == &ref2){
            return *i;
        }
    }

    return nullptr;
}

template <typename T>
bool Relationship<T>::areAssociated(const T &ref1, const T &ref2) const{
    return getConstAssociation(ref1, ref2) != nullptr;
}

template <typename T>
void Relationship<T>::associate(const T& ref1, const T& ref2, const QString& label){

    // Si l'association existe déjà, on met simplement à jour le label
    Association<T>* a = getAssociation(ref1, ref2);
    if(a != nullptr){
        a->label = label;
    }else{
        // Sinon on crée une nouvelle association
        associations.push_back(new Association<T>(*this, ref1, ref2, label));
    }
}

template <typename T>
void Relationship<T>::dissociate(const T &ref1, const T &ref2){
    Association<T>* a = getAssociation(ref1, ref2);
    associations.removeOne(a);

    delete a;
}


template <typename T>
QVector<const Association<T>*>* Relationship<T>::getChildren(const T& ref) const{
    QVector<const Association<T>*>* children = new QVector<const Association<T>*>;


    for(typename QVector<Association<T>*>::const_iterator t = associations.constBegin(); t != associations.constEnd(); t++){
        if((*t)->getRelatedFrom() == ref){
            children->push_back(*t);
        }
    }

    return children;
}

template <typename T>
QVector<const Association<T>*>* Relationship<T>::getParents(const T& ref) const{
    QVector<const Association<T>*>* parents = new QVector<const Association<T>*>;

    for(typename QVector<Association<T>*>::const_iterator t = associations.constBegin(); t != associations.constEnd(); t++){
        if((*t)->getRelatedTo() == ref){
            parents->push_back(*t);
        }
    }

    return parents;
}

template <typename T>
int Relationship<T>::countAssociations() const{
    return associations.size();
}

template <typename T>
Relationship<T>::~Relationship(){
    for(Association<T>** a = associations.begin(); a != associations.end(); a++){
        delete *a;
    }
}

#endif // RELATION_H
