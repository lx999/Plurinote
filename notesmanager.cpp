#include "notesmanager.h"

NotesManager::NotesManager(){
    modelHolder = new NotesModelHolder(*this);
}

/* Tout membre static  doit être définie dans un fichier source et initialisé */
NotesManager* NotesManager::instance=0;

NotesManager& NotesManager::getInstance(){
    if (!instance)// si pas encore d'instance de la classe
        instance= new NotesManager();// constructeur sans arguments
    return *instance;
}

void NotesManager::freeInstance(){
    if (instance)
        delete instance;
    instance=nullptr; // obligatoire
}

/*Fin des membres statiques*/


const NoteHolder& NotesManager::Iterator::current() const{
    if(idx == -1){
        throw new AppException("NotesIterator points nothing");
    }

    //return dynamic_cast<Note&>(*(manager.notesModel->item(idx)));
    return *manager.notes[idx];
}

bool NotesManager::Iterator::isDone() const{
    //return idx >= 0 && idx >= manager.notesModel->rowCount() - 1;
    int size = manager.notes.size();
    return /*idx >= 0 && */idx >= size - 1;
}

void NotesManager::Iterator::next(){
    if(!isDone()){
        idx++;
    }else{
        throw new AppException("NotesIterator overflow attempt");
    }
}

void NotesManager::registerNewNote(NoteHolder& note){
    notes.push_back(&note);
    modelHolder->generateItem(note);
    emit noteCreated(note);
}

Note& NotesManager::createNoteBody(QString type) const{
    if(type == "Article") return *(new Article());
    if(type == "Task") return *(new Task());
    if(type == "Image") return *(new Image());
    if(type == "Sound") return *(new Sound());
    if(type == "Video") return *(new Video());
    throw new AppException("Unknown note type");
}

const NoteHolder& NotesManager::createNote(QString type){
    NoteHolder* n_holder = new NoteHolder();
    n_holder->update(createNoteBody(type));
    registerNewNote(*n_holder);

    return *n_holder;
}

const NoteHolder& NotesManager::createArticle(){
    return createNote("Article");
}

const NoteHolder& NotesManager::createTask(){
    return createNote("Task");
}

const NoteHolder& NotesManager::createImage(){
    return createNote("Image");
}

const NoteHolder& NotesManager::createVideo(){
    return createNote("Video");
}

const NoteHolder& NotesManager::createSound(){
    return createNote("Sound");
}

const NoteHolder* NotesManager::find(const QUuid& identifier) const{
    NotesManager::Iterator& it = getIterator();

    while(!it.isDone()){
        it.next();
        const NoteHolder& n = it.current();
        if(n.getId() == identifier){
            delete &it;
            return &n;
        }
    }

    delete &it;
    return nullptr;
}

void NotesManager::updateNote(const NoteHolder& holder, const Note& newBody){
    const_cast<NoteHolder&>(holder).update(newBody);
    modelHolder->updateItem(holder);
    emit noteUpdated(holder);
}

void NotesManager::noteStatusChangeRequested(const NoteHolder& const_holder, NoteState state){
    NoteHolder& holder = const_cast<NoteHolder&>(const_holder);
    NoteState oldState= NoteState(holder.getState());
    holder.setState(state);

    emit noteStatusChanged(holder, oldState);

}


NotesManager::Iterator& NotesManager::getIterator() const{
    Iterator* it = new NotesManager::Iterator(*this);
    return *it;
}



QStandardItem* NotesManager::NotesModelHolder::generateItem(const NoteHolder& note){
    QString qstr = QString(":/icons/") + note.getLastVersion().getType().toLower();
    QStandardItem* item = new QStandardItem(QIcon(qstr), note.getLastVersion().getTitle().length() ? note.getLastVersion().getTitle() : "Note sans nom");

    model.appendRow(item);
    indexMap.insert(const_cast<NoteHolder*>(&note), item->index());
    return item;
}

void NotesManager::NotesModelHolder::updateItem(QStandardItem* item, const NoteHolder& note){
    item->setText(note.getLastVersion().getTitle().length() ? note.getLastVersion().getTitle() : "Note sans nom");
}

void NotesManager::NotesModelHolder::updateItem(const NoteHolder& note){
    const QModelIndex& index = indexMap.value(const_cast<NoteHolder*>(&note));
    QStandardItem* item = model.itemFromIndex(index);
    updateItem(item, note);
}

const NoteHolder& NotesManager::NotesModelHolder::findByIndex(const QModelIndex& index) const{
    return *indexMap.key(index);
}

bool NotesManager::NotesModelHolder::hasIndex(const QModelIndex& index) const{
    return indexMap.key(index) != 0;
}


NoteHolder& NotesManager::import(QString identifier, QDateTime created, int state, const Note& body){
    NoteHolder* nh = new NoteHolder(identifier, created, state);
    nh->update(body);

    registerNewNote(*nh);
    return *nh;
}
