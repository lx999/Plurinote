#include "imageinterface.h"

ImageInterface::ImageInterface(const Image& im, QWidget *parent): NoteInterface(parent), image(&im){
    layout=new QFormLayout;
    boutonLayout = new QHBoxLayout;
    bAddImage= new QPushButton(QString("Ajouter une image"));
    generate= new QPushButton(QString("Sauvegarder"));
    //bDeleteImage= new QPushButton(QString("Supprimer l'image"));
    //deletedImage=0;
    nameFileImage= new QString(image->getnameFile());
    idEdit= new QLineEdit(image->getIdentifier().toString(),this);
    idEdit->setReadOnly(1);
    activer=new QPushButton(QString("activer"));
    choisir=new QPushButton(QString("choisir"));
    supprimer=new QPushButton(QString("supprimer"));
    boxLayout=new QFormLayout;
    versions=new QComboBox;
    parcourir();

    titleEdit= new QLineEdit(image->getTitle(),this);
    descriptionEdit= new QTextEdit(image->getDescription(),this);

    // Espace pour l'image
    imageLabel = new QLabel("Pas d'image chargé");
    imageLabel->setAlignment(Qt::AlignCenter);
    //imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setAutoFillBackground(true);
    fitCheckBox = new QCheckBox("Fit to Window");
    QHBoxLayout* layoutImage = new QHBoxLayout;
    layoutImage->addStretch();
    layoutImage->addWidget(imageLabel);
    layoutImage->addStretch();
    imageLabel->setFixedSize(264,144);


    //ajustement de la taille des Widgets
    descriptionEdit->setFixedHeight(120);
    titleEdit->setFixedWidth(180);
    idEdit->setFixedWidth(300);

    // ajout des composants sur la layout
    layout->addRow("Identifiant :",idEdit);
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Description :",descriptionEdit);
    boutonLayout->addWidget(generate);
    boutonLayout->addWidget(bAddImage);
    //boutonLayout->addWidget(bDeleteImage);

    //gestion des Layouts
    mainLayout = new QVBoxLayout;
    if(image->getState()=="active"){
        boxLayout->addRow(versions);
        boxLayout->addRow(choisir);
        boxLayout->addRow(supprimer);
        mainLayout->addLayout(layout);
        mainLayout->addLayout(layoutImage);
        mainLayout->addWidget(fitCheckBox);
        mainLayout->addLayout(boutonLayout);
        mainLayout->addLayout(boxLayout);
    }else{
        titleEdit->setReadOnly(1);
        descriptionEdit->setReadOnly(1);
        boxLayout->addRow(activer);
        mainLayout->addLayout(layout);
        mainLayout->addLayout(layoutImage);
        mainLayout->addWidget(fitCheckBox);
        mainLayout->addLayout(boxLayout);
    }

    setLayout(mainLayout);
    setWindowTitle("Image");
    resize(400, 400);


    //Si déjà présence d'une image l'afficher directement!
    if(!(image->getImage().isNull())){
        //imageLabel->setPixmap(QPixmap::fromImage(image->getImage()).scaled(QSize(213,10)));
        imageLabel->setPixmap(QPixmap(*nameFileImage));
        //layout->addWidget(imageLabel);
        imageLabel->show();
        bAddImage->setEnabled(false);
    }

    //slot
    QObject::connect(bAddImage, SIGNAL(clicked()), this, SLOT(openImage()));
    QObject::connect(fitCheckBox, SIGNAL(clicked()), this, SLOT(fitToWindow()));
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(versions, SIGNAL(activated(int)), this, SLOT(enregistrerid(int)));
    QObject::connect(choisir, SIGNAL(clicked()), this, SLOT(charger()));
    //QObject::connect(activer, SIGNAL(clicked()), this, SLOT(charger()));
    //QObject::connect(bDeleteImage, SIGNAL(clicked()), this, SLOT(deleteImage()));

}




void ImageInterface::setNameFileImage(QString nameImage){
    nameFileImage=&nameImage;
}

//slot
void ImageInterface::openImage(){
    nameFileImage = new QString();
    *nameFileImage = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.bmp)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + *nameFileImage);
    //chargement de l'image sur l'interface graphique
    imageToRegister= new QImage(*nameFileImage);
    imageLabel->setPixmap(QPixmap(*nameFileImage));
    imageLabel->show();
    bAddImage->setEnabled(false);

}

void ImageInterface::fitToWindow(){
     imageLabel->setScaledContents(fitCheckBox->isChecked());
}

void ImageInterface::save(){
    Image* i = new Image(*image);
    i->setDescription(descriptionEdit->toPlainText());
    i->setTitle(titleEdit->text());
    i->setImage(*nameFileImage);

    image = i;
    emit newVersion(i); // signal d'émition pour la création d'une nouvelle version
    //QMessageBox::information(this, "Fichier", "Enregistrement :\n" +titleEdit->text()+"\n"+descriptionEdit->toPlainText() +"\n"+ *nameFileImage);
}

/* // si on souhaite pouvoir changer une image de la note (fonction que ne n'utilisons pas car c'est contraire au principe d'une note)
void ImageInterface::deleteImage(){
    delete imageLabel;
    //nameFileImage=0;
    setNameFileImage(nullptr);
    QMessageBox::information(this, "Fichier", "Vous avez supprimé :\n" + *nameFileImage);
    deletedImage=1;
    bAddImage->setEnabled(true);
}
*/

void ImageInterface::parcourir(){
    QSqlQuery q;
    q.exec("SELECT n.Id,n.Title,n.Edited FROM (Note n INNER JOIN Image a ON n.Id=a.Id) WHERE a.Idreal='"+ image->getIdentifier().toString()+"';");
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

void ImageInterface::charger(){
    QSqlQuery q;
    q.exec("SELECT n.Title,a.Description,a.File FROM Image a,Note n WHERE n.Id=a.Id AND a.Id='"+ QString::number(Id) +"';");
    q.next();
    Image* change=const_cast<Image*>(image);
    change->setTitle(q.value(0).toString());
    change->setDescription(q.value(1).toString());
    change->setImage(q.value(2).toString());
}

void ImageInterface::enregistrerid(int i){
    std::cout<<i;
    Id=a[i];
    std::cout<<Id;
}
