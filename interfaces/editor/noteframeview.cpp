#include "noteframeview.h"
#include "notes/noteholder.h"
#include <QHBoxLayout>
#include <QObject>
#include <QFrame>
#include <QClipboard>
#include <QApplication>

NoteFrameView::NoteFrameView(QWidget *parent) :
    QWidget(parent),
    widget(nullptr)
{
    initUI();
}

void NoteFrameView::initUI(){


    layout = new QVBoxLayout;
    btns_bar = new QWidget;
    btns_bar_l = new QHBoxLayout;


    save_btn = new QPushButton("Enregistrer");
    copy_id_btn = new QPushButton("Référencer");

    btns_bar_l->addWidget(save_btn);
    btns_bar_l->addWidget(copy_id_btn);
    btns_bar_l->addSpacing(10);

    btns_bar->setMaximumHeight(50);
    btns_bar->setLayout(btns_bar_l);
    btns_bar->setVisible(false);

    layout->addWidget(btns_bar);

    setMinimumWidth(500);
    setLayout(layout);

    copyDialog = new QMessageBox(this);
    copyDialog->setIcon(QMessageBox::Information);
    copyDialog->setText("L'identifiant de cette note a été copié dans le presse papier. Collez-le dans une autre note pour permettre le référencement.");
    copyDialog->setModal(true);
    copyDialog->setWindowModality(Qt::WindowModal);

    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(save()));
    QObject::connect(copy_id_btn, SIGNAL(released()), this, SLOT(copy_id()));

}

void NoteFrameView::setNote(const NoteHolder * note){
    this->note = note;

    setNoteContent(note->getLastVersion());

    btns_bar->setVisible(true);
    save_btn->setVisible(note->isActive());
    copy_id_btn->setVisible(note->isActive());
}

void NoteFrameView::setNoteContent(const Note& content){

    if(widget != nullptr){
        layout->removeWidget(widget);
        delete widget;
    }

    widget = content.getUI();
    widget->setReadOnly(!note->isActive());

    layout->insertWidget(0, widget);
}

void NoteFrameView::save(){
    if(widget){
        const Note& newBody = widget->toNote();
        emit noteSaved(*note, newBody);
    }
}

void NoteFrameView::copy_id(){
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("\\ref" + note->getId().toString());

    copyDialog->exec();
}

void NoteFrameView::noteStatusChanged(const NoteHolder& note){
    if(this->note && *this->note == note){
        widget->setReadOnly(!note.isActive());
    }
}
