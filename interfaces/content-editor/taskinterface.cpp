#include "taskinterface.h"
TaskInterface::TaskInterface(const Task& t,QWidget *parent): NoteInterface(parent),task(&t){
    layout=new QFormLayout;

    titleEdit= new QLineEdit(task->getTitle(),this);
    actionEdit= new QTextEdit(task->getActionToBeDone(),this);
    dateEdit= new QDateTimeEdit(task->getExpired(),this);
    statusCombo= new QComboBox(this);
    priorityCombo= new QComboBox(this);

    // priority
    priorityCombo->addItem("Prioritaire");
    priorityCombo->addItem("Pas de priorité");
    priorityCombo->addItem("Peu important");

    priorityCombo->setItemIcon(0, QIcon(":/icons/priority-high"));
    priorityCombo->setItemIcon(1, QIcon(":/icons/priority-medium"));
    priorityCombo->setItemIcon(2, QIcon(":/icons/priority-low"));
    priorityCombo->setCurrentIndex(task->getPriority()-1);

    // status
    statusCombo->addItem("En attente");
    statusCombo->addItem("En cours");
    statusCombo->addItem("Terminée");
    statusCombo->setCurrentIndex(task->getStatusInt());

    //Fixation des tailles des Widgets
    dateEdit->setFixedWidth(180);
    titleEdit->setFixedWidth(180);
    //ajout des Widget sur le layout
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Status :",statusCombo);
    layout->addRow("Priorité :",priorityCombo);
    layout->addRow("Date échouant",dateEdit);
    layout->addRow("Objectif :",actionEdit);

    setLayout(layout);
    setWindowTitle("Tâche à réaliser");


}

void TaskInterface::setReadOnly(bool readOnly){
    titleEdit->setDisabled(readOnly);
    actionEdit->setDisabled(readOnly);
    dateEdit->setDisabled(readOnly);
    priorityCombo->setDisabled(readOnly);
    statusCombo->setDisabled(readOnly);
}

//slots
const Note& TaskInterface::toNote(){
    Task* t = new Task(*task);
    t->setTitle(titleEdit->text());
    t->setStatus(Status(statusCombo->currentIndex()));
    t->setPriority(priorityCombo->currentIndex()+1);
    t->setActionToBeDone(actionEdit->toPlainText());
    t->setExpired(dateEdit->dateTime());

    return *(task = t);
}


