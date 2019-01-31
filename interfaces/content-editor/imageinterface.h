#ifndef IMAGEINTERFACE_H
#define IMAGEINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QCheckBox>
#include <QStyle>
#include <QComboBox>
#include <QVector>

#include "noteinterface.h"
#include "notes/image.h" // inclusion récursif.?

class Image;

class ImageInterface: public NoteInterface {
    Q_OBJECT

    const Image* image;
    QImage* imageToRegister;
    QString* nameFileImage;
    QLabel* imageLabel;
    QLineEdit* titleEdit;
    QLineEdit* idEdit;
    QTextEdit* descriptionEdit;
    QFormLayout* layout;
    QVBoxLayout *mainLayout;
    QHBoxLayout* boutonLayout;
    QPushButton* bAddImage;
    QCheckBox* fitCheckBox;
    /**< la partie choisir et charger les versions */
    QFormLayout* boxLayout;

public:
    ImageInterface(const Image& im, QWidget *parent = 0);
    void setNameFileImage(QString nameImage);

    const Note& toNote();
    void setReadOnly(bool);

public slots :
    void openImage();
    void fitToWindow();
};

#endif // IMAGEINTERFACE_H
