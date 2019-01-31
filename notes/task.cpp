#include "task.h"

const QString Task::type = QString("Task");

// accesseurs
 QString Task::getStatus() const{ //{en_attente, en_cours,terminee}
    if(status==0)
        return QString("en_attente");
    else if(status==1)
        return QString("en_cours");
    else
        return QString("terminee");
}

unsigned int Task::getPriority() const{
    return priority;
}

const QString& Task::getActionToBeDone() const{
    return actionToBeDone;
}

const QDateTime& Task::getExpired() const{
    return expired;
}

unsigned int Task::getStatusInt() const{
    return status;
}

const QString Task::getEveryText() const{
    return Note::getEveryText() + " " + actionToBeDone;
}


// setters

void Task::setActionToBeDone(const QString& a){
    actionToBeDone=a;
    setEdited();
}

void Task::setPriority(unsigned int p){
    if (p>5)
        throw AppException("Error with priority level (must be beetween 0 and 5)");
    priority=p;
    setEdited();
}

void Task::setStatus(int s){
    status=static_cast<Status>(s);
    setEdited();
}

void Task::setExpired(const QDateTime exp){
    expired=exp;
    setEdited();
}

//Interface
NoteInterface* Task::getUI() const{
    return new TaskInterface(*this);
}

Status Task::getStatus_re() const{
    return status;
}

const QString& Task::getType() const{
    return type;
}

