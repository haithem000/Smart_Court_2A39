#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"
#include"employee.h"
#include <QSortFilterProxyModel>
#include <QMainWindow>
#include <aff_juridique.h>
#include <QtCharts>
#include <QLineSeries>
#include "audiorecorder.h"
#include"stat_combo.h"
#include"arduino.h"
#include "avocat.h"
QT_BEGIN_NAMESPACE
/*    */
#include <QPixmap>
#include "rendezvous.h"

#include "citoyen.h"


/***************saadani************************/

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

/***************saadani***********************/


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
//void affcherRendezvousArduino();

private slots:
    void rechEmploy();
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_rechercher_clicked();

    void on_PDFF_clicked();

    //void on_pushButton_11_clicked();



    void on_le_TYPEAFF_currentIndexChanged(int index);
    //void on_mod_TYPEAFF_currentIndexChanged(int index);


    void on_mod_TYPEAFF_currentIndexChanged(int index);

    void on_trier_type_clicked();

    void on_trier_date_clicked();



    void on_pb_stat_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
     void on_pushButton_4_clicked();
    void on_pushButton333_clicked();
    void on_recorder_clicked();

    /*     ****************************wejden*******************************                                           */

    void on_pb_ajouter_2_clicked();

        void on_pb_supprimer_2_clicked();

        void on_pb_modifier_2_clicked();

        //void on_pushButton_15_clicked();

        void on_pushButton_9_clicked();
/*******/
        void on_pushButton_8_clicked();
/*******/
        //void on_pushButton_10_clicked();

        void on_pushButton_7_stat_clicked();

       // void on_pushButton_4_clicked();

        void on_pushButton_4pdf1_clicked();

        void on_pushButton_5pdf2_clicked();

        //void on_pushButton_4_Excel_clicked();


        void on_aff_clicked();
        void on_photo_clicked();



        void on_calendarWidget_clicked(const QDate &date);

        void on_calendrier_activated(const QModelIndex &index);
        void affcherRendezvousArduino();

   /*     ****************************selim*******************************                                           */

            //void on_MainWindow_iconSizeChanged(const QSize &iconSize);

            //void on_pushButton_10_clicked();

            //void on_pushButton_11_clicked();

            void on_pushButton_supprimer_clicked();

            void on_pushButton_13_clicked();

            void on_pushButton_recherche_clicked();

            void on_pushButton_trprix_clicked();

            void on_pushButton_trspec_clicked();

            //void on_pushButton_valider_clicked();

            void on_pushButton_pdf_clicked();

            void on_statboutton_2_clicked();


            void on_pushButton_calc_clicked();
      //  void affcherRendezvousArduino();


            void on_pushButton_clear_clicked();

            /***************************selim*************************************/

            void on_pushButton_14_clicked();

            /***************************saadani*********************************/
            void on_Ajouterbutton_clicked();

            void on_Supprimerbutton_clicked();

            void on_Modifierbutton_clicked();

            void on_tableview_activated(const QModelIndex &index);

            void on_sortid_clicked();

            void on_saadeni_stat_clicked();



            void on_rechercher_2_clicked();

            void on_statbouton_clicked();
            /**********************saadani**********************************************************/
            /***************************bilel********************************************************/

           void on_pushButton_15_clicked();
          //  void on_MainWindow_iconSizeChanged(const QSize &iconSize);

           // void on_pushButton_10_clicked();
            void on_pushButton_supprimer_2_clicked();

            void on_pushButton_12_clicked();

           void on_pushButton_21_clicked();

            void on_pushButton_19_clicked();

            void on_pushButton_20_clicked();

            void on_pushButton_pdftri_clicked();

            void on_pushButton_77_clicked();

            void on_pushButton_rech_clicked();

/********************************************************************************************/



 /****************************nesrine********************************************************/
            void on_pb_ajouter_3_clicked();



            void on_pb_supprimer_3_clicked();

           void on_pb_modifier_3_clicked();
           void on_recherche_2_clicked();
           void on_tri_clicked();

           void on_Pdf_clicked();
           void on_pushButton223_clicked();

          // void on_pb_modifier_2_clicked();

          // void on_pb_modifier_3_clicked();
 /****************************nesrine******************************************************/

private:
    Ui::MainWindow *ui;
    QString audio="C:/Users/PC/Documents/GitHub/Smart_Court_2A39/debug/audiorecorder.exe";
    Aff_juridique AFF,AFF1;
    QStringList files;
    QString exp="",exp_mod="";
    audiorecorder *ar;
    //stat_combo* stat;
    Arduino A;
        QByteArray data ;
        Rendezvous r;
        avocat a;
         Citoyen Ctemp;
         Employee E;
};

//test
#endif // MAINWINDOW_H
