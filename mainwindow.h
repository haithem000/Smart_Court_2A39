<<<<<<< Updated upstream
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rendezvous.h"
#include <QPixmap>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    //void on_pushButton_15_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    //void on_pushButton_10_clicked();

    void on_pushButton_7_stat_clicked();

   // void on_pushButton_4_clicked();

    void on_pushButton_4pdf1_clicked();

    void on_pushButton_5pdf2_clicked();

    //void on_pushButton_4_Excel_clicked();


    void on_aff_clicked();
    void on_photo_clicked();

    void on_pushButton_4_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendrier_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Rendezvous r;
};

#endif // MAINWINDOW_H

=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rendezvous.h"
#include <QPixmap>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    //void on_pushButton_15_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    //void on_pushButton_10_clicked();

    void on_pushButton_7_stat_clicked();

   // void on_pushButton_4_clicked();

    void on_pushButton_4pdf1_clicked();

    void on_pushButton_5pdf2_clicked();

    //void on_pushButton_4_Excel_clicked();


    void on_aff_clicked();
    void on_photo_clicked();

    void on_pushButton_4_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendrier_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Rendezvous r;
};

#endif // MAINWINDOW_H

>>>>>>> Stashed changes
