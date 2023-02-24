//-------------------------------------------
//mainwindow.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//登陆界面头文件
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "staffservice.h"
#include "hotelservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLogIn_clicked();

    void on_btnQuit_clicked();

private:
    Ui::MainWindow *ui;

    StaffService* m_staffService;
    HotelService* m_hotelService;
};
#endif // MAINWINDOW_H
