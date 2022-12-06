#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"employee.h"
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QLineSeries>
#include "arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_label();

private slots:
    void on_pb_ajouter_clicked();



    void on_pb_supprimer_clicked();

   void on_pb_modifier_clicked();
   void on_recherche_clicked();
   void on_tri_clicked();

   void on_Pdf_clicked();

   void on_pb_modifier_2_clicked();

   void on_pb_modifier_3_clicked();





private:
    Ui::MainWindow *ui;
    Employee E;
    Arduino A;
            QByteArray data ;
};

#endif // MAINWINDOW_H
