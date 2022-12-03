#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Citoyen.h"
#include "arduino.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QTextDocument>



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
void show_tables();

private slots:
    void on_Ajouterbutton_clicked();

    void on_Supprimerbutton_clicked();

    void on_Modifierbutton_clicked();

    void on_tableview_activated(const QModelIndex &index);

    void on_sortid_clicked();

    void on_pushButton_clicked();



    void on_rechercher_clicked();

    void on_statbouton_clicked();

private:
    Ui::MainWindow *ui;
    Citoyen Ctemp;
    QByteArray data; // variable contenant les données reçues

    arduino A; // objet temporaire
};

#endif // MAINWINDOW_H
