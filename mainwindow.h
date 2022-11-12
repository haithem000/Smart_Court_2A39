#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSortFilterProxyModel>
#include <QMainWindow>
#include <aff_juridique.h>
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

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;
    Aff_juridique AFF;
public slots:
    int creerPDF();
};

//test
#endif // MAINWINDOW_H
