#include "employee.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Employee::Employee()
{
ID=0; NOM=""; PRENOM="";MAIL="";
}
Employee::Employee(int ID,QString NOM,QString PRENOM,QString MAIL)
{this->ID=ID; this->NOM=NOM; this->PRENOM=PRENOM; this->MAIL=MAIL;}
int Employee::getID(){return ID;}
QString Employee::getNOM(){return NOM;}
QString Employee::getPRENOM(){return PRENOM;}
QString Employee::getMAIL(){return MAIL;}
void Employee::setID(int ID){this->ID=ID;}
void Employee::setNOM(QString NOM){this->NOM=NOM;}
void Employee::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void Employee::setMAIL(QString MAIL){this->MAIL=MAIL;}

bool Employee::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
          query.prepare("INSERT INTO TABLE1 (ID,NOM, PRENOM,MAIL) "
                        "VALUES (:ID, :forename, :surname,:MAIL)");
          query.bindValue(0,id_string);
          query.bindValue(1, NOM);
          query.bindValue(2, PRENOM);
          query.bindValue(3, MAIL);


     return query.exec();

}
bool Employee::supprimer(int ID)
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
          query.prepare(" Delete from TABLE1 where ID=:ID");
          query.bindValue(0,ID);



     return query.exec();

}
QSqlQueryModel* Employee::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel ();


          model->setQuery("SELECT* FROM TABLE1");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal,QObject:: tr("MAIL"));

    return model;

}
bool Employee::modifier(int ID){
    QSqlQuery query;
   QString ID_string= QString::number(ID);

    //requette sql
    query.prepare("UPDATE TABLE1 set NOM=:NOM,PRENOM=:PRENOM ,MAIL=:MAIL where ID=:ID");

    //saisir de donnee
    query.bindValue(":ID",ID_string);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":MAIL",MAIL);

    //execution de la requetteNU
    return query.exec();
}
