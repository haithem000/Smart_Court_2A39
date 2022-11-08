#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aff_juridique.h"
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_NUMAFF->setValidator(new QIntValidator(100, 99999999, this));


    ui->tab_affaire->setModel(AFF.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int NUMAFF=ui->le_NUMAFF->text().toInt();
    QString TYPEAFF=ui->le_TYPEAFF->text();
    QString DATEAFF=ui->le_DATEAFF->text();
    QString AVOCAT=ui->l_AVOCAT->text();
    QString JUGERES=ui->le_JUGERES->text();

   Aff_juridique AFF(NUMAFF,TYPEAFF,DATEAFF,AVOCAT,JUGERES);
   bool test;
   test=AFF.ajouter();
       QMessageBox msgBox;

       if(test)
       {msgBox.setText("ajout avec succes");
            ui->tab_affaire->setModel(AFF.afficher());
       }
       else msgBox.setText("Echec d'ajout");
       msgBox.exec();

}

void MainWindow::on_pb_supprimer_clicked()
{

    Aff_juridique AFF1;  AFF1.setNUMAFF(ui->num_supprimer->text().toInt());
    bool test=AFF1.supprimer(AFF1.getNUMAFF());

QMessageBox msgBox;
    if(test)
     {msgBox.setText("Suppression avec succes.");

        ui->tab_affaire->setModel(AFF.afficher());

    }
    else
        msgBox.setText("Echec de suppression.");

    msgBox.exec();

}

void MainWindow::on_pb_modifier_clicked()
{
    int NUMAFF=ui->mod_NUMAFF->text().toInt();
    QString TYPEAFF=ui->mod_TYPEAFF->text();
    QString DATEAFF=ui->mod_DATEAFF->text();
    QString AVOCAT=ui->mod_AVOCAT->text();
    QString JUGERES=ui->mod_JUGERES->text();

    Aff_juridique AFF(NUMAFF,TYPEAFF,DATEAFF,AVOCAT,JUGERES);

    bool test=AFF.modifier(NUMAFF);
        if(test)
        {
            //refrech
            ui->tab_affaire->setModel(AFF.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Modification avec succes.\n" "Click Close to exit."), QMessageBox::Close);
    }else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("Modification echoue.\n" "Click Close to exit."), QMessageBox::Close);
}



void MainWindow::on_trier_clicked()
{
    ui->tab_affaire->setModel(AFF.trier());
    bool test=AFF.trier();
        if(test)
        {
            //refrech
            ui->tab_affaire->setModel(AFF.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("tri avec succes.\n" "Click Close to exit."), QMessageBox::Close);
    }else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("tri echoue.\n" "Click Close to exit."), QMessageBox::Close);
}


void MainWindow::on_recherche_clicked()
{
    Aff_juridique *AFF = new Aff_juridique();
              ui->tab_affaire->setModel(AFF->rechercher());
              Aff_juridique AFF1;  AFF1.setNUMAFF(ui->num_recherche->text().toInt());

       bool test=AFF->rechercher();
           if(test)
           {
               //refrech
               ui->tab_affaire->setModel(AFF->afficher());
               QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("recherche avec succes.\n" "Click Close to exit."), QMessageBox::Close);
       }else
               QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("recherche echoue.\n" "Click Close to exit."), QMessageBox::Close);
}
