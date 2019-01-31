#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include "relationship.h"
#include "relationsmanager.h"




template <typename> class Relationship;
template <typename> class RelationsManager;

template<typename T>
class Association{
    Relationship<T>& relation;
    const T& obj1;
    const T& obj2;
    QString label;

    template<typename> friend class QVector;
    friend class Relationship<T>;
    friend class RelationsManager<T>;

    Association();
    Association(const Association<T>& a): obj1(a.obj1),obj2(a.obj2),relation(a.relation){}
    Association(Relationship<T>& rel, const T& obj1, const T& obj2, const QString& label = "") : relation(rel), obj1(obj1), obj2(obj2), label(label){}
public:

    bool operator ==(const Association& o){
        return (&obj1 == &(o.obj1) && &obj2 == &(o.obj2) && label == o.label);
    }

    Relationship<T>& getRelation() const { return relation; }
    const T& getRelatedFrom() const { return obj1; }
    const T& getRelatedTo() const { return obj2; }
    QString getLabel() const { return label; }

};

#endif // ASSOCIATION_H
