#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QDialog>

namespace Ui {
class calculatrice;
}

class calculatrice : public QDialog
{
    Q_OBJECT

public:
    explicit calculatrice(QWidget *parent = nullptr);
    ~calculatrice();

private:
    Ui::calculatrice *ui;

private slots:
    void digits_pressed();
    void on_pushButton_point_released();
    void unary_operation_pressed();
    void on_pushButton_c_released();
    void on_pushButton_egale_released();
    void binary_operation_pressed();
};

#endif // CALCULATRICE_H
