#ifndef DATABASE_H
#define DATABASE_H
#include "notesmanager.h"
#include "relations/relationsmanager.h"
#include "notes/note.h"
#include <QtSql>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QObject>
#include <QComboBox>
#include <QStringList>
#include <QMap>

class Database : public QObject
{
    NotesManager& notesManager;
    RelationsManager<NoteHolder>& relationsManager;

    QStringList types;

    QString filename;
    QSqlDatabase db;
    bool open = false;
    bool ignoreManagerSignal = false;

    bool createTables();/**< créer les tables*/


    Q_OBJECT
public:
    Database(NotesManager& nm, RelationsManager<NoteHolder>& rm, const QString& filename);/**< fait appel à la fonction connectBd*/

    const Note& loadContent(int id, const QString&) const;
    QMap<QDateTime, int>* fetchVersionsList(const NoteHolder&) const;
    void clean(const NoteHolder&, int leave);


    void loadAll();

    ~Database();

signals:
    void versionInserted(const NoteHolder& n, int db_id);

public slots:
    void insertVersion(const NoteHolder& n);/**< insérer tous les infos d'une note dans BDD*/
    void updateStatus(const NoteHolder& n);
    void emptyTrash();
    void insertRelation(void * const);
    void deleteRelation(void * const);
    void insertAssociation(void * const, void * const, void * const, QString);
    void deleteAssociation(void * const, void * const, void * const);
};


#endif // DATABASE_H
