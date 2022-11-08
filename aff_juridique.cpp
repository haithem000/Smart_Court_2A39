#include "aff_juridique.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>

Aff_juridique::Aff_juridique()
{
NUMAFF=0;TYPEAFF="";DATEAFF="";AVOCAT="";JUGERES="";
}


 Aff_juridique::Aff_juridique(int NUMAFF,QString TYPEAFF ,QString DATEAFF,QString AVOCAT,QString JUGERES)
{this->NUMAFF=NUMAFF; this->TYPEAFF=TYPEAFF; this->DATEAFF=DATEAFF;this->AVOCAT=AVOCAT;this->JUGERES=JUGERES;}
 int Aff_juridique::getNUMAFF(){return NUMAFF;}
 QString Aff_juridique::getTYPEAFF(){return TYPEAFF; };
 QString Aff_juridique::getDATEAFF(){return DATEAFF;};
 QString Aff_juridique::getAVOCAT(){return AVOCAT;};
 QString Aff_juridique::getJUGERES(){return JUGERES;};
 void Aff_juridique::setNUMAFF(int NUMAFF){this->NUMAFF=NUMAFF;};
 void Aff_juridique::setTYPEAFF(QString TYPEAFF ){this->TYPEAFF=TYPEAFF;};
 void Aff_juridique::setDATEAFF(QString DATEAFF ){this->DATEAFF=DATEAFF;};
 void Aff_juridique::setTAVOCAT(QString AVOCAT ){this->AVOCAT=AVOCAT;};
void Aff_juridique::setJUGERES(QString JUGERES ){this->JUGERES=JUGERES;};
bool Aff_juridique::ajouter()
{

    QSqlQuery query;
    QString NUMAFF_string= QString::number(NUMAFF);
          query.prepare("INSERT INTO AFF_JURIDIQUE(NUMAFF, TYPEAFF, DATEAFF, AVOCAT, JUGERES) ""VALUES (:NUMAFF,:TYPEAFF,:DATEAFF,:AVOCAT,:JUGERES)");
          query.bindValue(0,NUMAFF_string );
          query.bindValue(1, TYPEAFF);
          query.bindValue(2,DATEAFF );
          query.bindValue(3,AVOCAT );
          query.bindValue(4,JUGERES );
 return query.exec();
}
bool Aff_juridique::supprimer(int NUMAFF)
{

    QSqlQuery query;
          query.prepare("Delete from Aff_juridique where NUMAFF=:NUMAFF");
          query.bindValue(0,NUMAFF );

 return query.exec();

}
QSqlQueryModel* Aff_juridique::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
 model->setQuery("SELECT* FROM Aff_juridique");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Avocat"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Juge"));



    return model;
}

bool Aff_juridique::modifier(int NUMAFF){
    QSqlQuery query;
   QString NUMAFF_string= QString::number(NUMAFF);

    //requette sql
    query.prepare("UPDATE Aff_juridique set TYPEAFF=:TYPEAFF,DATEAFF=:DATEAFF,AVOCAT=:AVOCAT,JUGERES=:JUGERES where NUMAFF=:NUMAFF");

    //saisir de donnee
    query.bindValue(":NUMAFF",NUMAFF_string);
    query.bindValue(":TYPEAFF",TYPEAFF);
    query.bindValue(":DATEAFF",DATEAFF);
    query.bindValue(":AVOCAT",AVOCAT);
    query.bindValue(":JUGERES",JUGERES);

    //execution de la requetteNU
    return query.exec();
}
QSqlQueryModel* Aff_juridique::trier()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Aff_juridique ORDER BY Numero");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Avocat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Juge"));


 return model;
}

QSqlQueryModel* Aff_juridique::rechercher()
{
    QString a;
    QSqlQueryModel* model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM tab_affaire where Avocat LIKE 'N%' ");
    return model;
}

