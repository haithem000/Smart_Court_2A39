#include "citoyen.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Citoyen::Citoyen()
{
    id=0; nom="";prenom="";age=0;

}
   Citoyen::Citoyen(int id,QString nom,QString prenom,int age)
   {this->id=id; this->nom=nom;this->prenom=prenom;this->age=age;}
   int Citoyen::getid(){return id;}
    QString Citoyen::getnom(){return nom;}
    QString Citoyen::getprenom(){return prenom;}
    int Citoyen::getage(){return age;}
    void Citoyen::setid(int id){this->id=id;}
    void Citoyen::setnom(QString nom){this->nom=nom;}
    void Citoyen::setprenom(QString prenom){this->prenom=prenom;}
     void Citoyen::setage(int age){this->age=age;}

    bool Citoyen::ajouter()
    {
     QString id_String=QString::number(id);
        QSqlQuery QUERY ;
              QUERY.prepare("INSERT INTO Citoyen (id, nom, prenom,age) ""VALUES (:id, :forename, :surname,:age)");
              QUERY.bindValue(":id", id);
              QUERY.bindValue(":forename", nom);
              QUERY.bindValue(":surname", prenom);
              QUERY.bindValue(":age", age);
            return  QUERY.exec();

    }
    QSqlQueryModel * Citoyen::get_id()
    {
           QSqlQueryModel * model=new QSqlQueryModel();
           model->setQuery("SELECT ID FROM CITOYEN");
           return model;
    }


    bool Citoyen::supprimer(int ID)
    {
        QSqlQuery query;
           QString N_string =QString::number(ID) ; //converting number into Qstring
           query.prepare("DELETE FROM CITOYEN WHERE ID= :ID");
           query.bindValue(":ID",N_string);
           return query.exec();
    }

QSqlQueryModel* Citoyen::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT*  FROM CITOYEN");
          model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal,QObject:: tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject:: tr("prenom"));
             model->setHeaderData(3, Qt::Horizontal, QObject:: tr("age"));
    return model;
}

bool Citoyen::update(int ID){
    QSqlQuery query;
    QString N_string =QString::number(ID) ;
    query.prepare("UPDATE CITOYEN SET NOM= :nom,PRENOM= :prenom,AGE= :age WHERE ID = :ID");
    query.bindValue(":ID", N_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    return query.exec();
}


QSqlQueryModel * Citoyen::trierid()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CITOYEN ORDER BY ID");
    model->setHeaderData(0, Qt::Horizontal,QObject :: tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject :: tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject :: tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject :: tr("age"));
    return model;
}

QSqlQueryModel *Citoyen::rechercher(QString id)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from CITOYEN where ID LIKE '"+id+"' ");
    return model;
}



