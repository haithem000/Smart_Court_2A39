#ifndef login_H
#define login_H
#include <QMainWindow>
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QDialog>
#include "connection.h"
#include "employee.h"
#include <QSql>
#include "arduino.h"


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void rechEmploy();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::login *ui;
    Arduino A;
            QByteArray data ;
};

#endif // login_H
