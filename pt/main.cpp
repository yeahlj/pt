#include "mainwindow.h"
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setFixedSize(1000,800);

    w.setWindowFlags(Qt::WindowCloseButtonHint);

   // QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));

   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName ("UTF-8"));

    w.show();
    return a.exec();

}

