#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
const QString REFERENCE = "Référence";

#include <QMainWindow>
#include <QDockWidget>
#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QtWidgets>
#include "mainframe.h"
#include "notesmanager.h"
#include "interfaces/relations/relateddockview.h"
#include "interfaces/versions/versionsdockview.h"
#include "relations/relationsmanager.h"
#include "memento.h"
#include <QRegExp>



class MainWindow : public QMainWindow
{
    Mainframe* mf;

    NotesManager& notesManager;
    Database& database;

    RelatedDockView* relationsView;
    QDockWidget* relationsDock;

    VersionsDockView* versionsView;
    QDockWidget* versionsDock;

    RelationsManager<NoteHolder>& relationsManager;
    NotesRelationsManagerSlotsProxy* relationsProxy;

    MementoCaretaker* memento;

    //menu
    QMenu* menuFichier;
    QMenu* menuEdition;
    QMenu* menuAffichage;
    QAction* actionRelation;

    QMessageBox* emptyTrashDialog;
    QMessageBox* deleteReferencedDialog;
    QMessageBox* helpingMenu;

    const NoteHolder* pendingNote = nullptr;

    QRegExp referencesRegexp = QRegExp("[\\\\]ref(\\{[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}\\})");

    void initUI();
    void initMemento();
    void closeEvent(QCloseEvent *event);

    Q_OBJECT

public:
    explicit MainWindow(NotesManager& nm, RelationsManager<NoteHolder>& rm, MementoCaretaker& mement, Database& db, QWidget *parent = 0);

    RelatedDockView* getRelatedDockView() { return relationsView; }
signals:
    void undo();
    void redo();

public slots:
    void updateReferences(const NoteHolder&, const Note&);
    void noteStatusChangeRequested(const NoteHolder&, NoteState);
    void archiveNote();

};

#endif // MAINWINDOW_H
