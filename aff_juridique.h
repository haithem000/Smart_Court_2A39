#ifndef AFF_JURIDIQUE_H
#define AFF_JURIDIQUE_H
//miss test
#include <QString>
#include <QComboBox>

#include <QSqlQueryModel>

class Aff_juridique
{
public:
    Aff_juridique();
     Aff_juridique(int,QString,QString, QString, QString);
     int getNUMAFF();
     QString getTYPEAFF();
     QString getDATEAFF();
     QString getJUGERES();
      QString getAVOCAT();
     void setNUMAFF(int);
     void setTYPEAFF(QString);
     void setDATEAFF(QString);
     void setJUGERES(QString);
     void setTAVOCAT(QString);
     bool ajouter();
     QSqlQueryModel* afficher();
     QSqlQueryModel* trier();
     QSqlQueryModel* rechercher();
     QSqlQueryModel* get_avocats(QString exp);
     QSqlQueryModel* get_judges(QString exp);

     bool supprimer(int);
     bool modifier(int NUMAFF);
private:
    int NUMAFF;
    QString TYPEAFF;
    QString DATEAFF;
    QString JUGERES;
   QString AVOCAT;

//haithem



};

#endif // AFF_JURIDIQUE_H
