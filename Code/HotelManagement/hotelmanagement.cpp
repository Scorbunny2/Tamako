//-------------------------------------------
//hotelmanagement.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//酒店管理界面的按钮跳转逻辑和初始化
//Copyright 2022 黄天宇
//-------------------------------------------

#include "hotelmanagement.h"
#include "ui_hotelmanagement.h"
#include <QAction>

HotelManagement::HotelManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotelManagement)
{

    init();
    initRoomTypeTable();
    initPageStaff();
    initPageRoom();
    initPageUser();
    on_btnPage1_clicked();
}

HotelManagement::~HotelManagement()
{
    delete ui;
    delete m_roomTypeService;
    delete m_modelRoom;
    delete m_modelRoomType;
    delete m_staffService;
    delete m_roomService;
    delete m_modelUser;
    delete m_modelStaff;
}

//初始化操作
void HotelManagement::init()
{
    m_roomTypeService = new RoomTypeService;
    m_staffService = new StaffService;
    m_roomService = new RoomService;
    m_userService = new UserService;

    ui->setupUi(this);
    this->setWindowTitle("酒店管理系统");
    QIcon icon(":/icon/icon.png");
    this->setWindowIcon(icon);

    QAction *searchAction = new QAction(this);
    searchAction->setIcon(QIcon(":/icon/sousuo.png"));
    ui->editSearchRoom->addAction(searchAction,QLineEdit::LeadingPosition);
    ui->editSearchUser->addAction(searchAction,QLineEdit::LeadingPosition);
    ui->editSearchStaff->addAction(searchAction,QLineEdit::LeadingPosition);
}

//界面切换按钮点击事件
void HotelManagement::on_btnPage1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//界面切换按钮点击事件
void HotelManagement::on_btnPage2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//界面切换按钮点击事件
void HotelManagement::on_btnPage3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//界面切换按钮点击事件
void HotelManagement::on_btnPage4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
