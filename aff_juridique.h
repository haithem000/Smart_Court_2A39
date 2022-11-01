#ifndef AFF_JURIDIQUE_H
#define AFF_JURIDIQUE_H

#include <QString>
#include <QSqlQueryModel>

class Aff_juridique
{
public:
    Aff_juridique();
     Aff_juridique(int,QString,QString);
     int getNUMAFF();
     QString getTYPEAFF();
     QString getDATEAFF();
     void setNUMAFF(int);
     void setTYPEAFF(QString);
     void setDATEAFF(QString);
     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer(int);
     bool modifier(int NUMAFF);
private:
    int NUMAFF;
    QString TYPEAFF;
    QString DATEAFF;



};

#endif // AFF_JURIDIQUE_H
