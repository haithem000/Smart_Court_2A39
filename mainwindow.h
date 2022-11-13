#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSortFilterProxyModel>
#include <QMainWindow>
#include <aff_juridique.h>
#include <QtCharts>
#include <QLineSeries>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSortFilterProxyModel *proxy;


private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_trier_clicked();
    void on_rechercher_clicked();

    void on_PDF_clicked();

    //void on_pushButton_11_clicked();

    void on_pb_stat_clicked();

private:
    Ui::MainWindow *ui;
    Aff_juridique AFF;
    QStringList files;
};

//test
#endif // MAINWINDOW_H
