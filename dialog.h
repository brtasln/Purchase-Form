#ifndef DIALOG_H
#define DIALOG_H
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QComboBox>
#include <QTableWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class LapisSiparis; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);


    ~Dialog();

private slots:
    void on_openButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::LapisSiparis *ui;

    QStringList readDataFromFile(const QString& fileName);



};
#endif // DIALOG_H
