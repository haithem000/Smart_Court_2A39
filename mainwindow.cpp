#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include<QIntValidator>
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExp>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QSqlQuery>
#include <QPrinter>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0, 99999999, this));
ui->tab_employee->setModel(E.afficher());

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
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pb_ajouter_clicked()


{
int ID=ui->le_id->text().toInt();
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
            QString MAIL=ui->le_mail->text();

            int MOTDEPASSE=ui->le_motdepasse->text().toInt();
            QString ADRESSE=ui->l_adresse->text();

    Employee E(ID,NOM,PRENOM,MAIL,MOTDEPASSE,ADRESSE);
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
      {  msgBox.setText("ajout avec succes");
    ui->tab_employee->setModel(E.afficher());}

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


void MainWindow::on_pb_supprimer_clicked()
{
    Employee E1; E1.setID(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getID());
    QMessageBox msgBox;
    if(test){
    msgBox.setText("suppression avec succes");
    ui->tab_employee->setModel(E.afficher());}

    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}
void MainWindow::on_pb_modifier_clicked()
{
    int ID=ui->mod_ID->text().toInt();
    QString NOM=ui->mod_NOM->text();
    QString PRENOM=ui->mod_PRENOM->text();
    QString MAIL=ui->mod_MAIL->text();
    int MOTDEPASSE=ui->mod_MOTDEPASSE->text().toInt();

    QString ADRESSE=ui->mod_ADRESSE->text();

    Employee E(ID,NOM,PRENOM,MAIL,MOTDEPASSE,ADRESSE);


    bool test=E.modifier(ID);
        if(test)
        {
            //refrech
            ui->tab_employee->setModel(E.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Modification avec succes.\n" "Click Close to exit."), QMessageBox::Close);
    }else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("Modification echoue.\n" "Click Close to exit."), QMessageBox::Close);
}


void MainWindow::on_recherche_clicked()
{
     ui->tab_employee->setModel(E.recherche());
}

void MainWindow::on_tri_clicked()
{
  ui->tab_employee->setModel(E.tri());

}


void MainWindow::on_Pdf_clicked()
{

QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tab_employee->model()->rowCount();
            const int columnCount =ui->tab_employee->model()->columnCount();


            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<h1>Liste Des Employes</h1>"

                        "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_employee->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab_employee->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tab_employee->isColumnHidden(column)) {
                               QString data = ui->tab_employee->model()->data(ui->tab_employee->model()->index(row, column)).toString().simplified();
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
    printer.setOutputFileName("test.pdf");
    document->print(&printer);}
void MainWindow::update_label()
{
    data=A.read_from_arduino();
            if(data=="1")
            ui->label_7->setText("porte ouverte");
            else

            if (data=="0")
            ui->label_7->setText("porte fermee");

}

void MainWindow::on_pb_modifier_2_clicked()
{
    A.write_to_arduino("1");

}

void MainWindow::on_pb_modifier_3_clicked()
{
    A.write_to_arduino("0");

}




