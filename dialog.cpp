#include "dialog.h"
#include "ui_dialog.h"
#include<QPieSeries>
#include <QSqlQuery>
#include "rendezvous.h"
#include <QChart>
#include <QChartView>
#include<QPieSeries>
#include <QPieSlice>
#include <QtCharts>
#include <QChartView>
#include <iostream>

#include "avocat.h"
#include <QtCharts>
using namespace::std;
using namespace std;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::afficher()
{QSqlQuery query0,query1,query2;
    float valEl=0,valPre=0,items=0;
    query0.prepare("select * from TABLE1");
    query0.exec();
    query1.prepare("select * from TABLE1 where TYPER =:Enligne");
    query1.bindValue(":Enligne","Enligne");
    query1.exec();
    query2.prepare("select * from TABLE1 where TYPER =:Presentiel ");
    query2.bindValue(":Presentiel","Presentiel");
    query2.exec();

    while(query0.next()){items++;};
    while(query1.next()){valEl++;};
    while(query2.next()){valPre++;};

    valEl=valEl/items;
    valPre=valPre/items;
    //cout << valEl << endl;
    QPieSeries *series = new QPieSeries();
    series->append("En ligne ",valEl);
    series->append("Presentiel",valPre);

    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible();



    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(420,300);
    chartView->show();
}

/*****************************************selim*******************************************************/

void Dialog::stats()
{

    QSqlQuery query0,query1,query2,query3;
        float valCiv=0,valPen=0,valAff=0,items=0;
        query0.prepare("select * from AVOCAT");
        query0.exec();
        query1.prepare("select * from AVOCAT where SPEC =:Civiliste");
        query1.bindValue(":Civiliste","Civiliste");
        query1.exec();
        query2.prepare("select * from AVOCAT where SPEC =:Penaliste");
        query2.bindValue(":Penaliste","Penaliste");
        query2.exec();
        query3.prepare("select * from AVOCAT where SPEC =:Affaires");
        query3.bindValue(":Affaires","Affaires");
        query3.exec();
        while(query0.next()){items++;};
        while(query1.next()){valCiv++;};
        while(query2.next()){valPen++;};
        while(query3.next()){valAff++;}

        valCiv=valCiv/items;
        valPen=valPen/items;
        valAff=valAff/items;

        QPieSeries *series = new QPieSeries();
        series->append("Civiliste",valCiv);
        series->append("Penaliste",valPen);
        series->append("Affaires",valAff);

        QPieSlice *slice0 = series->slices().at(0);
        slice0->setLabelVisible();
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
        QPieSlice *slice2 = series->slices().at(2);
        slice2->setLabelVisible();




        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart,this);
           chartView->setRenderHint(QPainter::Antialiasing);
           chartView->setMinimumSize(420,300);
           chartView->show();

}
/***************************************haithem********************************************************/
void Dialog::statistique()
{QSqlQuery query0,query1,query2,query3;
    float valEl=0,valPre=0,items=0;
    query0.prepare("select * from AFF_JURIDIQUE");
    query0.exec();
    query1.prepare("select * from AFF_JURIDIQUE where TYPEAFF =:A");
    query1.bindValue(":A","A");
    query1.exec();
    query2.prepare("select * from AFF_JURIDIQUE where TYPEAFF =:B ");
    query2.bindValue(":B","B");
    query2.exec();
    query3.prepare("select * from AFF_JURIDIQUE where TYPEAFF =:C ");
    query3.bindValue(":C","C");
    query3.exec();

    while(query0.next()){items++;};
    while(query1.next()){valEl++;};
    while(query2.next()){valPre++;};
     while(query3.next()){valPre++;};

    valEl=valEl/items;
    valPre=valPre/items;
    //cout << valEl << endl;
    QPieSeries *series = new QPieSeries();
    series->append("TYPE A ",valEl);
    series->append("TYPE B",valPre);
     series->append("TYPE C",valPre);

    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible();
    QPieSlice *slice2 = series->slices().at(2);
    slice2->setLabelVisible();


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(420,300);
    chartView->show();
}


/********************************bilel*****************************************************************/
void Dialog::sttat()
{

    QSqlQuery query0,query1,query2,query3;
        float valvi=0,valcom=0,items=0;
        query0.prepare("select * from SALLE");
        query0.exec();
        query1.prepare("select * from SALLE where ETAT =:Vide");
        query1.bindValue(":Vide","Vide");
        query1.exec();
        query2.prepare("select * from SALLE where ETAT =:Complet");
        query2.bindValue(":Complet","Complet");
        query2.exec();

        while(query0.next()){items++;};
        while(query1.next()){valvi++;};
        while(query2.next()){valcom++;};

        valvi=valvi/items;
        valcom=valcom/items;


        QPieSeries *series = new QPieSeries();
        series->append("Vide",valvi);
        series->append("Complet",valcom);


        QPieSlice *slice0 = series->slices().at(0);
        slice0->setLabelVisible();
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart,this);
           chartView->setRenderHint(QPainter::Antialiasing);
           chartView->setMinimumSize(420,300);
           chartView->show();

}


/********************************nesserine*****************************************************************/
void Dialog::statis()
{QSqlQuery query0,query1,query2;
    float valEl=0,valPre=0,items=0;
    query0.prepare("select * from EMPLOYE");
    query0.exec();
    query1.prepare("select * from EMPLOYE where ADRESSE =:tunis1");
    query1.bindValue(":tunis1","tunis1");
    query1.exec();
    query2.prepare("select * from EMPLOYE where ADRESSE =:tunis2 ");
    query2.bindValue(":tunis2","tunis2");
    query2.exec();

    while(query0.next()){items++;};
    while(query1.next()){valEl++;};
    while(query2.next()){valPre++;};

    valEl=valEl/items;
    valPre=valPre/items;
    //cout << valEl << endl;
    QPieSeries *series = new QPieSeries();
    series->append("tunis1 ",valEl);
    series->append("tunis2",valPre);
    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible();


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(420,300);
    chartView->show();
}
/*******************************************************saadeni*******************************************************/
void Dialog::saadeni_stat()
{QSqlQuery query0,query1,query2;
    float valEl=0,valPre=0,items=0;
    query0.prepare("select * from CITOYEN");
    query0.exec();
    query1.prepare("select * from CITOYEN where AGE =:25");
    query1.bindValue(":25","25");
    query1.exec();
    query2.prepare("select * from CITOYEN where AGE =:tunis2 ");
    query2.bindValue(":tunis2","tunis2");
    query2.exec();

    while(query0.next()){items++;};
    while(query1.next()){valEl++;};
    while(query2.next()){valPre++;};

    valEl=valEl/items;
    valPre=valPre/items;
    //cout << valEl << endl;
    QPieSeries *series = new QPieSeries();
    series->append("tunis1 ",valEl);
    series->append("tunis2",valPre);
    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible();


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart,this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(420,300);
    chartView->show();}
