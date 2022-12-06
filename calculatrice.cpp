#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <QDebug>
double firstnum;
bool usertyping= false;

calculatrice::calculatrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calculatrice)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digits_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digits_pressed()));
     connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digits_pressed()));
      connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digits_pressed()));
       connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digits_pressed()));
        connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digits_pressed()));
         connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digits_pressed()));
          connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digits_pressed()));
           connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digits_pressed()));
            connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digits_pressed()));
             connect(ui->pushButton_plusmoin,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
             connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

              connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
              connect(ui->pushButton_moins,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
              connect(ui->pushButton_mult,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
              connect(ui->pushButton_div,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

ui->pushButton_plus->setCheckable(true);
ui->pushButton_moins->setCheckable(true);
ui->pushButton_mult->setCheckable(true);
ui->pushButton_div->setCheckable(true);


}

calculatrice::~calculatrice()
{
    delete ui;
}

void calculatrice::digits_pressed()
{

    qDebug()<<"test";
   QPushButton * button = (QPushButton*)sender();
   double labelnumber;
   QString newlabel;
 if((ui->pushButton_plus->isChecked() || ui->pushButton_moins->isChecked() ||
     ui->pushButton_mult->isChecked() || ui->pushButton_div->isChecked()) && (!usertyping))
 {
 labelnumber=button->text().toDouble();
  usertyping= true;
   newlabel=QString::number(labelnumber,'g',15);
 }
 else {
     if(ui->labe_res->text().contains('.') && button->text()=="0")
     { newlabel=ui->labe_res->text()+ button->text();

     }
     else {
         labelnumber=(ui->labe_res->text()+ button->text()).toDouble();
          newlabel=QString::number(labelnumber,'g',15);
     }



 }

   ui->labe_res->setText(newlabel);
}

void calculatrice::on_pushButton_point_released()
{
    ui->labe_res->setText(ui->labe_res->text() + ".");
}

void calculatrice::unary_operation_pressed()
{
     double labelnumber;
     QString newlabel;

     QPushButton * button=(QPushButton*) sender();
     if(button->text()=="+/-")
     {
         labelnumber=ui->labe_res->text().toDouble();
         labelnumber=labelnumber * -1;
         newlabel=QString::number(labelnumber,'g',15);
         ui->labe_res->setText(newlabel);
     }
     if(button->text()=="%")
     {
         labelnumber=ui->labe_res->text().toDouble();
         labelnumber=labelnumber * 0.01;
         newlabel=QString::number(labelnumber,'g',15);
         ui->labe_res->setText(newlabel);
     }

 }

void calculatrice::on_pushButton_c_released()
{
ui->pushButton_plus->setChecked(false);
ui->pushButton_moins->setChecked(false);
ui->pushButton_mult->setChecked(false);
ui->pushButton_div->setChecked(false);
usertyping=false;
ui->labe_res->setText("0");

}

void calculatrice::on_pushButton_egale_released()
{
    double labelnumber, secondnum;
    QString newlabel;
    secondnum = ui->labe_res->text().toDouble();

   if (ui->pushButton_plus->isChecked())
   {
      labelnumber= firstnum+secondnum;
      newlabel= QString::number(labelnumber,'g',15);
      ui->labe_res->setText(newlabel);
      ui->pushButton_plus->setChecked(false);
   }
  else if (ui->pushButton_moins->isChecked())
   {
       labelnumber= firstnum - secondnum;
       newlabel= QString::number(labelnumber,'g',15);
       ui->labe_res->setText(newlabel);
       ui->pushButton_moins->setChecked(false);
   }
   else if (ui->pushButton_mult->isChecked())
   {
       labelnumber= firstnum * secondnum;
       newlabel= QString::number(labelnumber,'g',15);
       ui->labe_res->setText(newlabel);
       ui->pushButton_mult->setChecked(false);
   }
   else if (ui->pushButton_div->isChecked())
   {
       labelnumber= firstnum / secondnum;
       newlabel= QString::number(labelnumber,'g',15);
       ui->labe_res->setText(newlabel);
       ui->pushButton_div->setChecked(false);
   }
   usertyping=false;
}

void calculatrice::binary_operation_pressed()
{
    QPushButton * button=(QPushButton*) sender();
    firstnum= ui->labe_res->text().toDouble();
    button->setChecked(true);


}
