#include "rendezvous.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QString>
#include <QDebug>
Rendezvous::Rendezvous()
{
NUMR=0;ADRESSER="";TYPER="";DATER="";NUMS=0;NOMA="";NOMC="";
}

Rendezvous::Rendezvous(int num, QString type , QString adresse, QString date,int nums,QString noma,QString nomc,QString time,QString ETAT)
{
    this->NUMR=num;
    this->TYPER=type;
    this->ADRESSER= adresse;
    this->DATER=date;
    this->NUMS=nums;
    this->NOMA=noma;
   this->NOMC=nomc;
    this->TIME=time;
    this->ETAT=ETAT;
}
bool Rendezvous:: ajouter ()
{


     QString NUMR_string= QString ::number(NUMR);
   QString NUMS_string= QString ::number(NUMS);
   //QString ETAT_string=QString ::number(ETAT);
     QSqlQuery query;
          query.prepare("INSERT INTO TABLE1 (NUMR,TYPER, ADRESSE, DATER,NUMS,NOMA,NOMC,TIME,ETAT) "
                        "VALUES (:NUMR, :TYPER, :ADRESSE,:DATER,:NUMS,:NOMA,:NOMC,:TIME,:ETAT)");
          query.bindValue(":NUMR", NUMR_string);
          query.bindValue(":TYPER", TYPER);
          query.bindValue(":ADRESSE", ADRESSER);
          query.bindValue(":DATER", DATER);
          query.bindValue(":NOMA", NOMA);
          query.bindValue(":NOMC", NOMC);
          query.bindValue(":NUMS", NUMS_string);
          query.bindValue(":TIME", TIME);
           query.bindValue(":ETAT", ETAT);
        return  query.exec();

}
bool Rendezvous::supprimer (int id)
{
    QSqlQuery query;
         query.prepare("delete from TABLE1 where NUMR=:NUMR");
         query.bindValue(":NUMR", id);

       return  query.exec();



}
QSqlQueryModel *Rendezvous::afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel;
         model->setQuery("SELECT* FROM TABLE1");
         model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Identefiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero de la salle"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nom d'avocat"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("Nom de citoyen "));
           model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
             model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));



    return model;
}
bool Rendezvous :: modifier(int NUMR)
{

    QString NUMR_string= QString ::number(NUMR);
     QString NUMS_string= QString ::number(NUMS);
    QSqlQuery query;
         query.prepare("UPDATE  TABLE1 SET NUMR=:NUMR,TYPER=:TYPER, ADRESSE=:ADRESSE, DATER=:DATER,NUMS=:NUMS,NOMA=:NOMA,NOMC=:NOMC where NUMR=:NUMR ") ;

         query.bindValue(":NUMR", NUMR_string);
         query.bindValue(":TYPER", TYPER);
         query.bindValue(":ADRESSE", ADRESSER);
         query.bindValue(":DATER", DATER);
         query.bindValue(":NOMA", NOMA);
         query.bindValue(":NOMC", NOMC);
         query.bindValue(":NUMS", NUMS_string);

       return  query.exec();
}
QSqlQueryModel* Rendezvous ::rechercherID(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM TABLE1 where NUMR LIKE '"+recherche+"%'  OR LOWER(NUMR) LIKE '"+recherche+"%' OR UPPER(NUMR) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPER"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATER"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUMS"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NOMA"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("NOMC"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
      model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));
    return model;
}
QSqlQueryModel* Rendezvous::rechercherIDA(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM TABLE1 where NOMA LIKE '"+recherche+"%'  OR LOWER(NOMA) LIKE '"+recherche+"%' OR UPPER(NOMA) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero de salle"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom d'avocat"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("nom de citoyen"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
      model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));
    return model;
}
QSqlQueryModel* Rendezvous::recherchernomc(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM TABLE1 where NOMC LIKE '"+recherche+"%'  OR LOWER(NOMC) LIKE '"+recherche+"%' OR UPPER(NOMC) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero de salle"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom d'avocat"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("nom de citoyen"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
      model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));
    return model;
}
QSqlQueryModel * Rendezvous::triID()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM TABLE1 order by NUMR");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero de salle"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom d'avocat"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("nom de citoyen"));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));
     return model;


}
QSqlQueryModel * Rendezvous::triIDA()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM TABLE1 order by NOMA");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero de salle"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom d'avocat"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("nom de citoyen"));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));
     return model;


}
QSqlQueryModel * Rendezvous::triNomC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM TABLE1 order by NOMC");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero de salle"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom d'avocat"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("nom de citoyen"));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("TIME "));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("PIC "));
     return model;


}
QSqlQueryModel * Rendezvous::recherche_DATED(QDate val)
{
    QString vall=val.toString("dd.MM.yyyy").toUpper();
        QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select * from TABLE1 where DATER LIKE '"+vall+"'");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse "));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero salle"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("nom avocat"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("nom citoyen"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("time"));
       model->setHeaderData(8,Qt::Horizontal,QObject::tr("picture"));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("ETAT"));


        return model;
}

