#ifndef ARTICLE_H
#define ARTICLE_H


#include "note.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include "interfaces/content-editor/articleinterface.h"
class ArticleInterface;

/*! Classe Article, classe fille de Note  */

class Article : public Note{
    QString text; /**< Texte qui correspond au coeur de l'article  */
    static const QString type; /**< Attribut static qui correspond au type de Note */
public:

    void setText(const QString& texte); /**< Méthode modifiant l'attribut text */
    const QString& getText() const; /**< Accesseur de l'attribut Text */
    NoteInterface* getUI() const; /**< Méthode virtuelle renvoyant l'interface de Article */

    const QString& getType() const; /**< Méthode permettant d'obtenir le type de Note */

    const QString getEveryText() const;
};

#endif // ARTICLE_H
