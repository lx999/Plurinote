QT += core
QT += gui
QT += multimediawidgets
QT += sql
CONFIG += c++11

TARGET = Projet
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    notes/note.cpp \
    notesmanager.cpp \
    notes/article.cpp \
    notes/task.cpp \
    notes/image.cpp \
    notes/video.cpp \
    notes/sound.cpp \
    notes/notextualnote.cpp \
    memento.cpp \
    interfaces/content-editor/articleinterface.cpp \
    interfaces/content-editor/taskinterface.cpp \
    interfaces/content-editor/imageinterface.cpp \
    interfaces/content-editor/soundinterface.cpp \
    interfaces/content-editor/videointerface.cpp \
    interfaces/mainframe.cpp \
    interfaces/editor/noteframeview.cpp \
    interfaces/content-editor/noteinterface.cpp \
    interfaces/mainwindow.cpp \
    interfaces/relations/relateddockview.cpp \
    interfaces/relations/createlinkdialog.cpp \
    notes/noteholder.cpp \
    database.cpp \
    interfaces/sidebar/sidebar.cpp \
    interfaces/sidebar/noteslistview.cpp \
    interfaces/versions/versionsdockview.cpp \
    interfaces/relations/managerelationsdialog.cpp \
    proxys/notestatefilter.cpp \
    proxys/notesproxy.cpp \
    proxys/taskfilter.cpp


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS +=\
    notes/note.h \
    notesmanager.h \
    utils.h \
    notes/article.h \
    notes/task.h \
    notes/image.h \
    notes/video.h \
    notes/sound.h \
    notes/notextualnote.h \
    memento.h \
    interfaces/content-editor/articleinterface.h \
    interfaces/content-editor/taskinterface.h \
    interfaces/content-editor/imageinterface.h \
    interfaces/content-editor/soundinterface.h \
    interfaces/content-editor/videointerface.h \
    relations/relationship.h \
    relations/relationsmanager.h \
    relations/association.h \
    relations/bidirectionalrelationship.h \
    interfaces/mainframe.h \
    interfaces/editor/noteframeview.h \
    interfaces/content-editor/noteinterface.h \
    interfaces/mainwindow.h \
    interfaces/relations/relateddockview.h \
    interfaces/relations/createlinkdialog.h \
    notes/noteholder.h \
    database.h \
    interfaces/sidebar/sidebar.h \
    interfaces/sidebar/noteslistview.h \
    interfaces/versions/versionsdockview.h \
    interfaces/relations/managerelationsdialog.h \
    proxys/notestatefilter.h \
    proxys/notesproxy.h \
    proxys/taskfilter.h


RESOURCES += \
    resources.qrc

