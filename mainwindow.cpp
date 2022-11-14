#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aff_juridique.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExp>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QSqlQuery>
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_NUMAFF->setValidator(new QIntValidator(100, 999999, this));
    ui->mod_NUMAFF->setValidator(new QIntValidator(100, 999999, this));
    ui->num_supprimer->setValidator(new QIntValidator(0, 999999, this));
    QRegExp RX("^[A-C.]+$");
    QValidator* validatoR = new QRegExpValidator(RX, this);
    ui->le_TYPEAFF->setValidator(validatoR);
     ui->mod_TYPEAFF->setValidator(validatoR);
    QRegExp rx("^[a-zA-Z.]+$");
    QValidator* validator = new QRegExpValidator(rx, this);
    ui->l_AVOCAT->setValidator(validator);

    ui->le_JUGERES->setValidator(validator);

    ui->mod_AVOCAT->setValidator(validator);
    ui->mod_JUGERES->setValidator(validator);
    ui->tab_affaire->setModel(AFF.afficher());

    ui->l_AVOCAT->setModel(AFF.get_avocats("A"));
    ui->le_JUGERES->setModel(AFF.get_judges("A"));

    ui->mod_AVOCAT->setModel( AFF1.get_avocats("A"));
    ui->mod_JUGERES->setModel(AFF1.get_judges("A"));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int NUMAFF=ui->le_NUMAFF->text().toInt();
    QString TYPEAFF=ui->le_TYPEAFF->currentText();
    QString DATEAFF=ui->le_DATEAFF->text();
    QString AVOCAT=ui->l_AVOCAT->currentText();
    QString JUGERES=ui->le_JUGERES->currentText();

   Aff_juridique AFF(NUMAFF,TYPEAFF,DATEAFF,AVOCAT,JUGERES);
   bool test;
   test=AFF.ajouter();
       QMessageBox msgBox;

       if(test)
       {msgBox.setText("ajout avec succes");
            ui->tab_affaire->setModel(AFF.afficher());
       }
       else msgBox.setText("Echec d'ajout");
       msgBox.exec();

}

void MainWindow::on_pb_supprimer_clicked()
{

    Aff_juridique AFF1;  AFF1.setNUMAFF(ui->num_supprimer->text().toInt());
    bool test=AFF1.supprimer(AFF1.getNUMAFF());

QMessageBox msgBox;
    if(test)
     {msgBox.setText("Suppression avec succes.");

        ui->tab_affaire->setModel(AFF.afficher());

    }
    else
        msgBox.setText("Echec de suppression.");

    msgBox.exec();

}

void MainWindow::on_pb_modifier_clicked()
{
    int NUMAFF=ui->mod_NUMAFF->text().toInt();
    QString TYPEAFF=ui->mod_TYPEAFF->currentText();
    QString DATEAFF=ui->mod_DATEAFF->text();
    QString AVOCAT=ui->mod_AVOCAT->currentText();
    QString JUGERES=ui->mod_JUGERES->currentText();

    Aff_juridique AFF(NUMAFF,TYPEAFF,DATEAFF,AVOCAT,JUGERES);

    bool test=AFF.modifier(NUMAFF);
        if(test)
        {
            //refrech
            ui->tab_affaire->setModel(AFF.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Modification avec succes.\n" "Click Close to exit."), QMessageBox::Close);
    }else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("Modification echoue.\n" "Click Close to exit."), QMessageBox::Close);
}



void MainWindow::on_trier_date_clicked()
{
  ui->tab_affaire->setModel(AFF.trier_date());

}


void MainWindow::on_trier_type_clicked()
{
    ui->tab_affaire->setModel(AFF.trier_type());

}


void MainWindow::on_rechercher_clicked()
{
            int NUMAFF=ui->le_Rechercher->text().toInt();
            QString TYPEAFF=ui->le_Rechercher->text();
            QString DATEAFF=ui->le_Rechercher->text();
            QString AVOCAT=ui->le_Rechercher->text();
            QString JUGERES=ui->le_Rechercher->text();
ui->tab_affaire->setModel(AFF.rechercher(NUMAFF,TYPEAFF,DATEAFF,AVOCAT,JUGERES));


}


//pdf : vous trouver le fichier dans le dossier build
void MainWindow::on_PDF_clicked()
{

QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tab_affaire->model()->rowCount();
            const int columnCount =ui->tab_affaire->model()->columnCount();


            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("eleve")
                    <<  "</head>\n"
                    "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                        "<h1>Liste Des Affaires</h1>"

                        "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab_affaire->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab_affaire->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tab_affaire->isColumnHidden(column)) {
                               QString data = ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(row, column)).toString().simplified();
                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                           }
                       }
                       out << "</tr>\n";
                   }
                   out <<  "</table>\n"
                       "</body>\n"
                       "</html>\n";



    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);


    //QTextDocument document;
    //document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("MYfile.pdf");
    document->print(&printer);}


void MainWindow::on_pb_stat_clicked()
{
    QSqlQuery query,query1,query2,query3;
        qreal c1=0 ,sum=0,c2=0,c3=0;
        query.prepare("SELECT * FROM AFF_JURIDIQUE") ;
        query.exec();
        while(query.next())
        {
                sum++ ;
        }

        query1.prepare("SELECT * FROM AFF_JURIDIQUE where TYPE=A") ;
        query1.exec();
        while(query1.next())
        {
                c1++ ;
        }

        query2.prepare("SELECT * FROM AFF_JURIDIQUE where TYPE=B") ;
        query2.exec();
        while(query2.next())
        {
                c2++ ;
        }

        query3.prepare("SELECT * FROM AFF_JURIDIQUE where TYPE =C") ;
        query3.exec();
        while(query3.next())
        {
                c3++ ;
        }

    qreal d1,d2,d3;
    d1=(c1/sum)*100;
    d2=(c1/sum)*100;
    d3=(c1/sum)*100;
        QBarSet *set1 = new QBarSet("TYPE A");
        QBarSet *set2 = new QBarSet("TYPE B");
        QBarSet *set3 = new QBarSet("TYPE C");


        // Assign values for each bar
         *set1 << d1 ;
         *set2 << d2 ;
         *set3 << d3 ;


        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();

        // 2. Stacked bar chart
        // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

        series->append(set1);
        series->append(set2);
        series->append(set3);


        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);

        // Set title
        chart->setTitle("Statistique selon type");

        // Define starting animation
        // NoAnimation, GridAxisAnimations, SeriesAnimations
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Holds the category titles
        QStringList categories;
        categories << "stats";

        // Adds categories to the axes
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->addAxis(axis, Qt::AlignBottom);
        series->attachAxis(axis);
        chart->createDefaultAxes();


        // 2. Stacked Bar chart

        // Define where the legend is displayed
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);


        // Used to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

         chartView->setMinimumSize(800,400);
        chartView->setParent(ui->tableau);

        // Used to change the palette
        QPalette pal = qApp->palette();


        // Apply palette changes to the application
        qApp->setPalette(pal);
}




void MainWindow::on_le_TYPEAFF_currentIndexChanged(int index)
{
    exp=ui->le_TYPEAFF->currentText();
    ui->l_AVOCAT->setModel( AFF.get_avocats(exp));
    ui->le_JUGERES->setModel(AFF.get_judges(exp));

}

void MainWindow::on_mod_TYPEAFF_currentIndexChanged(int indexx)
{
    exp_mod=ui->mod_TYPEAFF->currentText();
    ui->mod_AVOCAT->setModel( AFF1.get_avocats(exp_mod));
    ui->mod_JUGERES->setModel(AFF1.get_judges(exp_mod));

}


void MainWindow::on_recordButton_clicked()
{
    QProcess *process = new QProcess(this);
    process->start(audio);
   /* ar= new audiorecorder();
    ar->show();
    */
}




