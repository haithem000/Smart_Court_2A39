#ifndef SALLE_H
#define SALLE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>

class Salle
{
public:
    Salle();
    Salle(int NBSALLE,QString ETAT, int CAPACITE);

    int getNBSALLE();
    int getCAPACITE();
    QString getETAT();


    void setNBSALLE(int );
    void setCAPACITE(int );
    void setETAT(QString );

bool modifier(int NBSALLE);
bool supprimer(int NBSALLE);
QSqlQueryModel* afficher();
    bool ajouter();
QSqlQueryModel* recherche_nbsalle(QString);
QSqlQueryModel* recherche_cap(QString);
QSqlQueryModel* recherche_etat(QString);

    QSqlQueryModel* tri_cap();
         QSqlQueryModel* tri_etat();
private:
    int NBSALLE,CAPACITE;
    QString ETAT;

};

#endif // SALLE_H
