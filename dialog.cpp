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
