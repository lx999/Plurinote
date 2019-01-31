#ifndef RELATEDDOCKVIEW_H
#define RELATEDDOCKVIEW_H

#include <QWidget>
#include <QTreeView>
#include "notesmanager.h"
#include "relations/relationsmanager.h"
#include "memento.h"
#include <QVBoxLayout>
#include <QLabel>
#include "notes/note.h"
#include <QStandardItemModel>
#include <QMap>
#include <QModelIndex>
#include <QPushButton>
#include "createlinkdialog.h"

class RelatedDockView : public QWidget
{

    QPushButton* linkButton;
    QVBoxLayout* layout;
    QTreeView* childrenView;
    QTreeView* parentsView;

    CreateLinkDialog* createDialog;
    ManageRelationsDialog* manageDialog;

    RelationsManager<NoteHolder>& relationsManager;
    MementoCaretaker& memento;

    QStandardItemModel childrenModel;
    QStandardItemModel parentsModel;

    QMap<QModelIndex, const Association<NoteHolder>*> childrenIndexMap;
    QMap<QModelIndex, const Association<NoteHolder>*> parentsIndexMap;


    const NoteHolder* selectedNote;

    QMessageBox* deleteConfirm;

    void initUI();

    Q_OBJECT
public:
    explicit RelatedDockView(RelationsManager<NoteHolder>& relationsManager,MementoCaretaker& mement ,QWidget *parent = 0);
    bool eventFilter(QObject *object, QEvent *event);
signals:
    void linkCreated(QString rel, const NoteHolder&, const NoteHolder&, QString label);
    void linkDestroyed(QString rel, const NoteHolder&, const NoteHolder&,QString label);

public slots:
    void setSelectedNote(const NoteHolder*);
    void noteStatusChanged(const NoteHolder& note);
    void refresh();
};

#endif // RELATEDDOCKVIEW_H
