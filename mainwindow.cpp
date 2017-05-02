#include <QDebug>
#include <QFile>
#include <QTextCodec>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libxls/xls.h"

//static char  stringSeparator = '\"';
//static void OutputString(const char *string) {
//    const char *str;

//    printf("%c", stringSeparator);
//    for (str = string; *str; str++) {
//        if (*str == stringSeparator) {
//            printf("%c%c", stringSeparator, stringSeparator);
//        } else if (*str == '\\') {
//            printf("\\\\");
//        } else {
//            printf("%c", *str);
//        }
//    }
//    printf("%c", stringSeparator);
//}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // modify the xls_open path to your own.
    xls::xlsWorkBook *pWB = xls::xls_open("/Users/John/Work/build-taokehelper-Desktop_Qt_5_7_1_clang_64bit-Debug/taokehelper.app/Contents/MacOS/productworker.xls", "UTF-8");
    // xls::xlsWorkBook *pWB = xls::xls_open("/Users/John/Desktop/productworker.xls", "UTF-8");
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
//            if (cell->id == 0x27e || cell->id == 0x0BD || cell->id == 0x203) {
//                qDebug() << "Number : " << QString::number(cell->d);
//            } else if (cell->id == 0x06) {
//                // formula
//                if (cell->l == 0) // its a number
//                {
//                    qDebug() << "Number : " << QString::number(cell->d);
//                } else {
//                    if (!strcmp((char *)cell->str, "bool")) // its boolean, and test cell->d
//                    {
//                        if (cell->d == 0) {
//                            qDebug() << "Boolean : false";
//                        } else {
//                            qDebug() << "Boolean : true";
//                        }
//                    } else if (!strcmp((char *)cell->str, "error")) // formula is in error
//                    {
//                        qDebug() << "formula *error*";
//                    } else // ... cell->str is valid as the result of a string formula.
//                    {
//                        // qDebug() << "Formula String : " << QTextCodec::codecForMib(1015)->toUnicode((char *)cell->str);
//                        qDebug() << "String : " << (char *)cell->str;
//                    }
//                }
//            } else if (cell->str != NULL) {
//                // qDebug() << "String : " << (char *)cell->str;
//                // qDebug() << "String : " << QString::fromUtf16((const ushort *)cell->str).toUtf8();
//                // QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//                // qDebug() << "String : " << QString::fromUtf16(reinterpret_cast<const ushort*>(cell->str));
//                // qDebug() << "wcslen((wchar_t *)cell->str) = " << QString::number(wcslen((wchar_t *)cell->str));
//                // qDebug() << "strlen((char *)cell->str) = " << QString::number(strlen((char *)cell->str));
//                qDebug() << "Normal String : " << (char *)cell->str;
//                // qDebug() << "UTF-16 : " << QString::fromUtf16((ushort *)cell->str, wcslen((wchar_t *)cell->str));
//            } else {
//                qDebug() << "";
//            }
        }
    }
    xls::xls_close_WS(pWS);
    xls::xls_close_WB(pWB);
}

MainWindow::~MainWindow()
{
    delete ui;
}
