#ifndef VERSIONSDOCKVIEW_H
#define VERSIONSDOCKVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QMap>
#include <QMessageBox>

#include "interfaces/editor/noteframeview.h"
#include "database.h"

class VersionsDockView : public QWidget
{

    const NoteHolder* currentNote;

    Database * database;
    NoteFrameView * noteview;

    QList<int> versionsMapping;
    QStringListModel* model;

    QPushButton* restoreButton;
    QPushButton* cleanButton;

    QListView* versionList;
    QVBoxLayout* layout;

    QMessageBox* cleanDialog;

    void initUI();
    QString label(int, QDateTime);
    void refresh();

    Q_OBJECT
public:
    explicit VersionsDockView(Database *, NoteFrameView *, QWidget *parent = 0);

signals:

public slots:
    void setCurrentNote(const NoteHolder *);
    void clean();
    void restore();
    void versionInserted(const NoteHolder& ,int);
    void noteStatusChanged(const NoteHolder&);
    void selectionChanged();
};

#endif // VERSIONSDOCKVIEW_H
