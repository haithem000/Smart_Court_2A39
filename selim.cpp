#include "selim.h"
#include "ui_selim.h"
#include "avocat.h"
#include <QtCharts>
#include<iostream>
using namespace::std;




selim::selim(QWidget *parent) :
    selim(parent),
    ui(new Ui::selim)
{
    ui->setupUi(this);
}

selim::~selim()
{
    delete ui;
}

void selim::stats()
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
       /* QPieSlice *slice3 = series->slices().at(3);
        slice3->setLabelVisible();*/

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart,this);
           chartView->setRenderHint(QPainter::Antialiasing);
           chartView->setMinimumSize(420,300);
           chartView->show();

}
