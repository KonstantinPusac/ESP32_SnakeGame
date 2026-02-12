#include "MainSnake.h"
#include <iostream>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSnake w;
    w.show();
    return a.exec();
}
