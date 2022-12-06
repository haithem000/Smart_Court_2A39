#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>
class Employee
{
public:
    Employee();
Employee(int,QString,QString,QString,int,QString);
int getID();
QString getNOM();
QString getPRENOM();
QString getMAIL();
QString getADRESSE();
int getMOTDEPASSE();

void setID(int);
void setNOM(QString);
void setPRENOM(QString);
void setMAIL (QString);
void setMOTDEPASSE(int);
void setADRESSE(QString);
bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int );
QSqlQueryModel* recherche();
QSqlQueryModel* tri();
QSqlQueryModel * rechercher_MAIL(QString recherche1,QString recherche2);

private:
    int ID,MOTDEPASSE;
    QString NOM,PRENOM,MAIL,ADRESSE;

};


#endif // EMPLOYEE_H
