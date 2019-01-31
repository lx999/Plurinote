#include "memento.h"
#include <QMessageBox>
//
// MementoCaretaker
//


//Singleton

MementoCaretaker* MementoCaretaker::instance=0;
MementoCaretaker& MementoCaretaker::getInstance(){
    if(!instance)
        instance=new MementoCaretaker();
    return *instance;
}

void MementoCaretaker::freeInstance(){
    if(instance){
        delete instance;
    }
     instance=nullptr;
}

//end Singleton

void MementoCaretaker::undo() {
    if(m_vecMemento.size()!=0){
        Memento* mem=m_vecMemento.back();
        stopPropagation = true;
        m_vecMemento.pop_back();
        m_vecMementoInverse.push_back(mem);
        if (typeid(*mem)==typeid(MementoNoteState)){
            MementoNoteState* MementoNoteStatemem =dynamic_cast<MementoNoteState*> (mem);
            emit changeNoteState(MementoNoteStatemem->getNote(), MementoNoteStatemem->getOldState());}
        else
            if (typeid(*mem)==typeid(MementoRelation)){
                MementoRelation* MementoRelationmem =dynamic_cast<MementoRelation*> (mem);
                emit DeleteRelation(MementoRelationmem->getNameRelation(),MementoRelationmem->getNote(),MementoRelationmem->getNote1());}
            else throw("Error de TypeMemento");

    }
    else{
        std::cout<<"rien à annuler"<<std::endl;
    }
     std::cout<<"UNDO"<<std::endl;
}



void MementoCaretaker::save(Memento* memento) {
    m_vecMemento.push_back(memento);
}

void MementoCaretaker::redo(){
    if (m_vecMementoInverse.size()!=0){
        Memento* mem= m_vecMementoInverse.back();
        m_vecMementoInverse.pop_back();
        m_vecMemento.push_back(mem);
        stopPropagation = true;
        if (typeid(*mem)==typeid(MementoNoteState)){
            MementoNoteState* MementoNoteStatemem =dynamic_cast<MementoNoteState*> (mem);
            emit changeNoteState(MementoNoteStatemem->getNote(), MementoNoteStatemem->getNewState());}
        else
            if (typeid(*mem)==typeid(MementoRelation)){
                MementoRelation* MementoRelationmem =dynamic_cast<MementoRelation*> (mem);
                emit CreateRelation(MementoRelationmem->getNameRelation(),MementoRelationmem->getNote(),MementoRelationmem->getNote1(),MementoRelationmem->getNameLabel());}
            else throw("Error de TypeMemento");
    }
    else{
        std::cout<<"rien à rétablir"<<std::endl;
    }
    std::cout<<"REDO"<<std::endl;
    //QMessageBox::information(this,QString("great!"),QString("great"));

}

