#ifndef CREATELINKDIALOG_H
#define CREATELINKDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include "notes/note.h"
#include "relations/relationsmanager.h"
#include "relations/relationship.h"
#include "notesmanager.h"
#include "managerelationsdialog.h"

class CreateLinkDialog : public QDialog
{
    NotesManager& notesManager = NotesManager::getInstance();
    RelationsManager<NoteHolder>& relationsManager;
    ManageRelationsDialog& manageDialog;

    QVBoxLayout* glblLayout;
    QFormLayout* formLayout;
    QComboBox* relationCombo;
    QComboBox* relatedCombo;
    QLineEdit* labelField;
    QDialogButtonBox* btnsLayout;

    const NoteHolder* currentNote;

    void initUI();
    void populate();
    void accept();


    Q_OBJECT
public:
    explicit CreateLinkDialog(RelationsManager<NoteHolder>& relationsManager, ManageRelationsDialog& manageDialog, QWidget *parent = 0);
    void setCurrentNote(const NoteHolder& n);


signals:
    void linkCreated(const QString& rel, const NoteHolder&, const NoteHolder&, QString label);


public slots:
     void openManage();
};

#endif // CREATELINKDIALOG_H
