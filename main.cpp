#include <QApplication>
#include <QtWidgets>
#include <QTextStream>
#include <QTimer>
#include <QTreeView>
#include "notesmanager.h"
#include "memento.h"
#include "database.h"
#include "interfaces/sidebar/sidebar.h"
#include "interfaces/mainwindow.h"
#include <QStandardItemModel>
#include <QMap>
#include <QModelIndex>
#include <QMessageBox>



int main(int argc, char *argv[]){


            QApplication app(argc, argv);
            app.setAttribute(Qt::AA_UseHighDpiPixmaps);
    try{

            NotesManager& m=NotesManager::getInstance();

            RelationsManager<NoteHolder>* rm = new RelationsManager<NoteHolder>;

            MementoCaretaker& mainMemento=MementoCaretaker::getInstance();

            Database* db = new Database(m, *rm, "database.db");
            db->loadAll();

            MainWindow window(m, *rm, mainMemento, *db);

            window.show();

            return app.exec();
    }catch(AppException* ex){
        QMessageBox::critical(nullptr, "Erreur", ex->message);
    }

}
