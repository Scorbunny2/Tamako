//-------------------------------------------
//main.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//main.cpp
//Copyright 2022 黄天宇
//-------------------------------------------

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
