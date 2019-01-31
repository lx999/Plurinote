#ifndef BIDIRECTIONALRELATION_H
#define BIDIRECTIONALRELATION_H

#include <QString>
#include "relationship.h"
#include "relationsmanager.h"
#include "association.h"

template<typename T> class Relationship;
template<typename T> class Association;

template<typename T>
class BidirectionalRelationship : public Relationship<T>
{

    template<typename> friend class RelationsManager;

    BidirectionalRelationship(const QString& title) : Relationship<T>(title){}
    virtual Association<T>* getAssociation(const T& ref1, const T& ref2);
    virtual const Association<T>* getConstAssociation(const T& ref1, const T& ref2) const;
    virtual QVector<const Association<T>*>* getChildren(const T& ref) const;
    virtual QVector<const Association<T>*>* getParents(const T& ref) const;

public:
};


template<typename T>
Association<T>* BidirectionalRelationship<T>::getAssociation(const T& ref1, const T& ref2) {
    Association<T>** i;
    for(i = this->associations.begin(); i != this->associations.end(); i++){
        if(((*i)->getRelatedFrom() == ref1 && (*i)->getRelatedTo() == ref2) || ((*i)->getRelatedFrom() == ref2 && (*i)->getRelatedTo() == ref1)){
            return *i;
        }
    }

    return nullptr;
}

template <typename T>
const Association<T>* BidirectionalRelationship<T>::getConstAssociation(const T& ref1, const T& ref2) const {
    Association<T>* const * i;
    for(i = this->associations.constBegin(); i != this->associations.constEnd(); i++){
        if(((*i)->getRelatedFrom() == ref1 && (*i)->getRelatedTo() == ref2) || ((*i)->getRelatedFrom() == ref2 && (*i)->getRelatedTo() == ref1)){
            return *i;
        }
    }

    return nullptr;
}

template <typename T>
QVector<const Association<T>*>* BidirectionalRelationship<T>::getChildren(const T& ref) const{
    QVector<const Association<T>*>* children = new QVector<const Association<T>*>;

    for(typename QVector<Association<T>*>::const_iterator t = this->associations.constBegin(); t != this->associations.constEnd(); t++){
        if((*t)->getRelatedFrom() == ref){
            children->push_back(*t);
        }else if((*t)->getRelatedTo() == ref){
            children->push_back(*t);
        }
    }

    return children;
}

template <typename T>
QVector<const Association<T>*>* BidirectionalRelationship<T>::getParents(const T& ref) const{
    return getChildren(ref);
}

#endif // BIDIRECTIONALRELATION_H
