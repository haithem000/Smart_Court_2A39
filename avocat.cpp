#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avocat.h"
#include<QSqlQuery>
#include<QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include<QComboBox>
#include <QtCharts>
avocat::avocat()
{
ID="";
NOMPRENOM="";
SPEC="";
PRIX=0;
NUM=0;
ADRESSE="";
EXP="";
}

void avocat::setID(QString n){ID=n;}
void avocat::setnNOMPRENOM(QString n){NOMPRENOM=n;}
void avocat::setSPEC(QString n){SPEC=n;}
void avocat::setPRIX(int n){PRIX=n;}
void avocat::setNUM(int n){NUM=n;}
void avocat::setADRESSE(QString n){ADRESSE=n;}
void avocat::setEXP(QString n){EXP=n;}

QString avocat::get_ID(){return ID;}
QString avocat::get_NOMPRENOM(){return NOMPRENOM;}
QString avocat::get_SPEC(){return SPEC;}
int avocat::get_PRIX(){return PRIX;}
int avocat::get_NUM(){return NUM;}
QString avocat::get_ADRESSE(){return ADRESSE;}
QString avocat::get_EXP(){return EXP;}

avocat::avocat(QString ID, QString NOMPRENOM, QString SPEC, int PRIX, int NUM, QString ADRESSE, QString EXP)
{this->ID=ID, this->NOMPRENOM=NOMPRENOM, this->SPEC=SPEC, this->PRIX=PRIX, this->NUM=NUM, this->ADRESSE=ADRESSE, this->EXP=EXP;}

bool avocat::verif_id(){

 return ID.isEmpty();
}
bool avocat::verif_adr(){
  if (ADRESSE.contains("@",Qt::CaseSensitive)==false)
      return true ;
  else return false;

}
bool avocat::verif_nom(){
  return NOMPRENOM.isEmpty();
}
bool avocat::verif_num(){

if (NUM==0) return false;
else return true;
}
bool avocat::verif_spec(){
   return SPEC.isEmpty();
}
bool avocat::verif_prix(){

if (PRIX==0) return false;
else return true;
}


bool avocat::ajouter()
{
   QSqlQuery query;

        query.prepare("INSERT INTO AVOCAT (NOMPRENOM, ID, SPEC,PRIX, NUM, ADRESSE, EXP) "
                      "VALUES (:NOMPRENOM, :ID, :SPEC,:PRIX,:NUM, :ADRESSE, :EXP)");
        query.bindValue(":ID", ID);
        query.bindValue(":NOMPRENOM", NOMPRENOM);
        query.bindValue(":SPEC", SPEC);
        query.bindValue(":PRIX", PRIX);
        query.bindValue(":NUM", NUM);
        query.bindValue(":ADRESSE", ADRESSE);
         query.bindValue(":EXP", EXP);
        return query.exec();
}

QSqlQueryModel* avocat::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM AVOCAT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOMPRENOM"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("SPEC"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE"));
             model->setHeaderData(6, Qt::Horizontal, QObject::tr("EXP"));

return model;
}

bool avocat::supprimer(QString ID)
{
    QSqlQuery query;
         query.prepare("Delete from AVOCAT where ID=:ID");
         query.bindValue(":ID", ID);

         return query.exec();
}

bool avocat::modifier(QString ID)
{
    QSqlQuery query;
    query.prepare("UPDATE AVOCAT SET NOMPRENOM=:NOMPRENOM, SPEC=:SPEC, PRIX=:PRIX, NUM=:NUM, ADRESSE=:ADRESSE , EXP=:EXP where ID=:ID");
    query.bindValue(":ID",ID);
     query.bindValue(":NOMPRENOM", NOMPRENOM);
    query.bindValue(":SPEC", SPEC);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":NUM", NUM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":EXP", EXP);
    return query.exec();
}

/*QSqlQueryModel* avocat::afficher_recherche(QString ID)
{

    QSqlQueryModel* model2=new QSqlQueryModel();

          model2->setQuery("SELECT * FROM AVOCAT where ID LIKE '"+ID+"%' OR LOWER(ID) LIKE '"+ID+"%' OR (ID) LIKE '"+ID+"%' ");

          model2->setHeaderData(0, Qt::Horizontal, QObject::tr("NOMPRENOM"));
          model2->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
           model2->setHeaderData(2, Qt::Horizontal, QObject::tr("SPEC"));
            model2->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
            model2->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
            model2->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE"));


return model2;
}*/
QSqlQueryModel* avocat::rech_id(QString recherche)
{


        QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM AVOCAT where ID LIKE '"+recherche+"%'  OR LOWER(ID) LIKE '"+recherche+"%' OR UPPER(ID) LIKE '"+recherche+"%'");
       /* model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DEBUT_M"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NBR_DE_PERSONES"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESTINATION"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_FIN_M"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("TYPE_DE_MISSION"));*/
        return model;
    }

QSqlQueryModel* avocat::rech_spec(QString recherche)
{


        QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM AVOCAT where SPEC LIKE '"+recherche+"%'  OR LOWER(SPEC) LIKE '"+recherche+"%' OR UPPER(SPEC) LIKE '"+recherche+"%'");
       /* model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DEBUT_M"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NBR_DE_PERSONES"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESTINATION"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_FIN_M"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("TYPE_DE_MISSION"));*/
        return model;
    }

QSqlQueryModel* avocat::rech_nom(QString recherche)
{


        QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM AVOCAT where NOMPRENOM LIKE '"+recherche+"%'  OR LOWER(NOMPRENOM) LIKE '"+recherche+"%' OR UPPER(NOMPRENOM) LIKE '"+recherche+"%'");
       /* model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DEBUT_M"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NBR_DE_PERSONES"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESTINATION"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("BUDGET"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_FIN_M"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("TYPE_DE_MISSION"));*/
        return model;
    }



QSqlQueryModel* avocat::tri_prix()
{

    QSqlQueryModel* model2=new QSqlQueryModel();

          model2->setQuery("SELECT * FROM AVOCAT order by PRIX ASC");

          model2->setHeaderData(0, Qt::Horizontal, QObject::tr("NOMPRENOM"));
          model2->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
           model2->setHeaderData(2, Qt::Horizontal, QObject::tr("SPEC"));
            model2->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
            model2->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
            model2->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE"));

             model2->setHeaderData(6, Qt::Horizontal, QObject::tr("EXP"));

return model2;
}

QSqlQueryModel* avocat::tri_spec()
{

    QSqlQueryModel* model2=new QSqlQueryModel();

          model2->setQuery("SELECT * FROM AVOCAT order by SPEC ");

          model2->setHeaderData(0, Qt::Horizontal, QObject::tr("NOMPRENOM"));
          model2->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
           model2->setHeaderData(2, Qt::Horizontal, QObject::tr("SPEC"));
            model2->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
            model2->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
            model2->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE"));
             model2->setHeaderData(6, Qt::Horizontal, QObject::tr("EXP"));

return model2;
}
