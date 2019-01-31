#ifndef SOUNDINTERFACE_H
#define SOUNDINTERFACE_H


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
#include <QMediaPlayer>
#include <QComboBox>
#include <QVector>

#include "noteinterface.h"
#include "notes/sound.h"
class Sound;



class SoundInterface : public NoteInterface{
    Q_OBJECT

    const Sound* sound;
    QSound* soundToRegister;
    QString* nameFileSound;
    QLabel* labelSound;
    QLineEdit* titleEdit;
    QLineEdit* idEdit;
    QTextEdit* descriptionEdit;
    QFormLayout* layout;
    QVBoxLayout *mainLayout;
    QHBoxLayout* boutonLayout;
    QHBoxLayout* boutonLayout2;
    QPushButton* bAddSound;
    QPushButton* bStopMusic;
    QPushButton* bPlayMusic;
    bool initSound;
    //QMediaPlayer* player;

public :
    SoundInterface(const Sound& s, QWidget *parent = 0);
    void setNameFileSound(QString nameSound);

    const Note& toNote();
    void setReadOnly(bool);

public slots :
    void openSound();
    void playMusic();
    void stopMusic();
};

#endif // SOUNDINTERFACE_H
