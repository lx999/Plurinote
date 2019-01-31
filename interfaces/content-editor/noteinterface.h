#ifndef GENERALINTERFACE_H
#define GENERALINTERFACE_H

#include <QWidget>
#include "notes/note.h"
#include <iostream>
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QStringList>


class NoteManager;
class Note;

class NoteInterface : public QWidget{
    Q_OBJECT

public:
    explicit NoteInterface(QWidget *parent = 0);
    virtual const Note& toNote() = 0;
    virtual void setReadOnly(bool) = 0;

};

#endif // GENERALINTERFACE_H
