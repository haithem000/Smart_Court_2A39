#include "mainwindow.h"
#include "Citoyen.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCheckBox>
#include<QSqlQuery>
#include<QPainter>
#include<QtCharts>
#include<QtCharts/QBarSet>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QBarSeries>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
           switch(ret){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
    ui->tableview->setModel(Ctemp.afficher());
    ui->combosupp->setModel(Ctemp.get_id());
    show_tables();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouterbutton_clicked()
{
    int id=ui->idedit->text().toInt() ; //recovery and converting to an integer
       QString nom=ui->nomedit->text();
        QString prenom=ui->prenomedit->text();// recovery of string
        int age=ui->ageedit->text().toInt();
       Citoyen C(id,nom,prenom,age);
       bool test=C.ajouter();
       if(test)
          {
           ui->tableview->setModel(Ctemp.afficher());
           ui->combosupp->setModel(Ctemp.get_id());
           A.write_to_arduino("1");
           QMessageBox::information(nullptr, QObject::tr("Ajouter espace"),
                       QObject::tr("Patient ajouter.\n""Click Cancel to exit."), QMessageBox::Cancel);
       }

       else

       {
           A.write_to_arduino("2");
           ui->tableview->setModel(Ctemp.afficher());
           ui->combosupp->setModel(Ctemp.get_id());
           QMessageBox::critical(nullptr, QObject::tr("not Ajouter espace"),
                       QObject::tr("Ajout echoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

       }
}

void MainWindow::on_Supprimerbutton_clicked()
{
    int ID = ui->combosupp->currentText().toInt();
           bool test=Ctemp.supprimer(ID);

        if(test)
           {
            ui->tableview->setModel(Ctemp.afficher());
            ui->combosupp->setModel(Ctemp.get_id());
            A.write_to_arduino("3");
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression effectuée.\n""Click Cancel to exit."), QMessageBox::Cancel);
        }

        else

        {
            ui->tableview->setModel(Ctemp.afficher());
            ui->combosupp->setModel(Ctemp.get_id());
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Suppression echoué.\n""Click Cancel to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_Modifierbutton_clicked()
{
    int ID = ui->oldid->text().toInt();
            QString nom= ui->nommod->text();
            QString prenom= ui->prenommod->text();
int age = ui->oldage->text().toInt();
           Citoyen C(ID,nom,prenom,age);
             bool test = C.update(ID);


                if(test)

                {

                    ui->tableview->setModel(Ctemp.afficher());
                     ui->combosupp->setModel(Ctemp.get_id());

                    QMessageBox::information(nullptr, QObject::tr("EQUIPEMENT modifie"),
                                QObject::tr("EQUIPEMENT modifie\n"
                "Click Cancel to exit."), QMessageBox::Cancel);}

                else

                {
                    ui->tableview->setModel(Ctemp.afficher());
                    ui->combosupp->setModel(Ctemp.get_id());
                    QMessageBox::critical(nullptr, QObject::tr("not modifier"),
                                QObject::tr("not modified.\n""Click Cancel to exit."), QMessageBox::Cancel);

                }

                foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                        widget->clear();
                    }
}

void MainWindow::on_tableview_activated(const QModelIndex &index)
{
    QString id=ui->tableview->model()->data(index).toString();
         QSqlQuery query;
         query.prepare("SELECT * FROM CITOYEN WHERE ID= :ID");
         query.bindValue(":ID",id);
         if(query.exec()){
             while(query.next()){
                  ui->oldid->setText(query.value(0).toString());
                 ui->oldnom->setText(query.value(1).toString());
                 ui->oldprenom->setText(query.value(2).toString());
                 ui->oldage->setText(query.value(3).toString());

             }
         }
}

void MainWindow::on_sortid_clicked()
{
   ui->tableview->setModel(Ctemp.trierid());
}

void MainWindow::on_pushButton_clicked()
{
    QString strStream;
                     QTextStream out(&strStream);
                     const int rowCount = ui->tableview->model()->rowCount();
                     const int columnCount =ui->tableview->model()->columnCount();


                     out <<  "<html>\n"
                             "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             <<  QString("<title>%1</title>\n").arg("eleve")
                             <<  "</head>\n"
                             "<body bgcolor=#F2E7D5 link=#393E46>\n"
                                 "<h1>Liste des Citoyens</h1>"

                                 "<table border=0 cellspacing=5 cellpadding=5>\n";

                     // headers
                         out << "<thead><tr bgcolor=#F2E7D5>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tableview->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tableview->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";
                         // data table
                            for (int row = 0; row < rowCount; row++) {
                                out << "<tr>";
                                for (int column = 0; column < columnCount; column++) {
                                    if (!ui->tableview->isColumnHidden(column)) {
                                        QString data = ui->tableview->model()->data(ui->tableview->model()->index(row, column)).toString().simplified();
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
             printer.setOutputFileName("C:\\Users\\Hela\\Desktop\\QT_SADOUDA\\pdf.pdf"); //link needs to he right
             document->print(&printer);
}

void MainWindow::show_tables(){
//creation model (masque du tableau) : permet recherche et tri
    proxy = new QSortFilterProxyModel();

 //definir la source (tableau original)
    proxy->setSourceModel(Ctemp.afficher());

 //pour la recherche
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
    proxy->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
   //remplissage tableau avec le masque
    ui->tableview->setModel(proxy);

}

 //void MainWindow::on_searsh_textChanged(const QString &arg1)
//{
 //   proxy->setFilterFixedString(arg1);
//}

void MainWindow::on_rechercher_clicked()
{
    QString id1=ui->searsh->text();

         ui->tableview->setModel(Ctemp.rechercher(id1));
}

void MainWindow::on_statbouton_clicked()
{
    QSqlQuery query,query1,query2,query3;
                qreal c1=0 ,sum=0,c2=0,c3=0;
                query.prepare("SELECT * FROM employe") ;
                query.exec();
                while(query.next())
                {
                        sum++ ;
                }

                query1.prepare("SELECT * FROM employe where age >25 and age<35") ;
                query1.exec();
                while(query1.next())
                {
                        c1++ ;
                }

                query2.prepare("SELECT * FROM employe where age >35 and age<45 ") ;
                query2.exec();
                while(query2.next())
                {
                        c2++ ;
                }

                query3.prepare("SELECT * FROM employe where age >45") ;
                query3.exec();
                while(query3.next())
                {
                        c3++ ;
                }

            qreal d1,d2,d3;
            d1=(c1/sum)*100;
            d2=(c1/sum)*100;
            d3=(c1/sum)*100;
                QBarSet *set1 = new QBarSet("age>25");
                QBarSet *set2 = new QBarSet("age>35");
                QBarSet *set3 = new QBarSet("age>45");


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
                chart->setTitle("STATISTIQUE");

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

                 chartView->setMinimumSize(621,192);
                chartView->setParent(ui->tableaustat);
                chart->setTheme(QChart::ChartThemeBlueIcy);
                chartView->show();

}
