#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <process.h>

void format(char*);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}
