#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
class avocat
{
public:
      avocat();
    avocat(QString ID, QString NOMPRENOM, QString SPEC, int PRIX, int NUM, QString ADRESSE, QString EXP);
    void setID(QString n);
    void setnNOMPRENOM(QString n);
    void setSPEC(QString n);
    void setPRIX(int n);
    void setNUM(int n);
    void setADRESSE(QString n);
    void setEXP(QString n);

    QString get_ID();
    QString get_NOMPRENOM();
    QString get_SPEC();
    int get_PRIX();
    int get_NUM();
    QString get_ADRESSE();
     QString get_EXP();

    bool verif_id();
    bool verif_nom();
    bool verif_spec();
    bool verif_num();
    bool verif_adr();
    bool verif_prix();



    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString );
    bool modifier(QString);
     QSqlQueryModel* rech_id(QString);
      QSqlQueryModel* rech_nom(QString);
       QSqlQueryModel* rech_spec(QString);
     QSqlQueryModel* tri_prix();
     QSqlQueryModel* tri_spec();
     void stats();

 private:
    QString ID,NOMPRENOM,SPEC, ADRESSE, EXP;
    int PRIX, NUM;
};

#endif // CLIENT_H
