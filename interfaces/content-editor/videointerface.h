#ifndef VIDEOINTERFACE_H
#define VIDEOINTERFACE_H


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
#include <QMediaPlaylist>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QMovie>
#include <QToolButton>
#include <QStyle>
#include <QComboBox>
#include <QVector>

#include "notes/video.h"
#include "noteinterface.h"

class Video;

class VideoInterface : public NoteInterface {
    Q_OBJECT
    const Video* video;
    QMovie* videoToRegister;
    QGraphicsVideoItem* item;
    QString* nameFileVideo;

    QGraphicsView* graphicsView;
    QGraphicsScene* scene;

    QLineEdit* titleEdit;
    QTextEdit* descriptionEdit;

    QFormLayout* layout;
    QVBoxLayout* mainLayout;
    QHBoxLayout *layoutVideo;
    QHBoxLayout* boutonLayout;

    QToolButton* stopButton;
    QToolButton* openButton;
    QToolButton* playButton; //    QPushButton* playButton;
    QToolButton* pauseButton;


    QMediaPlayer* player;
    bool initVideo;


public:
    VideoInterface(const Video& vid, QWidget *parent = 0);
    void updateButtons();

    const Note& toNote();
    void setReadOnly(bool);

public slots:
    void openVideo();
    void playVideo();
    void stopVideo();
    void pauseVideo();
};

#endif // VIDEOINTERFACE_H
