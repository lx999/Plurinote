#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QVector>
#include <iterator>
#include <QStandardItemModel>
#include <QModelIndex>
#include "utils.h"
#include "notes/noteholder.h"
#include "notes/note.h"
#include "notes/image.h"
#include "notes/article.h"
#include "notes/video.h"
#include "notes/task.h"
#include "notes/sound.h"
#include "relations/relationsmanager.h"

class Note;
class NoteHolder;

class NotesManager : public QObject{
public:

    class NotesModelHolder
    {
        NotesManager& notesManager;
        QStandardItemModel model;
        QMap<NoteHolder*, QModelIndex> indexMap;

        QStandardItem* generateItem(const NoteHolder&);
        void updateItem(QStandardItem*, const NoteHolder&);
        void updateItem(const NoteHolder& note);

        friend class NotesManager;

    public:
        NotesModelHolder(NotesManager& nm) : notesManager(nm){}
        QStandardItemModel& getModel(){ return model; }
        const NoteHolder& findByIndex(const QModelIndex&) const;
        bool hasIndex(const QModelIndex&) const;
    };

private:
    std::vector<NoteHolder*> notes;
    NotesModelHolder* modelHolder;

    static NotesManager* instance;// singleton
    NotesManager();
    NotesManager(const NotesManager& n);
    NotesManager& operator=(const NotesManager& n);

    void registerNewNote(NoteHolder& note);

    Q_OBJECT

public:
    static NotesManager& getInstance();
    static void freeInstance();

    const NoteHolder* find(const QUuid& identifier) const;
    NotesModelHolder & getModelHolder() const { return *modelHolder; }
    NoteHolder& import(QString identifier, QDateTime created, int state, const Note& body);

    class Iterator : public ::Iterator<const NoteHolder>{
        const NotesManager& manager;
        int idx;
        Iterator();
    public:
        Iterator(const NotesManager& m) : manager(m), idx(-1){}
        const NoteHolder& current() const;
        bool isDone() const;
        void next();

    };

    NotesManager::Iterator& getIterator() const;

    Note& createNoteBody(QString type) const;
    bool replaceReference(const Note *);

signals:

    void noteCreated(const NoteHolder&);
    void noteUpdated(const NoteHolder&);
    void noteStatusChanged(const NoteHolder&, NoteState oldState);


public slots:

    const NoteHolder& createArticle();
    const NoteHolder& createTask();
    const NoteHolder& createImage();
    const NoteHolder& createSound();
    const NoteHolder& createVideo();
    const NoteHolder& createNote(QString type);
    void noteStatusChangeRequested(const NoteHolder& holder, NoteState state);
    void updateNote(const NoteHolder& holder, const Note& newBody);


   // ~NotesManager();
};

#endif // NOTESMANAGER_H
