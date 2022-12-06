#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "salle.h"
#include<QSqlQuery>
#include<QDebug>
#include <QSqlQueryModel>
#include <QObject>
Salle::Salle()
{
NBSALLE=0;
CAPACITE=0;
ETAT="";
}

void Salle::setNBSALLE(int NBSALLE){this->NBSALLE=NBSALLE;}
void Salle::setCAPACITE(int CAPACITE){this->CAPACITE=CAPACITE;}
void Salle::setETAT(QString ETAT){this->ETAT=ETAT;}


int Salle::getNBSALLE(){return NBSALLE;}
int Salle::getCAPACITE(){return CAPACITE;}
QString Salle::getETAT(){return ETAT;}



Salle::Salle(int NBSALLE, QString ETAT, int CAPACITE)
{this->NBSALLE=NBSALLE,  this->ETAT=ETAT,this->CAPACITE=CAPACITE;}



bool Salle::ajouter()
{
   QSqlQuery query;

        query.prepare("INSERT INTO SALLE (NBSALLE, ETAT, CAPACITE) "
                      "VALUES (:NBSALLE, :ETAT, :CAPACITE)");
        query.bindValue(":NBSALLE", NBSALLE);
        query.bindValue(":ETAT", ETAT);
        query.bindValue(":CAPACITE", CAPACITE);

        return query.exec();
}

QSqlQueryModel* Salle::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM SALLE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NBSALLE"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));


return model;
}


bool Salle::supprimer(int NBSALLE)
{
    QSqlQuery query;
         query.prepare("Delete from Salle where NBSALLE=:NBSALLE");
         query.bindValue(":NBSALLE", NBSALLE);

         return query.exec();
}

bool Salle::modifier(int NBSALLE)
{
    QSqlQuery query;
    query.prepare("UPDATE SALLE SET  ETAT=:ETAT, CAPACITE=:CAPACITE where NBSALLE=:NBSALLE");
    query.bindValue(":NBSALLE",NBSALLE);
     query.bindValue(":ETAT", ETAT);
    query.bindValue(":CAPACITE", CAPACITE);
    return query.exec();
}



QSqlQueryModel* Salle::recherche_cap(QString recherche)
{


        QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM SALLE where CAPACITE LIKE '"+recherche+"%'  OR LOWER(CAPACITE) LIKE '"+recherche+"%' OR UPPER(CAPACITE) LIKE '"+recherche+"%'");

        return model;
    }


QSqlQueryModel* Salle::recherche_nbsalle(QString recherche)
{


        QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM SALLE where NBSALLE LIKE '"+recherche+"%'  OR LOWER(NBSALLE) LIKE '"+recherche+"%' OR UPPER(NBSALLE) LIKE '"+recherche+"%'");

        return model;
    }

QSqlQueryModel* Salle::recherche_etat(QString recherche)
{


        QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM SALLE where ETAT LIKE '"+recherche+"%'  OR LOWER(ETAT) LIKE '"+recherche+"%' OR UPPER(ETAT) LIKE '"+recherche+"%'");

        return model;
    }

QSqlQueryModel* Salle::tri_cap()
{

    QSqlQueryModel* model2=new QSqlQueryModel();

          model2->setQuery("SELECT * FROM SALLE order by CAPACITE DESC ");

          model2->setHeaderData(0, Qt::Horizontal, QObject::tr("NBSALLE"));
          model2->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
           model2->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));



return model2;
}

QSqlQueryModel* Salle::tri_etat()
{

    QSqlQueryModel* model2=new QSqlQueryModel();

          model2->setQuery("SELECT * FROM SALLE order by ETAT DESC");

          model2->setHeaderData(0, Qt::Horizontal, QObject::tr("NBSALLE"));
          model2->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
           model2->setHeaderData(2, Qt::Horizontal, QObject::tr("CAPACITE"));


return model2;
}
