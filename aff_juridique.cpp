#include "aff_juridique.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>

Aff_juridique::Aff_juridique()
{
NUMAFF=0;TYPEAFF="";DATEAFF="";
}


 Aff_juridique::Aff_juridique(int NUMAFF,QString TYPEAFF ,QString DATEAFF)
{this->NUMAFF=NUMAFF; this->TYPEAFF=TYPEAFF; this->DATEAFF=DATEAFF;}
 int Aff_juridique::getNUMAFF(){return NUMAFF;}
 QString Aff_juridique::getTYPEAFF(){return TYPEAFF; };
 QString Aff_juridique::getDATEAFF(){return DATEAFF;};
 void Aff_juridique::setNUMAFF(int NUMAFF){this->NUMAFF=NUMAFF;};
 void Aff_juridique::setTYPEAFF(QString TYPEAFF ){this->TYPEAFF=TYPEAFF;};
 void Aff_juridique::setDATEAFF(QString DATEAFF ){this->DATEAFF=DATEAFF;};
bool Aff_juridique::ajouter()
{

    QSqlQuery query;
    QString NUMAFF_string= QString::number(NUMAFF);
          query.prepare("INSERT INTO AFF_JURIDIQUE(NUMAFF, TYPEAFF, DATEAFF) ""VALUES (:NUMAFF,:TYPEAFF,:DATEAFF)");
          query.bindValue(0,NUMAFF_string );
          query.bindValue(1, TYPEAFF);
          query.bindValue(2,DATEAFF );
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



    return model;
}

bool Aff_juridique::modifier(int NUMAFF){
    QSqlQuery query;
   QString NUMAFF_string= QString::number(NUMAFF);

    //requette sql
    query.prepare("UPDATE Aff_juridique set TYPEAFF=:TYPEAFF,DATEAFF=:DATEAFF where NUMAFF=:NUMAFF");

    //saisir de donnee
    query.bindValue(":NUMAFF",NUMAFF_string);
    query.bindValue(":TYPEAFF",TYPEAFF);
    query.bindValue(":DATEAFF",DATEAFF);

    //execution de la requetteNU
    return query.exec();
}
