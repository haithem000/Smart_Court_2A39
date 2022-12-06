#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QString>
#include<QSqlQueryModel>
#include"ui_mainwindow.h"

class Rendezvous
{
public:
    Rendezvous();
    Rendezvous(int, QString, QString, QString,int ,QString,QString,QString,QString);

    int getnumr(){return NUMR;}
    int getnumrs(){return NUMS;}
    QString gettype(){return TYPER;}
    QString getadresse(){return ADRESSER;}
    QString getdate(){return DATER;}
    QString gettime(){return TIME;}
    QString getnoma(){return NOMA;}
    QString getnomc(){return NOMC;}



    void setnumr(int numr){ NUMR=numr ;}
   void setnumrs(int numr){ NUMS=numr ;}
    void settype(QString type){TYPER=type;}
    void setadresse(QString adresse){ADRESSER=adresse;}
    void setdate(QString date ){DATER=date;}
     void setnoma(QString noma ){NOMA=noma;}
     void setnomc(QString nomc ){NOMC=nomc;}
     void settiem(QString time){TIME =time;}

    bool ajouter ();
    QSqlQueryModel *afficher();
    bool supprimer (int);
    bool modifier(int );
    QSqlQueryModel* rechercherID(QString );
    QSqlQueryModel* rechercherIDA(QString recherche);
    QSqlQueryModel * triID();
     QSqlQueryModel * triIDA();
    QSqlQueryModel * triNom();
     QSqlQueryModel * triNomC();
     QSqlQueryModel* recherchernomc(QString );
     QSqlQueryModel * recherche_DATED(QDate val);



private :
    int NUMR,NUMS;
    QString ADRESSER,TYPER,DATER,NOMA,NOMC,TIME,ETAT;
};

#endif // RENDEZVOUS_H

