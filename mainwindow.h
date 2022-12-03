#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"
#include <QSortFilterProxyModel>
#include <QMainWindow>
#include <aff_juridique.h>
#include <QtCharts>
#include <QLineSeries>
#include "audiorecorder.h"
#include"stat_combo.h"
#include"arduino.h"
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
    QSortFilterProxyModel *proxy;


private slots:
    void rechEmploy();
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_rechercher_clicked();

    void on_PDF_clicked();

    //void on_pushButton_11_clicked();



    void on_le_TYPEAFF_currentIndexChanged(int index);
    //void on_mod_TYPEAFF_currentIndexChanged(int index);


    void on_recordButton_clicked();


    void on_mod_TYPEAFF_currentIndexChanged(int index);

    void on_trier_type_clicked();

    void on_trier_date_clicked();



    void on_pb_stat_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_recorder_clicked();

private:
    Ui::MainWindow *ui;
    QString audio="C:/Users/PC/Documents/GitHub/Smart_Court_2A39/debug/audiorecorder.exe";
    Aff_juridique AFF,AFF1;
    QStringList files;
    QString exp="",exp_mod="";
    audiorecorder *ar;
    stat_combo* stat;
    Arduino A;
        QByteArray data ;
};

//test
#endif // MAINWINDOW_H
