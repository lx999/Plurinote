#include "articleinterface.h"
ArticleInterface::ArticleInterface(const Article& a, QWidget *parent): NoteInterface(parent),article(&a){
    layout=new QFormLayout;
    titleEdit= new QLineEdit(article->getTitle(),this);
    textEdit= new QTextEdit(article->getText(),this);
    //ajustement de la taille des Widgets
    titleEdit->setFixedWidth(180);

    //ajout des widgets à la layout
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Corps :",textEdit);

    setLayout(layout);
    setWindowTitle("Article");

}

//slot
const Note& ArticleInterface::toNote(){
    Article * a = new Article(*article);
    a->setText(textEdit->toPlainText());
    a->setTitle(titleEdit->text());

    return *(article = a);
}

void ArticleInterface::setReadOnly(bool readOnly){
    titleEdit->setDisabled(readOnly);
    textEdit->setDisabled(readOnly);
}
