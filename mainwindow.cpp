#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aff_juridique.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExp>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QSqlQuery>
#include <QPrinter>
#include"arduino.h"
#include <QSqlRecord>
#include "dialog.h"
#include "ui_dialog.h"
#include<QPieSeries>
#include <QFileDialog>
#include <QBarCategoryAxis>
#include<QDebug>
#include<QPrintDialog>
#include <QTextStream>
#include "calculatrice.h"
#include "avocat.h"
#include <QDesktopWidget>
#include <QSettings>
#include <QDataStream>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTextStream>
#include <QFile>

#include "salle.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
    ui->le_NUMAFF->setValidator(new QIntValidator(100, 999999, this));
    ui->mod_NUMAFF->setValidator(new QIntValidator(100, 999999, this));
    ui->num_supprimer->setValidator(new QIntValidator(0, 999999, this));
    QRegExp RX("^[A-C.]+$");
    QValidator* validatoR = new QRegExpValidator(RX, this);
    ui->le_TYPEAFF->setValidator(validatoR);
     ui->mod_TYPEAFF->setValidator(validatoR);
    QRegExp rx("^[a-zA-Z.]+$");
    QValidator* validator = new QRegExpValidator(rx, this);
    ui->l_AVOCAT->setValidator(validator);

    ui->le_JUGERES->setValidator(validator);

    ui->mod_AVOCAT->setValidator(validator);
    ui->mod_JUGERES->setValidator(validator);
    ui->tab_affaire->setModel(AFF.afficher());

    ui->l_AVOCAT->setModel(AFF.get_avocats("A"));
    ui->le_JUGERES->setModel(AFF.get_judges("A"));

    ui->mod_AVOCAT->setModel( AFF1.get_avocats("A"));
    ui->mod_JUGERES->setModel(AFF1.get_judges("A"));



    /*************************wejden***************************/
    ui->numero->setValidator( new QIntValidator(0,9999999,this));
        ui->comboBox_2->setValidator(new QRegExpValidator (QRegExp ("[A-Za-z]{0,255}"),this));
        ui->tab_RV->setModel(r.afficher());
         ui->numero_s->setValidator( new QIntValidator(0,9999999,this));

         ui->comboBox_2->addItem("Enligne");
          ui->comboBox_2->addItem("Presentiel");

    /*************************wejden***************************/
    /*************************** Arduino************************/


              int ret=A.connect_arduino(); // lancer la connexion Ã  arduino
              switch(ret){
              case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                  break;
              case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                 break;
              case(-1):qDebug() << "arduino is not available";
              }
               //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
               //le slot update_label suite Ã  la reception du signal readyRead (reception des donnÃ©es).



     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(rechEmploy()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rechEmploy()
{
    data.append(A.read_from_arduino());
QString ch= data.append(A.read_from_arduino());

     QSqlQueryModel *model=new QSqlQueryModel();

     model->setQuery("select * from AFF_JURIDIQUE where NUMAFF = '"+ch+"'");
     QSqlRecord sr = model->record(0);
     QString code= sr.value(3).toString();

if (code!=""){
QString  message="Numero : "+sr.value(0).toString()+"\nType Affaire : "+sr.value(1).toString()+"\nDate : "+sr.value(2).toString();
     QMessageBox::information(this,"Employee existant  " , message ,QMessageBox::Ok);



}
else {
    QMessageBox::critical(nullptr, QObject::tr("Employee n'existe pas"),
             QObject::tr("Employee n'existe pas.\n"
                         "click cancel to exit . ") , QMessageBox::Cancel);
}

}

/******************************************************/


void MainWindow::on_pb_ajouter_clicked()
{
    int NUMAFF=ui->le_NUMAFF->text().toInt();
    QString TYPEAFF=ui->le_TYPEAFF->currentText();
    QString DATEAFF=ui->le_DATEAFF->text();
    QString AVOCAT=ui->l_AVOCAT->currentText();
    QString JUGERES=ui->le_JUGERES->currentText();

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
    QString TYPEAFF=ui->mod_TYPEAFF->currentText();
    QString DATEAFF=ui->mod_DATEAFF->text();
    QString AVOCAT=ui->mod_AVOCAT->currentText();
    QString JUGERES=ui->mod_JUGERES->currentText();

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



void MainWindow::on_trier_date_clicked()
{
  ui->tab_affaire->setModel(AFF.trier_date());

}


void MainWindow::on_trier_type_clicked()
{
    ui->tab_affaire->setModel(AFF.trier_type());

}

/*void MainWindow::on_trier_avocat_clicked()
{
    ui->tab_affaire->setModel(AFF.trier_type());
}*/

void MainWindow::on_rechercher_clicked()
{
            int NUMAFF=ui->le_Rechercher->text().toInt();
            QString TYPEAFF=ui->le_Rechercher->text();
            QString DATEAFF=ui->le_Rechercher->text();
            QString AVOCAT=ui->le_Rechercher->text();
            QString JUGERES=ui->le_Rechercher->text();
ui->tab_affaire->setModel(AFF.rechercher(NUMAFF,TYPEAFF,DATEAFF,AVOCAT,JUGERES));


}

void MainWindow::on_pb_stat_clicked()
{
    Dialog d;
   d.statistique();
   d.exec();
}

//pdf : vous trouver le fichier dans le dossier build
void MainWindow::on_PDF_clicked()
{

QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tab_affaire->model()->rowCount();
            const int columnCount =ui->tab_affaire->model()->columnCount();


            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<h1>Liste Des Affaires</h1>"

                        "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_affaire->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab_affaire->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tab_affaire->isColumnHidden(column)) {
                               QString data = ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(row, column)).toString().simplified();
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
    printer.setOutputFileName("MYfile.pdf");
    document->print(&printer);}

void MainWindow::on_le_TYPEAFF_currentIndexChanged(int index)
{
    exp=ui->le_TYPEAFF->currentText();
    ui->l_AVOCAT->setModel( AFF.get_avocats(exp));
    ui->le_JUGERES->setModel(AFF.get_judges(exp));

}

void MainWindow::on_mod_TYPEAFF_currentIndexChanged(int indexx)
{
    exp_mod=ui->mod_TYPEAFF->currentText();
    ui->mod_AVOCAT->setModel( AFF1.get_avocats(exp_mod));
    ui->mod_JUGERES->setModel(AFF1.get_judges(exp_mod));

}


void MainWindow::on_recorder_clicked()
{
    QProcess *process = new QProcess(this);
    process->start(audio);
   /* ar= new audiorecorder();
    ar->show();
    */
}

void MainWindow::on_pushButton333_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_pushButton_5_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_pushButton_7_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}
/***********************************wejden**********************************************/
void MainWindow::on_pb_ajouter_2_clicked()
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
  QString ETAT =ui->ETAT->text();
    Rendezvous  r (NUMR,TYPER,ADRESSER,DATER,NUMS,NOMA,NOMC,TIME,ETAT);
    bool test =r.ajouter();
    if(test)
       { QMessageBox ::information(nullptr,QObject ::tr("ok"),QObject ::tr("ajout effectué .\n""click cancel to exit "),QMessageBox :: Cancel );
        ui->tab_RV->setModel(r.afficher());}
        else {
           QMessageBox :: information(nullptr,QObject::tr("ok"),QObject::tr("ajout echoué.\n""click cancel to exit" ),QMessageBox ::Cancel);
        }
}


void MainWindow::on_pb_supprimer_2_clicked()
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


void MainWindow::on_pb_modifier_2_clicked()
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
     QString ETAT = ui->ETAT->text();
    QString recherche=ui->numero->text();
    Rendezvous  r (NUMR,TYPER,ADRESSER,DATER,NUMS,NOMA,NOMC,TIME,ETAT);


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

void MainWindow::on_pushButton_8_clicked()
{
    Rendezvous m;
        if(ui->comboBox->currentIndex()==0){
            ui->recherche->setModel(m.triID());

        }
        else if (ui->comboBox->currentIndex()==1)
        {
            ui->recherche->setModel(m.triIDA());

        }
        else if(ui->comboBox->currentIndex()==2)
        {
            ui->recherche->setModel(m.triNomC());

        }

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
             ui->recherche->setModel(r1.rechercherIDA(recherche));


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
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste Des Rendez_Vous</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
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
        printer.setOutputFileName("Rendez-Vous.pdf");
        document->print(&printer);
}

void MainWindow::on_pushButton_5pdf2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->recherche->model()->rowCount();
                const int columnCount =ui->recherche->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste Des Rendez_Vous</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->recherche->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->recherche->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->recherche->isColumnHidden(column)) {
                                   QString data = ui->recherche->model()->data(ui->recherche->model()->index(row, column)).toString().simplified();
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
         ui->ETAT->setText(qry.value(9).toString());
}
   }
void MainWindow::on_photo_clicked()
    {
        QString picpath=QFileDialog::getOpenFileName(this,tr("Open file"),"c://","JPG File(.jpg);;PNG File(.png)");
        int numero=ui->id->text().toInt();
        QSqlQuery query;
        query.prepare("update TABLE1 set pic=:picpath where NUMR=:numero");
        query.bindValue(":picpath",picpath);
        query.bindValue(":numero",numero);
        query.exec();
    }

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
 //cout <<"wejden";
}


void MainWindow::on_pushButton_7_stat_clicked()
{

  Dialog d;
 d.afficher();
 d.exec();
}


/**************************************************************selim**********************************************/

void MainWindow::on_pushButton_14_clicked()
{
MainWindow w;
    QString ID=ui->lineEdit_id->text();
    QString NOMPRENOM=ui->lineEdit_nom->text();
   // QString SPEC=ui->lineEdit_spec->text();
     QString SPEC=ui->comboBox_spec->currentText();
    int PRIX=ui->lineEdit_prix->text().toInt();
    int NUM=ui->lineEdit_num->text().toInt();
    QString ADRESSE=ui->lineEdit_ad->text();
       QString EXP=ui->comboBox_exp->currentText();
            avocat c(ID,NOMPRENOM,SPEC,PRIX,NUM,ADRESSE, EXP);
           /* if (c.verif_id())
            {
            }*/
           bool test= c.ajouter();

               if(test){
               w.show();
               QMessageBox::information(nullptr, QObject::tr("database is open"),
                           QObject::tr("Ajout effectué.\n"
                                       "Click OK to exit."), QMessageBox::Ok);
            ui->tableView_aff->setModel(a.afficher());
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                           QObject::tr("Ajout non effectué.\n"
                                       "Click OK to exit."), QMessageBox::Ok);

               ui->lineEdit_id->clear();
               ui->lineEdit_ad->clear();

               ui->lineEdit_nom->clear();
               ui->lineEdit_num->clear();
               ui->lineEdit_prix->clear();


}

void MainWindow::on_pushButton_supprimer_clicked()
{ MainWindow w;
    avocat a; a.setID(ui->lineEdit_id->text());

 bool test=a.supprimer(a.get_ID());

     if(test){
     w.show();
     QMessageBox::information(nullptr, QObject::tr("database is open"),
                 QObject::tr("Supression effectué.\n"
                             "Click OK to exit."), QMessageBox::Ok);
             ui->tableView_aff->setModel(a.afficher());

 }
 else
     QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                 QObject::tr("Supressnion non effectué.\n"
                             "Click OK to exit."), QMessageBox::Ok);
     ui->lineEdit_id->clear();
     ui->lineEdit_ad->clear();

     ui->lineEdit_nom->clear();
     ui->lineEdit_num->clear();
     ui->lineEdit_prix->clear();

}
void MainWindow::on_pushButton_13_clicked()
{
    MainWindow w;
        avocat a;
        a.setID(ui->lineEdit_id->text());
        a.setnNOMPRENOM(ui->lineEdit_nom->text());
        /*if(a.get_NOMPRENOM()== "")
            cout << "egale" << endl;*/
       // a.setSPEC(ui->lineEdit_spec->text());
         //QString SPEC=ui->comboBox_spec->currentText();
        a.setSPEC(ui->comboBox_spec->currentText());
        a.setPRIX(ui->lineEdit_prix->text().toInt());
        a.setNUM(ui->lineEdit_num->text().toInt());
        a.setADRESSE(ui->lineEdit_ad->text());
 //QString EXP=ui->comboBox_exp->currentText();
       a.setEXP(ui->comboBox_exp->currentText());
                bool test=a.modifier(a.get_ID());
         if(test){
         w.show();
         QMessageBox::information(nullptr, QObject::tr("database is open"),
                     QObject::tr("Modification effectué.\n"
                                 "Click OK to exit."), QMessageBox::Ok);
                 ui->tableView_aff->setModel(a.afficher());

     }
         else{
         QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                     QObject::tr("Modification non effectué.\n"
                                 "Click OK to exit."), QMessageBox::Ok);}

         ui->lineEdit_id->clear();
         ui->lineEdit_ad->clear();

         ui->lineEdit_nom->clear();
         ui->lineEdit_num->clear();
         ui->lineEdit_prix->clear();

}
void MainWindow::on_pushButton_recherche_clicked()
{
    avocat M1;
        QString recherche = ui->lineEdit_rech->text();
        if(recherche.length()!=0)
    {
           //ui->tab_Mission->setModel(M1.rechercherType(recherche));
        // ui->tab_Mission->setModel(M1.rechercherID(recherche));
            if(ui->comboBox_rech->currentIndex()==0){
                ui->tableView_rech->setModel(M1.rech_nom(recherche));
               // ui->tab_Mission->setModel(m.triID());

            }
            else if (ui->comboBox_rech->currentIndex()==1)
            {
                 ui->tableView_rech->setModel(M1.rech_id(recherche));
               // ui->tab_Mission->setModel(m.triNBP());

            }
            else if(ui->comboBox_rech->currentIndex()==2)
            {
                ui->tableView_rech->setModel(M1.rech_spec(recherche));


        }
        else
        {
           ui->tableView_rech->setModel(M1.afficher());
        }
    }
   }
void MainWindow::on_pushButton_trprix_clicked()
{
    MainWindow w;
    avocat c;

         ui->tableView_tri->setModel(c.tri_prix());


}
void MainWindow::on_pushButton_trspec_clicked()
{
    MainWindow w;
    avocat c;

         ui->tableView_tri->setModel(c.tri_spec());


}
void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableView_aff->model()->rowCount();
                const int columnCount =ui->tableView_aff->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste des Avocats</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableView_aff->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableView_aff->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_aff->isColumnHidden(column)) {
                                   QString data = ui->tableView_aff->model()->data(ui->tableView_aff->model()->index(row, column)).toString().simplified();
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
        printer.setOutputFileName("Liste des Avocats.pdf");
        document->print(&printer);
}

void MainWindow::on_statboutton_2_clicked()
{
Dialog d;
d.stats();
d.exec();
}
void MainWindow::on_pushButton_calc_clicked()
{
   calculatrice c;
   c.exec();
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_ad->clear();

    ui->lineEdit_nom->clear();
    ui->lineEdit_num->clear();
    ui->lineEdit_prix->clear();



}
void MainWindow::affcherRendezvousArduino(){
    QString dateRDV,message;
    data = A.read_from_arduino();
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(data);
    if(data == "0"){
        A.write_to_arduino("n'existe pas");
    }
    else{
        QSqlQuery query,query1;
             query.prepare("select * from TABLE1 where NUMR =:NUMR ");
             query.bindValue(":NUMR", DataAsString);
             query.exec();
             while(query.next()){
                 dateRDV = query.value(3).toString();
                 if(query.value(9).toInt() == 0){
                     query1.prepare("update TABLE1 set ETAT =:ETAT");
                     query.bindValue(":ETAT","1");
                     message = dateRDV + "RVdone";
                 }
                 else{
                        message ="RV deja fait";
                     }
                 }
             A.write_to_arduino(message.toUtf8());
             }
}
/****************************************saadani*******************************************************************/



void MainWindow::on_Ajouterbutton_clicked()
{
    int id=ui->idedit->text().toInt() ; //recovery and converting to an integer
       QString nom=ui->nomedit->text();
        QString prenom=ui->prenomedit->text();// recovery of string
        int age=ui->ageedit->text().toInt();
       Citoyen C(id,nom,prenom,age);
       bool test=C.ajouter();
       if(test)
          {
           ui->tableview->setModel(Ctemp.afficher());
           ui->combosupp->setModel(Ctemp.get_id());
           A.write_to_arduino("1");
           QMessageBox::information(nullptr, QObject::tr("Ajouter espace"),
                       QObject::tr("Patient ajouter.\n""Click Cancel to exit."), QMessageBox::Cancel);
       }

       else

       {
           A.write_to_arduino("2");
           ui->tableview->setModel(Ctemp.afficher());
           ui->combosupp->setModel(Ctemp.get_id());
           QMessageBox::critical(nullptr, QObject::tr("not Ajouter espace"),
                       QObject::tr("Ajout echoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

       }
}

void MainWindow::on_Supprimerbutton_clicked()
{
    int ID = ui->combosupp->currentText().toInt();
           bool test=Ctemp.supprimer(ID);

        if(test)
           {
            ui->tableview->setModel(Ctemp.afficher());
            ui->combosupp->setModel(Ctemp.get_id());
            A.write_to_arduino("3");
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression effectuée.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }

        else

        {
            ui->tableview->setModel(Ctemp.afficher());
            ui->combosupp->setModel(Ctemp.get_id());
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Suppression echoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_Modifierbutton_clicked()
{
    int ID = ui->oldid->text().toInt();
            QString nom= ui->nommod->text();
            QString prenom= ui->prenommod->text();
int age = ui->oldage->text().toInt();
           Citoyen C(ID,nom,prenom,age);
             bool test = C.update(ID);


                if(test)

                {

                    ui->tableview->setModel(Ctemp.afficher());
                     ui->combosupp->setModel(Ctemp.get_id());

                    QMessageBox::information(nullptr, QObject::tr("EQUIPEMENT modifie"),
                                QObject::tr("EQUIPEMENT modifie\n"
                "Click Cancel to exit."), QMessageBox::Cancel);}

                else

                {
                    ui->tableview->setModel(Ctemp.afficher());
                    ui->combosupp->setModel(Ctemp.get_id());
                    QMessageBox::critical(nullptr, QObject::tr("not modifier"),
                                QObject::tr("not modified.\n""Click Cancel to exit."), QMessageBox::Cancel);

                }

                foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                        widget->clear();
                    }
}

void MainWindow::on_tableview_activated(const QModelIndex &index)
{
    QString id=ui->tableview->model()->data(index).toString();
         QSqlQuery query;
         query.prepare("SELECT * FROM CITOYEN WHERE ID= :ID");
         query.bindValue(":ID",id);
         if(query.exec()){
             while(query.next()){
                  ui->oldid->setText(query.value(0).toString());
                 ui->oldnom->setText(query.value(1).toString());
                 ui->oldprenom->setText(query.value(2).toString());
                 ui->oldage->setText(query.value(3).toString());

             }
         }
}

void MainWindow::on_sortid_clicked()
{
   ui->tableview->setModel(Ctemp.trierid());
}

void MainWindow::on_saadeni_stat_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableview->model()->rowCount();
                const int columnCount =ui->tableview->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste Des Citoyens</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableview->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableview->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableview->isColumnHidden(column)) {
                                   QString data = ui->tableview->model()->data(ui->tableview->model()->index(row, column)).toString().simplified();
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
        printer.setOutputFileName("Citoyens.pdf");
        document->print(&printer);
}

void MainWindow::on_rechercher_2_clicked()
{
    QString id1=ui->searsh->text();

         ui->tableview->setModel(Ctemp.rechercher(id1));
}

void MainWindow::on_statbouton_clicked()
{
    QSqlQuery query,query1,query2,query3;
                qreal c1=0 ,sum=0,c2=0,c3=0;
                query.prepare("SELECT * FROM employe") ;
                query.exec();
                while(query.next())
                {
                        sum++ ;
                }

                query1.prepare("SELECT * FROM employe where age >25 and age<35") ;
                query1.exec();
                while(query1.next())
                {
                        c1++ ;
                }

                query2.prepare("SELECT * FROM employe where age >35 and age<45 ") ;
                query2.exec();
                while(query2.next())
                {
                        c2++ ;
                }

                query3.prepare("SELECT * FROM employe where age >45") ;
                query3.exec();
                while(query3.next())
                {
                        c3++ ;
                }

            qreal d1,d2,d3;
            d1=(c1/sum)*100;
            d2=(c1/sum)*100;
            d3=(c1/sum)*100;
                QBarSet *set1 = new QBarSet("age>25");
                QBarSet *set2 = new QBarSet("age>35");
                QBarSet *set3 = new QBarSet("age>45");


                // Assign values for each bar
                 *set1 << d1 ;
                 *set2 << d2 ;
                 *set3 << d3 ;


                // Add all sets of data to the chart as a whole
                // 1. Bar Chart
                QBarSeries *series = new QBarSeries();

                // 2. Stacked bar chart
                // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

                series->append(set1);
                series->append(set2);
                series->append(set3);


                // Used to define the bar chart to display, title
                // legend,
                QChart *chart = new QChart();

                // Add the chart
                chart->addSeries(series);

                // Set title
                chart->setTitle("STATISTIQUE");

                // Define starting animation
                // NoAnimation, GridAxisAnimations, SeriesAnimations
                chart->setAnimationOptions(QChart::SeriesAnimations);

                // Holds the category titles
                QStringList categories;
                categories << "stats";

                // Adds categories to the axes
                QBarCategoryAxis *axis = new QBarCategoryAxis();
                axis->append(categories);
                chart->addAxis(axis, Qt::AlignBottom);
                series->attachAxis(axis);
                chart->createDefaultAxes();


                // 2. Stacked Bar chart

                // Define where the legend is displayed
                chart->legend()->setVisible(true);
                chart->legend()->setAlignment(Qt::AlignBottom);


                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);

                 chartView->setMinimumSize(621,192);
                chartView->setParent(ui->tableaustat);
                chart->setTheme(QChart::ChartThemeBlueIcy);
                chartView->show();

}
/**********************************************bilel***********************************************************/

void MainWindow::on_pushButton_15_clicked()
{
MainWindow w;
    int NBSALLE=ui->lineEdit_NBsalle->text().toInt();
    QString ETAT=ui->comboBox_etat->currentText();
    int CAPACITE=ui->lineEdit_Capacite->text().toInt();

            Salle c(NBSALLE,ETAT,CAPACITE);
           bool test= c.ajouter();

               if(test){
               w.show();
               QMessageBox::information(nullptr, QObject::tr("database is open"),
                           QObject::tr("Ajout effectué.\n"
                                       "Click OK to exit."), QMessageBox::Ok);
            ui->tableView_aff_2->setModel(c.afficher());
           }
           else
               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                           QObject::tr("Ajout non effectué.\n"
                                       "Click OK to exit."), QMessageBox::Ok);

}


void MainWindow::on_pushButton_supprimer_2_clicked()
{ MainWindow w;
    Salle a; a.setNBSALLE(ui->lineEdit_NBsalle->text().toUInt());

 bool test=a.supprimer(a.getNBSALLE());

     if(test){
     w.show();
     QMessageBox::information(nullptr, QObject::tr("database is open"),
                 QObject::tr("Supression effectué.\n"
                             "Click OK to exit."), QMessageBox::Ok);
             ui->tableView_aff_2->setModel(a.afficher());

 }
 else
     QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                 QObject::tr("Supressnion non effectué.\n"
                             "Click OK to exit."), QMessageBox::Ok);
}

void MainWindow::on_pushButton_12_clicked()
{
    MainWindow w;
        Salle a;
        a.setNBSALLE(ui->lineEdit_NBsalle->text().toUInt());
        a.setETAT(ui->comboBox_etat->currentText());
        a.setCAPACITE(ui->lineEdit_Capacite->text().toUInt());


                bool test=a.modifier(a.getNBSALLE());

         if(test){
         w.show();
         QMessageBox::information(nullptr, QObject::tr("database is open"),
                     QObject::tr("Modification effectué.\n"
                                 "Click OK to exit."), QMessageBox::Ok);
                 ui->tableView_aff_2->setModel(a.afficher());

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                     QObject::tr("Modification non effectué.\n"
                                 "Click OK to exit."), QMessageBox::Ok);
}

void MainWindow::on_pushButton_21_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tableView_aff_2->model()->rowCount();
                    const int columnCount =ui->tableView_aff_2->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Salles</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView_aff_2->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView_aff_2->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tableView_aff_2->isColumnHidden(column)) {
                                       QString data = ui->tableView_aff_2->model()->data(ui->tableView_aff_2->model()->index(row, column)).toString().simplified();
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
            printer.setOutputFileName("bilelfile.pdf");
            document->print(&printer);

}

void MainWindow::on_pushButton_pdftri_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tableView_tri_2->model()->rowCount();
                    const int columnCount =ui->tableView_tri_2->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Salles</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView_tri_2->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView_tri_2->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tableView_tri_2->isColumnHidden(column)) {
                                       QString data = ui->tableView_tri_2->model()->data(ui->tableView_tri_2->model()->index(row, column)).toString().simplified();
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
            printer.setOutputFileName("bilelfiletri.pdf");
            document->print(&printer);

}

void MainWindow::on_pushButton_19_clicked()
{
    MainWindow w;
        Salle s;

             ui->tableView_tri_2->setModel(s.tri_etat());
}

void MainWindow::on_pushButton_20_clicked()
{
    MainWindow w;
        Salle s;

             ui->tableView_tri_2->setModel(s.tri_cap());
}
void MainWindow::on_pushButton_rech_clicked()
{
    Salle S;
           QString recherche = ui->lineEdit_rech_2->text();
           if(recherche.length()!=0)
       {

               if(ui->comboBox_rech_2->currentIndex()==0){
                   ui->tableView_rech_2->setModel(S.recherche_nbsalle(recherche));


               }
               else if (ui->comboBox_rech_2->currentIndex()==1)
               {
                    ui->tableView_rech_2->setModel(S.recherche_etat(recherche));

               }
               else if(ui->comboBox_rech_2->currentIndex()==2)
               {
                   ui->tableView_rech_2->setModel(S.recherche_cap(recherche));


           }
           else
           {
              ui->tableView_rech_2->setModel(S.afficher());
           }
       }
}

void MainWindow::on_pushButton_77_clicked()
{
    Dialog d;
    d.sttat();
    d.exec();
}
