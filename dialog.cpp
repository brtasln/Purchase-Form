#include "dialog.h"
#include "./ui_dialog.h"
#include <QTableWidget>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include "QStringList"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LapisSiparis)
{

    ui->setupUi(this);

    QPixmap image(":/resources/Lapis-Logo.jpg");

    QStringList readDataFromFile(const QString& fileName);

    int columnToModify = 1;

    QStringList comboBoxData = readDataFromFile(":/resources/satinAlmaTurleri.txt");
    qDebug() << comboBoxData;
    for (int row = 1; row < ui->tableWidget->rowCount(); row++)
    {
        QComboBox* comboBox = new QComboBox;
        comboBox->addItems(comboBoxData);
        ui->tableWidget->setCellWidget(row, columnToModify, comboBox);
      //  ui->tableWidget->cellWidget(row , columnToModify, comboBox);

    //static_cast<QComboBox*>(ui->tableWidget->cellWidget(row,columnToModify))->currentText();
    }
}

QStringList readDataFromFile(const QString& fileName)
{
    QStringList data;
    QFile file(":/resources/satinAlmaTurleri.txt");

    if( file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QTextStream in(&file);
        while( !in.atEnd())
        {
            QString line = in.readLine();
            data.append(line);
        }
        file.close();
    }
        else
        {
            qDebug() <<"texti açamadık malsf" << file.errorString();
            qDebug() <<"Dosya yolu : " << fileName;
        }
    return data;
}

void Dialog ::on_openButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(
        this,".","xlsx");
    if(filepath.isEmpty())
        return;

    QXlsx::Document xlsxR(filepath);
    if( xlsxR.load())
    {
        ui->tableWidget->setRowCount(15);
        ui->tableWidget->setColumnCount(29);
        QStringList header;
        header << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" <<
            "I" << "J" << "K" << "L" << "M" << "N" << "O" ;
        ui->tableWidget->setHorizontalHeaderLabels(header);

        for(int row = 0 ; row < 15 ; row++)
        {
            for( int col = 0 ; col < 29 ; col++)
            {
                QXlsx::Cell* cell = xlsxR.cellAt(row+1 , col+1);
                if( cell != NULL)
                {
                    ui->tableWidget->setItem( row, col,
                          new QTableWidgetItem(cell->readValue().toString()));
                    ui->tableWidget->item(row, col)->setTextAlignment(Qt::Alignment(Qt::AlignCenter));
                    QVariant var = cell->readValue();
                    qDebug() << var;
                }
            }
        }
    }
}

void Dialog::on_saveButton_clicked()
{
    QXlsx::Document xlsxW;
    for( int row = 0; row < ui->tableWidget->rowCount() ; row++)
    {
        for( int col = 0 ; col < ui->tableWidget->columnCount() ; col++)
        {
            if(ui->tableWidget->cellWidget(row,col) != nullptr)
                xlsxW.write(row+1 , col+1, static_cast<QComboBox*>(ui->tableWidget->cellWidget(row,1))->currentText());
            else if(ui->tableWidget->item(row,col) != nullptr)
                xlsxW.write(row+1 , col+1, QVariant(ui->tableWidget->item(row,col)->text()));
        }
    }
   /* for( int row = 0; row < ui->tableWidget->rowCount() ; row++)
    {
        for( int col = 2 ; col < ui->tableWidget->columnCount() ; col++)
        {
            if(ui->tableWidget->item(row,col) != nullptr)
                xlsxW.write(row+1 , col+1, QVariant(ui->tableWidget->item(row,col)->text()));

        }
    }
    for (int row = 1 ; row < ui->tableWidget->rowCount() ; row ++)
    {
        for ( int col = 1 ; col < 2 ;  col ++)
        {
             qDebug() << static_cast<QComboBox*>(ui->tableWidget->cellWidget(row    ,1))->currentText();
        }
   */

    QString savefile = QFileDialog::getSaveFileName(this, "." ,"","Excel files (*.xlsx);; All files (*.*)");
    if( !savefile.isEmpty())
        xlsxW.saveAs(savefile);


}


Dialog::~Dialog()
{
    delete ui;
}

