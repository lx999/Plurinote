#include "taskinterface.h"
TaskInterface::TaskInterface(const Task& t,QWidget *parent): NoteInterface(parent),task(&t){
    if(task->getState()=="active"){
        layout=new QFormLayout;
        generate= new QPushButton(QString("Enregistrer"));
        titleEdit= new QLineEdit(task->getTitle(),this);
        actionEdit= new QTextEdit(task->getActionToBeDone(),this);
        //QString date=QDateTime::currentDateTime().toString();
        dateEdit= new QLineEdit(task->getExpired().toString(),this);
        idEdit= new QLineEdit(task->getIdentifier().toString(),this);
        idEdit->setReadOnly(1);
        idEdit->setFixedWidth(300);
        statusCombo= new QComboBox(this);
        priorityCombo= new QComboBox(this);

        // priority
        priorityCombo->addItem("0");
        priorityCombo->addItem("1");
        priorityCombo->addItem("2");
        priorityCombo->addItem("3");
        priorityCombo->addItem("4");
        priorityCombo->addItem("5");
        priorityCombo->setCurrentIndex(task->getPriority());

        // status
        statusCombo->addItem("En attente");
        statusCombo->addItem("En cours");
        statusCombo->addItem("Terminée");
        statusCombo->setCurrentIndex(task->getStatusInt());

        //Fixation des tailles des Widgets
        dateEdit->setFixedWidth(180);
        titleEdit->setFixedWidth(180);
        //ajout des Widget sur le layout
        layout->addRow("Identifiant :",idEdit);
        layout->addRow("Titre :",titleEdit);
        layout->addRow("Status :",statusCombo);
        layout->addRow("Priorité :",priorityCombo);
        layout->addRow("Date échouant",dateEdit);
        layout->addRow("Objectif :",actionEdit);
        layout->addWidget(generate);

        //layout de versions
        choisir=new QPushButton(QString("choisir"));
        versions=new QComboBox;
        parcourir();
        layout->addWidget(versions);
        layout->addWidget(choisir);
        supprimer=new QPushButton(QString("supprimer"));
        layout->addWidget(supprimer);

        setLayout(layout);
        setWindowTitle("Tâche à réaliser");

        //slot
        QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));
        QObject::connect(versions, SIGNAL(activated(int)), this, SLOT(enregistrerid(int)));
        QObject::connect(choisir, SIGNAL(clicked()), this, SLOT(charger()));
    }else{
        layout=new QFormLayout;


        titleEdit= new QLineEdit(task->getTitle(),this);
        titleEdit->setReadOnly(1);
        actionEdit= new QTextEdit(task->getActionToBeDone(),this);
        actionEdit->setReadOnly(1);
        //QString date=QDateTime::currentDateTime().toString();
        dateEdit= new QLineEdit(task->getExpired().toString(),this);
        dateEdit->setReadOnly(1);
        idEdit= new QLineEdit(task->getIdentifier().toString(),this);
        idEdit->setReadOnly(1);
        idEdit->setFixedWidth(300);

        // priority
        priorityEdit= new QLineEdit(QString::number(task->getPriority()),this);
        priorityEdit->setReadOnly(1);
        // status
        statusEdit= new QLineEdit(task->getStatus(),this);
        statusEdit->setReadOnly(1);
        //Fixation des tailles des Widgets
        dateEdit->setFixedWidth(180);
        titleEdit->setFixedWidth(180);
        //ajout des Widget sur le layout
        layout->addRow("Identifiant :",idEdit);
        layout->addRow("Titre :",titleEdit);
        layout->addRow("Status :",statusEdit);
        layout->addRow("Priorité :",priorityEdit);
        layout->addRow("Date échouant",dateEdit);
        layout->addRow("Objectif :",actionEdit);


        activer=new QPushButton(QString("activer"));
        layout->addWidget(activer);
        setLayout(layout);
        setWindowTitle("Tâche à réaliser");

        //slot
        //QObject::connect(activer, SIGNAL(clicked()), this, SLOT(charger()));

    }
}






void TaskInterface::parcourir(){
    QSqlQuery q;
    q.exec("SELECT n.Id,n.Title,n.Edited FROM (Note n INNER JOIN Task a ON n.Id=a.Id) WHERE a.Idreal='"+ task->getIdentifier().toString()+"';");
    while (q.next()) {
        a.push_back(q.value(0).toInt());
        QString final;
        final=q.value(0).toString()+"| "+q.value(1).toString()+q.value(2).toString();
        QStringList s;
        s<<final;
        versions->addItems(s);
    }
    q.finish();
}

//slots
void TaskInterface::save(){
    Task* t = new Task(*task);
    t->setTitle(titleEdit->text());
    t->setStatus(Status(statusCombo->currentIndex()));
    t->setPriority(priorityCombo->currentIndex());
    t->setActionToBeDone(actionEdit->toPlainText());
    t->setExpired(QDateTime::fromString(dateEdit->text()));

    task = t;
    emit newVersion(t); // signal d'émition pour la création d'une nouvelle version
    //QMessageBox::information(this, "Fichier", "Enregisterment de :\n" +titleEdit->text() +"\n"+statusCombo->currentText() + "\n" +priorityCombo->currentText() + "\n" +actionEdit->toPlainText() + "\n" +dateEdit->text()+ "\n"+ QDateTime::fromString(dateEdit->text()).toString());

}



void TaskInterface::charger(){
    QSqlQuery q;
    q.exec("SELECT n.Title,a.ActionToBeDone,a.Status,a.Priority,a.Expired FROM Task a,Note n WHERE n.Id=a.Id AND a.Id='"+ QString::number(Id) +"';");
    q.next();
    Task* change=const_cast<Task*>(task);
    change->setTitle(q.value(0).toString());
    change->setActionToBeDone(q.value(1).toString());
    change->setPriority(q.value(3).toInt());
    change->setExpired(q.value(4).toDateTime());
    switch(q.value(2).toInt()){
    case 0:change->setStatus(en_attente);break;
    case 1:change->setStatus(en_cours);break;
    case 2:change->setStatus(terminee);break;
    }
}

void TaskInterface::enregistrerid(int i){
    std::cout<<i;
    Id=a[i];
    std::cout<<Id;
}
