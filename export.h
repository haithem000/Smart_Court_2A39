#ifndef EXPORT_H
#define EXPORT_H
#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>

class EEO_Field1
{
public:
    EEO_Field1(const int ic, const QString &sf, const QString &st):
            iCol(ic),sFieldName(sf),sFieldType(st){}

    int     iCol;
    QString sFieldName;
    QString sFieldType;
};

class Export : public QObject
{
    Q_OBJECT
public:
    Export(const QString &filepath, const QString &sheettitle,
                      QTableView *tableview):excelFilePath(filepath),
                      sheetName(sheettitle), tableView(tableview){}

    ~Export() {QSqlDatabase::removeDatabase("excelexport");}

public:
    void setOutputFilePath(const QString &spath) {excelFilePath = spath;}
    void setOutputSheetTitle(const QString &ssheet) {sheetName = ssheet;}
    void setTableView(QTableView *tableview) {tableView = tableview;}

    void addField(const int iCol, const QString &fieldname, const QString &fieldtype)
         {fieldList << new EEO_Field1(iCol, fieldname, fieldtype);}

    void removeAllFields()
         {while (!fieldList.isEmpty()) delete fieldList.takeFirst();}

    int export2Excel();

signals:
    void exportedRowCount(int row);

private:
    QString excelFilePath;
    QString sheetName;
    QTableView *tableView;
    QList<EEO_Field1 *> fieldList;
};

#endif // EXPORT_H
