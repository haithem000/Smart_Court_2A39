#include "login.h"
#include "ui_login.h"
#include"employee.h"
#include"employee.cpp"
#include "mainwindow.h"
#include"mainwindow.cpp"
#include <QtDebug>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
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

login::~login()
{
    delete ui;
}
void login::rechEmploy()
{
    data.append(A.read_from_arduino());
QString ch= data.append(A.read_from_arduino());

     QSqlQueryModel *model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM EMPLOYE where ID LIKE  = '"+ch+"'");

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



void login::on_pushButton_clicked()
{
    login l;
    MainWindow *app;
    Employee e;
    app=new MainWindow();
    QString MAIL=ui->le_mail->text();
    QString MOTDEPASSE=ui->le_motdepasse->text();
    if (e.rechercher_MAIL(MAIL,MOTDEPASSE)->rowCount()!=0)
    {
        app->show();
        this->close();
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                          QObject::tr("ACCES IMPOSSIBLE"), QMessageBox::Cancel);
    }
}

void login::on_pushButton_2_clicked()
{
    A.write_to_arduino("1");
}
