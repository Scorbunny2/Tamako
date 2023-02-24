//-------------------------------------------
//mainwindow.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//登陆界面
//Copyright 2022 黄天宇
//-------------------------------------------

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMessageBox>
#include <QRegExpValidator>
#include "hotelmanagement.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("登陆");
    QIcon icon(":/icon/icon.png");
    this->setWindowIcon(icon);

    QAction *useraction = new QAction(this);
    useraction->setIcon(QIcon(":/icon/yonghu.png"));
    ui->editUser->addAction(useraction,QLineEdit::LeadingPosition);

    QAction *passwdaction = new QAction(this);
    passwdaction->setIcon(QIcon(":/icon/mima.png"));
    ui->editPasswd->addAction(passwdaction,QLineEdit::LeadingPosition);

    ui->editUser->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));
    ui->editPasswd->setEchoMode(QLineEdit::Password);

    ui->editUser->setText("admin");
    ui->editPasswd->setText("admin");

    m_hotelService = new HotelService;
    m_staffService = new StaffService;
}

MainWindow::~MainWindow()
{
    delete m_staffService;
    delete m_hotelService;
    delete ui;
}

//登陆按钮点击事件
void MainWindow::on_btnLogIn_clicked()
{
    QString userName = ui->editUser->text();
    QString passwd = ui->editPasswd->text();
    bool ok;

    if(userName != "" && passwd != "")
    {
        ok = m_staffService->checkStaff(userName, passwd);
        if(ok)
        {
            HotelManagement* newWindow = new HotelManagement;
            this->close();
            newWindow->show();
        }
        else
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("账号和密码错误,请重试"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("账号和密码不能为空"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
}

//退出按钮点击事件
void MainWindow::on_btnQuit_clicked()
{
    this->close();
}
