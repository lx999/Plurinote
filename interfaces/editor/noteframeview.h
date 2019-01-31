#ifndef NOTEFRAMEVIEW_H
#define NOTEFRAMEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "notes/noteholder.h"
#include "interfaces/content-editor/noteinterface.h"

class NoteFrameView : public QWidget
{
    Q_OBJECT

    const NoteHolder* note;

    NoteInterface* widget;
    QVBoxLayout* layout;

    QWidget* btns_bar;
    QHBoxLayout* btns_bar_l;

    QPushButton* save_btn;
    QPushButton* copy_id_btn;

    QMessageBox* copyDialog;

    void initUI();

public:
    explicit NoteFrameView(QWidget *parent = 0);


signals:
    void noteSaved(const NoteHolder&, const Note& body);
public slots:
    void setNote(const NoteHolder * note);
    void setNoteContent(const Note& note);
    void save();
    void copy_id();
    void noteStatusChanged(const NoteHolder&);
};

#endif // NOTEFRAMEVIEW_H
