#ifndef MANAGERELATIONSDIALOG_H
#define MANAGERELATIONSDIALOG_H

#include <QDialog>
#include <QListView>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QStandardItemModel>
#include <QGroupBox>
#include "relations/relationsmanager.h"
#include "notes/noteholder.h"

class ManageRelationsDialog : public QDialog
{

    Q_OBJECT

    RelationsManager<NoteHolder>& manager;

    QGridLayout* layout;
    QDialogButtonBox* dialog_btns_box;

    QListView* listview;

    QPushButton* add_btn;
    QPushButton* del_btn;

    QGroupBox* insertGroup;

    QLineEdit* relname_ipt;
    QCheckBox* bi_cbx;

    Relationship<NoteHolder>* rel_to_delete;


    void initUI();


public:
    ManageRelationsDialog(RelationsManager<NoteHolder>& relationsManager, QWidget *parent = 0);

public slots:
    void addRelation();
    void requestDeleteRelation();
    void deleteRelation();
    void selectionChanged(QItemSelection,QItemSelection);
};

#endif // MANAGERELATIONSDIALOG_H
