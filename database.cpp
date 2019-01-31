#include "database.h"
#include "notes/article.h"
#include "notes/image.h"
#include "notes/sound.h"
#include "notes/video.h"
#include "notes/task.h"
#include "relations/relationship.h"
#include "relations/bidirectionalrelationship.h"
#include "relations/association.h"

Database::Database(NotesManager& nm, RelationsManager<NoteHolder>& rm, const QString& filename) : notesManager(nm), relationsManager(rm), filename(filename){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    open = db.open();

    if(!open) throw new AppException("Impossible de se connecter à la base de données. La sauvegarde des données ne sera pas disponible.");

    createTables();
    //if(!createTables()) throw new AppException("Erreur lors de l'initialisation de la base de données.");

    types << "Article" << "Image" << "Task" << "Sound" << "Video";

   connect(&nm, SIGNAL(noteCreated(NoteHolder)), this, SLOT(insertVersion(NoteHolder)));
   connect(&nm, SIGNAL(noteUpdated(NoteHolder)), this, SLOT(insertVersion(NoteHolder)));
   connect(&nm, SIGNAL(noteStatusChanged(NoteHolder, NoteState)), this, SLOT(updateStatus(NoteHolder)));
   connect(rm.getProxy(), SIGNAL(relationCreated(void * const)), this, SLOT(insertRelation(void * const)));
   connect(rm.getProxy(), SIGNAL(relationDeleted(void * const)), this, SLOT(deleteRelation(void * const)));
   connect(rm.getProxy(), SIGNAL(objectsLinked(void * const, void * const, void * const, QString)), this, SLOT(insertAssociation(void * const, void * const, void * const, QString)));
   connect(rm.getProxy(), SIGNAL(objectsUnlinked(void * const, void * const, void * const)), this, SLOT(deleteAssociation(void * const, void * const, void * const)));
}

bool Database::createTables(){
        QSqlQuery query;
        bool result =
           query.exec("CREATE TABLE IF NOT EXISTS Note (Id INTEGER PRIMARY KEY AUTOINCREMENT,Genre VARCHAR(20) NOT NULL, HolderId VARCHAR NOT NULL, Title VARCHAR(20) ,Created TEXT, Edited TEXT,State INT);")
        && query.exec("CREATE TABLE IF NOT EXISTS Article (Id INTEGER NOT NULL,Text TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id) ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Image (Id INTEGER NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Task (Id INTEGER NOT NULL,ActionToBeDone TEXT ,Status VARCHAR(20) ,Priority INT(1) , Expired TEXT , PRIMARY KEY (Id), FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Sound (Id INTEGER NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Video (Id INTEGER NOT NULL,Description TEXT ,File TEXT , PRIMARY KEY (Id),FOREIGN KEY(Id) REFERENCES Note(Id)ON DELETE CASCADE);")
        && query.exec("CREATE TABLE IF NOT EXISTS Relationship(Name VARCHAR(255), Bidirectionnal BOOLEAN, PRIMARY KEY(Name));")
        && query.exec("CREATE TABLE IF NOT EXISTS Association(Relation VARCHAR(255) NOT NULL, NoteFrom VARCHAR NOT NULL, NoteTo VARCHAR NOT NULL, Label VARCHAR, PRIMARY KEY(Relation, NoteFrom, NoteTo), FOREIGN KEY(Relation) REFERENCES Relationship(Name) ON DELETE CASCADE);");

        return result;
}

void Database::insertVersion(const NoteHolder& note){
    if(ignoreManagerSignal) return;

    const Note& content = note.getLastVersion();
    const QString& type = content.getType();
    const QString& uuid = note.getId().toString();

    // Insertion des données de la version de la note
    QSqlQuery q;
    q.prepare("INSERT INTO Note(HolderId,Genre,Title,Created,Edited,State) VALUES (:HolderId, :Genre,:Title,:Created,:Edited,:State)");
    q.bindValue(":HolderId",uuid);
    q.bindValue(":Genre",type);
    q.bindValue(":Title",content.getTitle());
    q.bindValue(":Created",note.getCreated());
    q.bindValue(":Edited",content.getEdited());
    q.bindValue(":State",note.getState());

    if(!q.exec()) throw new AppException("Erreur lors de l'insertion d'une note en base de donnée");

    // Id de la version en base de donnée
    int id= q.lastInsertId().toInt();
    q.finish();

    q = QSqlQuery();
    bool subtable = true;

    if(type == "Article"){ // Article
        const Article& content_a = static_cast<const Article&>(content);
        q.prepare("INSERT INTO Article(Id, Text) VALUES (:Id, :Text)");
        q.bindValue(":Text", content_a.getText());
    } else

    if(type == "Task"){
        const Task& content_t = static_cast<const Task&>(content);
        q.prepare("INSERT INTO Task(Id,ActionToBeDone,Status,Priority,Expired) VALUES (:Id,:ActionToBeDone,:Status,:Priority,:Expired)");
        q.bindValue(":Id",id);
        q.bindValue(":ActionToBeDone",content_t.getActionToBeDone());
        q.bindValue(":Status",content_t.getStatus_re());
        q.bindValue(":Priority",content_t.getPriority());
        q.bindValue(":Expired",content_t.getExpired());

    } else

    if(const NoTextualNote* content_n = &dynamic_cast<const NoTextualNote&>(content)){ // Image + Sound + Video
        q.prepare("INSERT INTO " + type + "(Id, Description, File) VALUES (:Id, :Description, :File)");
        q.bindValue(":Description", content_n->getDescription());
        q.bindValue(":File", content_n->getFilename());
    } else {
        subtable = false;
    }

    if(subtable){
        q.bindValue(":Id", id);
        if(!q.exec()) throw new AppException("Erreur lors de l'insertion d'une note en base de donnée");

        q.finish();
    }

    emit versionInserted(note, id);
}

void Database::updateStatus(const NoteHolder &n){
    if(ignoreManagerSignal) return;

    QSqlQuery q;
    q.prepare("UPDATE Note SET State = ? WHERE HolderId = ?");
    q.addBindValue(n.getState());
    q.addBindValue(n.getId().toString());
    if(!q.exec()) throw new AppException("Erreur lors de l'insertion d'une note en base de donnée");
}

const Note& Database::loadContent(int version_id, const QString& note_type) const{
    QSqlQuery q;
    q.exec("SELECT * FROM (Note INNER JOIN " + note_type + " T ON Note.Id = T.Id) WHERE Note.Id='"+ QString::number(version_id) +"';");
    q.next();

    Note& note = notesManager.createNoteBody(note_type);

    if(note_type == "Article"){
        Article& a = static_cast<Article&>(note);
        a.setText(q.value("Text").toString());
        note = a;
    } else

    if(note_type == "Task"){
        Task& a = static_cast<Task&>(note);
        a.setActionToBeDone(q.value("ActionToBeDone").toString());
        a.setStatus(q.value("Status").toInt());
        a.setPriority(q.value("Priority").toInt());
        a.setExpired(q.value("Expired").toDateTime());

    } else if(NoTextualNote* a = &dynamic_cast<NoTextualNote&>(note)){
        a->setDescription(q.value("Description").toString());
        a->setFilename(q.value("File").toString());
    }else{
        throw new AppException("Note de type inconnu");
    }

    note.setTitle(q.value("Title").toString());

    return note;
}

void Database::loadAll(){
    ignoreManagerSignal = true;

    // Notes
    QSqlQuery q("SELECT Id, HolderId, Max(Edited), Created, State, Genre FROM Note GROUP BY HolderId ORDER BY Created DESC");
    while(q.next()){
        const Note& content = loadContent(q.value("Id").toInt(), q.value("Genre").toString());
        notesManager.import(q.value("HolderId").toString(), q.value("Created").toDateTime(), q.value("State").toInt(), content);
    }

    // Relations
    q = QSqlQuery("SELECT Name, Bidirectionnal FROM Relationship ORDER BY Name");
    while(q.next()){
        relationsManager.createRelation(q.value("Name").toString(), q.value("Bidirectionnal").toBool());
    }

    // Associations
    q = QSqlQuery("SELECT Relation, NoteFrom, NoteTo, Label FROM Association");
    while(q.next()){
        Relationship<NoteHolder>& rel = relationsManager.getRelation(q.value("Relation").toString());
        const NoteHolder& n1 = *notesManager.find(QUuid(q.value("NoteFrom").toString()));
        const NoteHolder& n2 = *notesManager.find(QUuid(q.value("NoteTo").toString()));

        relationsManager.link(rel, n1, n2, q.value("Label").toString());

    }

    ignoreManagerSignal = false;
}

QMap<QDateTime, int>* Database::fetchVersionsList(const NoteHolder& n) const{
    QSqlQuery q;
    q.prepare("SELECT Id, Edited FROM Note WHERE HolderId = :HolderId");
    q.bindValue(":HolderId", n.getId().toString());

    if(!q.exec()) throw new AppException("Note de type inconnu");

    QMap<QDateTime, int>* map = new QMap<QDateTime, int>;

    while(q.next()){
        map->insert(q.value("Edited").toDateTime(), q.value("Id").toInt());
    }

    return map;
}

void Database::clean(const NoteHolder& note, int leave){
    QSqlQuery q;
    q.prepare("DELETE FROM Note WHERE HolderId = :HolderId AND Id <> :Leave");
    q.bindValue(":HolderId", note.getId().toString());
    q.bindValue(":Leave", leave);

    if(!q.exec()) throw new AppException("Erreur lors du nettoyage");
}

void Database::emptyTrash(){
    QSqlQuery q;
    if(!q.exec("DELETE FROM Note WHERE State = 2")) throw new AppException("Erreur lors du vidage de la corbeille");
}

void Database::insertRelation(void * const r){
    if(!ignoreManagerSignal){
        const Relationship<NoteHolder>& rel = *(static_cast<Relationship<NoteHolder>* const>(r));
        const BidirectionalRelationship<NoteHolder>* v = dynamic_cast<const BidirectionalRelationship<NoteHolder>*>(&rel);
        bool bi = v;
        QSqlQuery q;
        q.prepare("INSERT INTO Relationship (Name, Bidirectionnal) VALUES(:Name, :Bidirectionnal)");
        q.bindValue(":Name", rel.getName());
        q.bindValue(":Bidirectionnal", bi);

        if(!q.exec()) throw new AppException("Erreur lors de l'ajout de relation");
    }
}

void Database::deleteRelation(void * const r){
    const Relationship<NoteHolder>& rel = *(static_cast<Relationship<NoteHolder>* const>(r));
    QSqlQuery q;
    q.prepare("DELETE FROM Relationship WHERE Name = :Name");
    q.bindValue(":Name", rel.getName());

    if(!q.exec()) throw new AppException("Erreur lors de la supression de relation");
}

void Database::insertAssociation(void * const rel, void * const from, void * const to, QString label){
    if(!ignoreManagerSignal){
        const Relationship<NoteHolder>* relation = (const Relationship<NoteHolder> *) rel;
        const NoteHolder* note_from = (const NoteHolder*) from;
        const NoteHolder* note_to = (const NoteHolder*) to;

        QSqlQuery q;
        q.prepare("INSERT INTO Association (Relation, NoteFrom, NoteTo, Label) VALUES(:Relation, :From, :To, :Label)");
        q.bindValue(":Relation", relation->getName());
        q.bindValue(":From", note_from->getId().toString());
        q.bindValue(":To", note_to->getId().toString());
        q.bindValue(":Label", label);

        if(!q.exec()) throw new AppException("Erreur lors de l'ajout de l'association");
    }
}

void Database::deleteAssociation(void * const rel, void * const from, void * const to){

    const Relationship<NoteHolder>* relation = (const Relationship<NoteHolder> *) rel;
    const NoteHolder* note_from = (const NoteHolder*) from;
    const NoteHolder* note_to = (const NoteHolder*) to;

    QSqlQuery q;
    q.prepare("DELETE FROM Association WHERE Relation = :Relation AND NoteFrom = :From AND NoteTo = :To");
    q.bindValue(":Relation", relation->getName());
    q.bindValue(":From", note_from->getId().toString());
    q.bindValue(":To", note_to->getId().toString());

    if(!q.exec()) throw new AppException("Erreur lors de la supression de l'association");
}


Database::~Database(){
    if(open) db.close();
}

