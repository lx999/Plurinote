#ifndef ARTICLEINTERFACE_H
#define ARTICLEINTERFACE_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QObject>
#include <QComboBox>
#include <QVector>
#include "notes/article.h"
#include "noteinterface.h"

class Article;

class ArticleInterface: public NoteInterface{
    Q_OBJECT
    const Article* article;

    QLineEdit* titleEdit;
    QTextEdit* textEdit;
    QFormLayout* layout;

public:
    ArticleInterface(const Article& a, QWidget *parent = 0);
    const Note& toNote();
    void setReadOnly(bool);

};

#endif // ARTICLEINTERFACE_H
