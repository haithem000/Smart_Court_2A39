#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aff_juridique.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExp>
#include <QPrinter>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_NUMAFF->setValidator(new QIntValidator(100, 999999, this));
    ui->mod_NUMAFF->setValidator(new QIntValidator(100, 999999, this));
    ui->num_supprimer->setValidator(new QIntValidator(0, 999999, this));


    QRegExp rx("^[a-zA-Z.]+$");
    QValidator* validator = new QRegExpValidator(rx, this);
    ui->l_AVOCAT->setValidator(validator);
    ui->le_TYPEAFF->setValidator(validator);
    ui->le_JUGERES->setValidator(validator);
    ui->mod_TYPEAFF->setValidator(validator);
    ui->mod_AVOCAT->setValidator(validator);
    ui->mod_JUGERES->setValidator(validator);

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

}

void MainWindow::on_rechercher_clicked()
{
              ui->tab_affaire->setModel(AFF.rechercher());
}

/*int stat_ressource::Statistique_partie2()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from RESSOURCE_TRAITEMENT where STOCK_T BETWEEN '1' AND '50'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}
int stat_ressource::Statistique_partie3()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from RESSOURCE_TRAITEMENT where STOCK_T BETWEEN '51' AND '150'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}
int stat_ressource::Statistique_partie4()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from RESSOURCE_TRAITEMENT where STOCK_T BETWEEN '151' AND '300'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;


}
void stat_ressource::paintEvent(QPaintEvent *)
{

    int b=Statistique_partie2();
    //cout<<b<<endl ;
    int c=Statistique_partie3();
   // cout<<c<<endl ;
    int d=Statistique_partie4();
    //cout<<d<<endl ;

        float s2= b*100 ;
        float s3=c*100;
        float nb = b+c+d ;
        float q2 ;
        q2 = s2/nb ;
        float q3;
        q3=s3/nb;
        float y  ;
        y = (q2*360)/100 ;
        float m;
        m= (q3*360)/100;
        float z  ;
        z=360-(y+m) ;
    QPainter painter(this);
    QRectF size=QRectF(50,50,this->width()-500,this->width()-500);

    painter.setBrush(Qt::red);
    painter.drawPie(size,0,16*y);
    ui->label_2->setText("10-50") ;
    painter.setBrush(Qt::green);
    painter.drawPie(size,16*y,16*m);
    ui->label_3->setText("51-100") ;
    painter.setBrush(Qt::blue);
    painter.drawPie(size,16*(m+y),16*z);
    ui->label_4->setText("101-9999") ;

}*/

//pdf : vous trouver le fichier dans le dossier build
int MainWindow::creerPDF()
{
    QPrinter printer;
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName("/miprimerpdf.pdf");
          QPainter painter;
          if (! painter.begin(&printer)) { // failed to open file
              qWarning("failed to open file, is it writable?");
              return 1;
          }
          painter.drawText(10, 10, "miprimerpdf");
          painter.drawText(10, 30, "hoja1");
          if (! printer.newPage()) {
              qWarning("failed in flushing page to disk, disk full?");
              return 1;
          }
          painter.drawText(10, 10, "hoja2");
          painter.end();
}
