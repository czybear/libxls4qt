#include <QDebug>
#include <QFile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libxls/xls.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // modify the xls_open path to your own.
    xls::xlsWorkBook *pWB = xls::xls_open("/Users/John/Work/libxls4qt/test.xls", "UTF-8");
    if (pWB == NULL) {
        qDebug() << "File not found, modify the xls_open path to your own.";
        return;
    }
    xls::xlsWorkSheet *pWS = xls::xls_getWorkSheet(pWB, 0);
    if (pWS == NULL) {
        qDebug() << "WorkSheet not found.";
        return;
    }
    xls::xls_parseWorkSheet(pWS);

    for (int r = 0; r <= pWS->rows.lastrow; r++) {
        for (int c = 0; c <= pWS->rows.lastcol; c++) {
            xls::xlsCell *cell = xls::xls_cell(pWS, r, c);
            if (!cell || cell->isHidden) {
                continue;
            }
            if (cell->id == 0x27e || cell->id == 0x0BD || cell->id == 0x203) {
                qDebug() << "Number : " << QString::number(cell->d);
            } else if (cell->id == 0x06) {
                // formula
                if (cell->l == 0) // its a number
                {
                    qDebug() << "Number : " << QString::number(cell->d);
                } else {
                    if (!strcmp((char *)cell->str, "bool")) // its boolean, and test cell->d
                    {
                        if (cell->d == 0) {
                            qDebug() << "Boolean : false";
                        } else {
                            qDebug() << "Boolean : true";
                        }
                    } else if (!strcmp((char *)cell->str, "error")) // formula is in error
                    {
                        qDebug() << "formula *error*";
                    } else // ... cell->str is valid as the result of a string formula.
                    {
                        qDebug() << "String : " << (char *)cell->str;
                    }
                }
            } else if (cell->str != NULL) {
                qDebug() << "String : " << (char *)cell->str;
            } else {
                qDebug() << "";
            }
        }
    }
    xls::xls_close_WS(pWS);
    xls::xls_close_WB(pWB);
}

MainWindow::~MainWindow()
{
    delete ui;
}
