<<<<<<< Updated upstream
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include"rendezvous.h"
#include<QMessageBox>
#include<QObject>
#include <QIntValidator>
#include<iostream>
#include <QPrinter>
#include <QTextStream>
#include<QPrintDialog>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QSqlQuery>
#include <QchartView>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include<QDebug>
#include <QFileDialog>
#include<QPieSeries>
#include "dialog.h"
#include "ui_dialog.h"
#include "excel.h"
#include <QFileDialog>

using namespace std ;
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->numero->setValidator( new QIntValidator(0,9999999,this));
    ui->comboBox_2->setValidator(new QRegExpValidator (QRegExp ("[A-Za-z]{0,255}"),this));
    ui->tab_RV->setModel(r.afficher());
     ui->numero_s->setValidator( new QIntValidator(0,9999999,this));

     ui->comboBox_2->addItem("Enligne");
      ui->comboBox_2->addItem("Presentiel");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int NUMR = ui->numero->text().toInt();
    int NUMS =ui->numero_s->text().toInt();
    QString NOMA=ui->nom_a->text();
    QString NOMC =ui->nom_c->text();
   QString TYPER = ui->comboBox_2->currentText();
    QString ADRESSER =ui->adresse->text();
    QString TIME =ui->timeEdit->time().toString("hh:mm");
    //QString DATER =ui->date->text();
    QString DATER=ui->dateEdit->date().toString("dd.MM.yyyy");
    Rendezvous  r (NUMR,TYPER,ADRESSER,DATER,NUMS,NOMA,NOMC,TIME);
    bool test =r.ajouter();
    if(test)
       { QMessageBox ::information(nullptr,QObject ::tr("ok"),QObject ::tr("ajout effectué .\n""click cancel to exit "),QMessageBox :: Cancel );
        ui->tab_RV->setModel(r.afficher());}
        else {
           QMessageBox :: information(nullptr,QObject::tr("ok"),QObject::tr("ajout echoué.\n""click cancel to exit" ),QMessageBox ::Cancel);
        }
}


void MainWindow::on_pb_supprimer_clicked()
{
   // Rendezvous r; r.setnumr(ui->numero->text().toInt());
    //QString recherche=ui->numero->text();
   int id=ui->numero->text().toInt();
      QString recherche=ui->numero->text();

     if (r.rechercherID(recherche)->rowCount()!=0 and recherche.length()!=0)
     {
         bool test=r.supprimer(id);
        QMessageBox::information(nullptr, QObject::tr("Succès"),
     QObject::tr("Suppression effectué.\n"
       "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
       }
       else
           {QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                 QObject::tr("Suppression non effectué !\n"
                                   "Cliquer sur Cancel to exit."), QMessageBox::Cancel);}

     ui->tab_RV->setModel(r.afficher());



}



void MainWindow::on_pb_modifier_clicked()
{
   int NUMR = ui->numero->text().toInt();
   int NUMS =ui->numero_s->text().toInt();
   QString NOMA=ui->nom_a->text();
   QString NOMC =ui->nom_c->text();
    QString TYPER = ui->comboBox_2->currentText();
    QString ADRESSER =ui->adresse->text();
   // QString DATER =ui->dateEdit->text();
    QString DATER=ui->dateEdit->date().toString("dd.MM.yyyy");
    //QString TIME =ui->timeEdit->text();
     QString TIME =ui->timeEdit->time().toString("hh:mm");
    QString recherche=ui->numero->text();
    Rendezvous  r (NUMR,TYPER,ADRESSER,DATER,NUMS,NOMA,NOMC,TIME);


    if (r.rechercherID(recherche)->rowCount()!=0 and recherche.length()!=0)
    {
                bool test= r.modifier(NUMR);
                               if(test){
                                   MainWindow w;
                               w.show();
                               QMessageBox::information(nullptr, QObject::tr("database is open"),
                                           QObject::tr("Modification effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
                                  ui->tab_RV->setModel(r.afficher());
                           }
                           else
                               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                           QObject::tr("Modification non effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                   QObject::tr("Modification non effectué !\n"
                     "Cliquer sur Cancel to exit."), QMessageBox::Cancel);}


    ui->tab_RV->setModel(r.afficher());
     }





void MainWindow::on_pushButton_9_clicked()
{

    Rendezvous r1;
    QString recherche = ui->typeac->text();
    if(recherche.length()!=0)
{

        if(ui->comboBox_3_re->currentIndex()==0){
            ui->recherche->setModel(r1.rechercherID(recherche));

        }
        else if (ui->comboBox_3_re->currentIndex()==1)
        {
             ui->recherche->setModel(r1.recherchernoma(recherche));


        }
        else if(ui->comboBox_3_re->currentIndex()==2)
        {
            ui->recherche->setModel(r1.recherchernomc(recherche));


    }
    else
    {
       ui->recherche->setModel(r1.afficher());
    }
}
}

void MainWindow::on_pushButton_clicked()
{
    Rendezvous m;
        if(ui->comboBox->currentIndex()==0){
            ui->tableView->setModel(m.triID());

        }
        else if (ui->comboBox->currentIndex()==1)
        {
            ui->tableView->setModel(m.triNom());

        }
        else if(ui->comboBox->currentIndex()==2)
        {
            ui->tableView->setModel(m.triNomC());

        }
        else
            cout << "no combobox" << endl;
}






void MainWindow::on_pushButton_4pdf1_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_RV->model()->rowCount();
                const int columnCount =ui->tab_RV->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#FDFEFE link=#5000A0>\n"
                            "<h1>Liste de Rendez_vous</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#F5B7B1>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_RV->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_RV->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_RV->isColumnHidden(column)) {
                                   QString data = ui->tab_RV->model()->data(ui->tab_RV->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Rendez_vous.pdf");
        document->print(&printer);
}

void MainWindow::on_pushButton_5pdf2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView->model()->rowCount();
                const int columnCount =ui->tableView->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#FDFEFE link=#5000A0>\n"
                            "<h1>Liste de RV</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#F5B7B1>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView->isColumnHidden(column)) {
                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Liste trié.pdf");
        document->print(&printer);
}



void MainWindow::on_pushButton_7_stat_clicked()
{

  Dialog d;
 d.afficher();
 d.exec();
}



    //button upload
    void MainWindow::on_photo_clicked()
    {
        QString picpath=QFileDialog::getOpenFileName(this,tr("Open file"),"c://","JPG File(*.jpg);;PNG File(*.png)");
        int numero=ui->id->text().toInt();
        QSqlQuery query;
        query.prepare("update TABLE1 set pic=:picpath where NUMR=:numero");
        query.bindValue(":picpath",picpath);
        query.bindValue(":numero",numero);
        query.exec();
    }
    //images de ajout
    void MainWindow::on_aff_clicked()
    {
        QSqlQuery qry;
        int numero=ui->id->text().toInt();
        qry.prepare("select * from TABLE1 where NUMR=:numero");
        qry.bindValue(":numero",numero);
        if(qry.exec())
        {
            while(qry.next())
            {   QMessageBox ::information(nullptr,QObject ::tr("ok"),QObject ::tr("Upload  effectué .\n""click cancel to exit "),QMessageBox :: Cancel );
                QPixmap photo;
                QString location=qry.value(8).toString();
                photo.load(location);
                ui->pic->setPixmap(photo);
                ui->pic->setScaledContents(true);

            }
          // QMessageBox :: information(nullptr,QObject::tr(" not ok"),QObject::tr("Rendez_vous n'existe pas.\n""click cancel to exit" ),QMessageBox ::Cancel);

        }
              else  QMessageBox :: information(nullptr,QObject::tr(" not ok"),QObject::tr("Rendez_vous n'existe pas.\n""click cancel to exit" ),QMessageBox ::Cancel);
       // else {QMessageBox :: information(nullptr,QObject::tr(" not ok"),QObject::tr("Rendez_vous n'existe pas.\n""click cancel to exit" ),QMessageBox ::Cancel);
 cout <<"wejden";
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

   Excel obj(fileName, "mydata", ui->tab_RV);

    //colums to export
    obj.addField(0, "IDENTIFIANT", "char(20)");
    obj.addField(1, "TYPE", "char(20)");
    obj.addField(2, "ADRESSE", "char(20)");
    obj.addField(3, "DATE", "char(20)");
    obj.addField(4, "NUMERO DE SALLE", "char(20)");
    obj.addField(5, "NOM AVOCAT", "char(20)");
    obj.addField(6, "NOM CITOYEN", "char(20)");
    obj.addField(7, "TIME", "char(20)");
    obj.addField(8, "PICTURE", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    Rendezvous r;

        qInfo()<<date;

               ui->calendrier->setModel(r.recherche_DATED(date));
}

void MainWindow::on_calendrier_activated(const QModelIndex &index)
{
    QString val=ui->calendrier->model()->data(index).toString();

   QSqlQuery qry;
   qry.prepare("select * FROM TABLE1 where NUMR=:numero" );
   qry.bindValue(":numero",val);
   if(qry.exec())

       while (qry.next())


   {
      ui->numero->setText(qry.value(0).toString());//supprimer
       ui->adresse->setText(qry.value(2).toString());
       ui->numero_s->setText(qry.value(4).toString());
       ui->nom_a->setText(qry.value(5).toString());
       ui->nom_c->setText(qry.value(6).toString());
}
       }
=======
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include"rendezvous.h"
#include<QMessageBox>
#include<QObject>
#include <QIntValidator>
#include<iostream>
#include <QPrinter>
#include <QTextStream>
#include<QPrintDialog>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QSqlQuery>
#include <QchartView>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include<QDebug>
#include <QFileDialog>
#include<QPieSeries>
#include "dialog.h"
#include "ui_dialog.h"
#include "excel.h"
#include <QFileDialog>

using namespace std ;
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->numero->setValidator( new QIntValidator(0,9999999,this));
    ui->comboBox_2->setValidator(new QRegExpValidator (QRegExp ("[A-Za-z]{0,255}"),this));
    ui->tab_RV->setModel(r.afficher());
     ui->numero_s->setValidator( new QIntValidator(0,9999999,this));

     ui->comboBox_2->addItem("Enligne");
      ui->comboBox_2->addItem("Presentiel");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int NUMR = ui->numero->text().toInt();
    int NUMS =ui->numero_s->text().toInt();
    QString NOMA=ui->nom_a->text();
    QString NOMC =ui->nom_c->text();
   QString TYPER = ui->comboBox_2->currentText();
    QString ADRESSER =ui->adresse->text();
    QString TIME =ui->timeEdit->time().toString("hh:mm");
    //QString DATER =ui->date->text();
    QString DATER=ui->dateEdit->date().toString("dd.MM.yyyy");
    Rendezvous  r (NUMR,TYPER,ADRESSER,DATER,NUMS,NOMA,NOMC,TIME);
    bool test =r.ajouter();
    if(test)
       { QMessageBox ::information(nullptr,QObject ::tr("ok"),QObject ::tr("ajout effectué .\n""click cancel to exit "),QMessageBox :: Cancel );
        ui->tab_RV->setModel(r.afficher());}
        else {
           QMessageBox :: information(nullptr,QObject::tr("ok"),QObject::tr("ajout echoué.\n""click cancel to exit" ),QMessageBox ::Cancel);
        }
}


void MainWindow::on_pb_supprimer_clicked()
{
   // Rendezvous r; r.setnumr(ui->numero->text().toInt());
    //QString recherche=ui->numero->text();
   int id=ui->numero->text().toInt();
      QString recherche=ui->numero->text();

     if (r.rechercherID(recherche)->rowCount()!=0 and recherche.length()!=0)
     {
         bool test=r.supprimer(id);
        QMessageBox::information(nullptr, QObject::tr("Succès"),
     QObject::tr("Suppression effectué.\n"
       "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
       }
       else
           {QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                 QObject::tr("Suppression non effectué !\n"
                                   "Cliquer sur Cancel to exit."), QMessageBox::Cancel);}

     ui->tab_RV->setModel(r.afficher());



}



void MainWindow::on_pb_modifier_clicked()
{
   int NUMR = ui->numero->text().toInt();
   int NUMS =ui->numero_s->text().toInt();
   QString NOMA=ui->nom_a->text();
   QString NOMC =ui->nom_c->text();
    QString TYPER = ui->comboBox_2->currentText();
    QString ADRESSER =ui->adresse->text();
   // QString DATER =ui->dateEdit->text();
    QString DATER=ui->dateEdit->date().toString("dd.MM.yyyy");
    //QString TIME =ui->timeEdit->text();
     QString TIME =ui->timeEdit->time().toString("hh:mm");
    QString recherche=ui->numero->text();
    Rendezvous  r (NUMR,TYPER,ADRESSER,DATER,NUMS,NOMA,NOMC,TIME);


    if (r.rechercherID(recherche)->rowCount()!=0 and recherche.length()!=0)
    {
                bool test= r.modifier(NUMR);
                               if(test){
                                   MainWindow w;
                               w.show();
                               QMessageBox::information(nullptr, QObject::tr("database is open"),
                                           QObject::tr("Modification effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
                                  ui->tab_RV->setModel(r.afficher());
                           }
                           else
                               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                           QObject::tr("Modification non effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                   QObject::tr("Modification non effectué !\n"
                     "Cliquer sur Cancel to exit."), QMessageBox::Cancel);}


    ui->tab_RV->setModel(r.afficher());
     }





void MainWindow::on_pushButton_9_clicked()
{

    Rendezvous r1;
    QString recherche = ui->typeac->text();
    if(recherche.length()!=0)
{

        if(ui->comboBox_3_re->currentIndex()==0){
            ui->recherche->setModel(r1.rechercherID(recherche));

        }
        else if (ui->comboBox_3_re->currentIndex()==1)
        {
             ui->recherche->setModel(r1.recherchernoma(recherche));


        }
        else if(ui->comboBox_3_re->currentIndex()==2)
        {
            ui->recherche->setModel(r1.recherchernomc(recherche));


    }
    else
    {
       ui->recherche->setModel(r1.afficher());
    }
}
}

void MainWindow::on_pushButton_clicked()
{
    Rendezvous m;
        if(ui->comboBox->currentIndex()==0){
            ui->tableView->setModel(m.triID());

        }
        else if (ui->comboBox->currentIndex()==1)
        {
            ui->tableView->setModel(m.triNom());

        }
        else if(ui->comboBox->currentIndex()==2)
        {
            ui->tableView->setModel(m.triNomC());

        }
        else
            cout << "no combobox" << endl;
}






void MainWindow::on_pushButton_4pdf1_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_RV->model()->rowCount();
                const int columnCount =ui->tab_RV->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#FDFEFE link=#5000A0>\n"
                            "<h1>Liste de Rendez_vous</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#F5B7B1>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_RV->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_RV->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_RV->isColumnHidden(column)) {
                                   QString data = ui->tab_RV->model()->data(ui->tab_RV->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Rendez_vous.pdf");
        document->print(&printer);
}

void MainWindow::on_pushButton_5pdf2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView->model()->rowCount();
                const int columnCount =ui->tableView->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#FDFEFE link=#5000A0>\n"
                            "<h1>Liste de RV</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#F5B7B1>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView->isColumnHidden(column)) {
                                   QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("Liste trié.pdf");
        document->print(&printer);
}



void MainWindow::on_pushButton_7_stat_clicked()
{

  Dialog d;
 d.afficher();
 d.exec();
}



    //button upload
    void MainWindow::on_photo_clicked()
    {
        QString picpath=QFileDialog::getOpenFileName(this,tr("Open file"),"c://","JPG File(*.jpg);;PNG File(*.png)");
        int numero=ui->id->text().toInt();
        QSqlQuery query;
        query.prepare("update TABLE1 set pic=:picpath where NUMR=:numero");
        query.bindValue(":picpath",picpath);
        query.bindValue(":numero",numero);
        query.exec();
    }
    //images de ajout
    void MainWindow::on_aff_clicked()
    {
        QSqlQuery qry;
        int numero=ui->id->text().toInt();
        qry.prepare("select * from TABLE1 where NUMR=:numero");
        qry.bindValue(":numero",numero);
        if(qry.exec())
        {
            while(qry.next())
            {   QMessageBox ::information(nullptr,QObject ::tr("ok"),QObject ::tr("Upload  effectué .\n""click cancel to exit "),QMessageBox :: Cancel );
                QPixmap photo;
                QString location=qry.value(8).toString();
                photo.load(location);
                ui->pic->setPixmap(photo);
                ui->pic->setScaledContents(true);

            }
          // QMessageBox :: information(nullptr,QObject::tr(" not ok"),QObject::tr("Rendez_vous n'existe pas.\n""click cancel to exit" ),QMessageBox ::Cancel);

        }
              else  QMessageBox :: information(nullptr,QObject::tr(" not ok"),QObject::tr("Rendez_vous n'existe pas.\n""click cancel to exit" ),QMessageBox ::Cancel);
       // else {QMessageBox :: information(nullptr,QObject::tr(" not ok"),QObject::tr("Rendez_vous n'existe pas.\n""click cancel to exit" ),QMessageBox ::Cancel);
 cout <<"wejden";
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

   Excel obj(fileName, "mydata", ui->tab_RV);

    //colums to export
    obj.addField(0, "IDENTIFIANT", "char(20)");
    obj.addField(1, "TYPE", "char(20)");
    obj.addField(2, "ADRESSE", "char(20)");
    obj.addField(3, "DATE", "char(20)");
    obj.addField(4, "NUMERO DE SALLE", "char(20)");
    obj.addField(5, "NOM AVOCAT", "char(20)");
    obj.addField(6, "NOM CITOYEN", "char(20)");
    obj.addField(7, "TIME", "char(20)");
    obj.addField(8, "PICTURE", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    Rendezvous r;

        qInfo()<<date;

               ui->calendrier->setModel(r.recherche_DATED(date));
}

void MainWindow::on_calendrier_activated(const QModelIndex &index)
{
    QString val=ui->calendrier->model()->data(index).toString();

   QSqlQuery qry;
   qry.prepare("select * FROM TABLE1 where NUMR=:numero" );
   qry.bindValue(":numero",val);
   if(qry.exec())

       while (qry.next())


   {
      ui->numero->setText(qry.value(0).toString());//supprimer
       ui->adresse->setText(qry.value(2).toString());
       ui->numero_s->setText(qry.value(4).toString());
       ui->nom_a->setText(qry.value(5).toString());
       ui->nom_c->setText(qry.value(6).toString());
}
       }
>>>>>>> Stashed changes
