#include "article.h"
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
const QString Article::type = QString("Article");


void Article::setText(const QString& texte){
    text=texte;
    setEdited();
}

const QString& Article::getText() const{
    return text;
}

NoteInterface* Article::getUI() const{
    return new ArticleInterface(*this);

}

const QString& Article::getType() const{
    return type;
}

const QString Article::getEveryText() const{
    return Note::getEveryText() + " " + text;
}
