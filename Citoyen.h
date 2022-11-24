#ifndef CITOYEN_H
#define CITOYEN_H
#include<QString>
#include<QSqlQueryModel>

class Citoyen
{
public:
    Citoyen();
    Citoyen(int,QString,QString,int);
    int getid();
    QString getnom();
    QString getprenom();
    int getage();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setage(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool update(int);
    QSqlQueryModel * trierid();
     QSqlQueryModel *get_id();
     QSqlQueryModel *rechercher(QString );
private:
    int id,age;
    QString nom,prenom;
};

#endif // CITOYEN_H
