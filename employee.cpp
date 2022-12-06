#include "employee.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Employee::Employee()
{
ID=0; NOM=""; PRENOM="";MAIL="",MOTDEPASSE=0,ADRESSE="";
}
Employee::Employee(int ID,QString NOM,QString PRENOM,QString MAIL,int MOTDEPASSE,QString ADRESSE)
{this->ID=ID; this->NOM=NOM; this->PRENOM=PRENOM; this->MAIL=MAIL,this->MOTDEPASSE=MOTDEPASSE;this->ADRESSE=ADRESSE;}
int Employee::getID(){return ID;}
QString Employee::getNOM(){return NOM;}
QString Employee::getPRENOM(){return PRENOM;}
QString Employee::getMAIL(){return MAIL;}
int Employee::getMOTDEPASSE(){return MOTDEPASSE;}
QString Employee::getADRESSE(){return ADRESSE;}

void Employee::setID(int ID){this->ID=ID;}
void Employee::setNOM(QString NOM){this->NOM=NOM;}
void Employee::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void Employee::setMAIL(QString MAIL){this->MAIL=MAIL;}
void Employee::setMOTDEPASSE(int MOTDEPASSE){this->MOTDEPASSE=MOTDEPASSE;}
void Employee::setADRESSE(QString ADRESSE){this->ADRESSE=ADRESSE;}

bool Employee::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
    QString motdepasse_string=QString::number(MOTDEPASSE);

          query.prepare("INSERT INTO EMPLOYE (ID,NOM, PRENOM,MAIL,MOTDEPASSE,ADRESSE) "
                        "VALUES (:ID, :forename, :surname,:MAIL,:MOTDEPASSE,:ADRESSE)");
          query.bindValue(0,id_string);
          query.bindValue(1, NOM);
          query.bindValue(2, PRENOM);
          query.bindValue(3, MAIL);
          query.bindValue(4,motdepasse_string);
          query.bindValue(5,ADRESSE);



     return query.exec();

}
bool Employee::supprimer(int ID)
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
          query.prepare(" Delete from EMPLOYE where ID=:ID");
          query.bindValue(0,ID);



     return query.exec();

}
QSqlQueryModel* Employee::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel ();


          model->setQuery("SELECT* FROM EMPLOYE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal,QObject:: tr("MAIL"));
          model->setHeaderData(4, Qt::Horizontal,QObject:: tr("MOTDEPASSE"));
          model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ADRESSE"));



    return model;

}
bool Employee::modifier(int ID){
    QSqlQuery query;
   QString ID_string= QString::number(ID);

    //requette sql
    query.prepare("UPDATE EMPLOYE set NOM=:NOM,PRENOM=:PRENOM ,MAIL=:MAIL,MOTDEPASSE=:MOTDEPASSE,ADRESSE=:ADRESSE where ID=:ID");

    //saisir de donnee
    query.bindValue(":ID",ID_string);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":MAIL",MAIL);
    query.bindValue(":MOTDEPASSE",MOTDEPASSE);
    query.bindValue(":ADRESSE",ADRESSE);


    //execution de la requetteNU
    return query.exec();
}

QSqlQueryModel* Employee::recherche()
{
    QSqlQueryModel* model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE where MAIL LIKE 'm%'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
        model->setHeaderData(4, Qt::Horizontal,QObject:: tr("MOTDEPASSE"));
        model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ADRESSE"));


    return model;
}

QSqlQueryModel* Employee::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE order by NOM asc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("MOTDEPASSE"));
    model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ADRESSE"));


 return model;
}
QSqlQueryModel * Employee::rechercher_MAIL(QString recherche1, QString recherche2)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * FROM  EMPLOYE where MAIL LIKE '"+recherche1+"' and MOTDEPASSE like '"+recherche2+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("MOTDEPASSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(5, Qt::Horizontal,QObject:: tr("ADRESSE"));


    return model;

}
