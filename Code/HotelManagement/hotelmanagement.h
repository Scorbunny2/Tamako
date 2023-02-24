//-------------------------------------------
//hotelmanagement.h
//创建者：黄天宇
//创建时间：2022/6/14
//酒店管理界面头文件
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef HOTELMANAGEMENT_H
#define HOTELMANAGEMENT_H

#include <QStandardItemModel>
#include <QWidget>
#include <QVector>
#include <QMap>
#include "roomtypeservice.h"
#include "staffservice.h"
#include "roomservice.h"
#include "userservice.h"


namespace Ui {
class HotelManagement;
}

class HotelManagement : public QWidget
{
    Q_OBJECT

public:
    explicit HotelManagement(QWidget *parent = nullptr);
    ~HotelManagement();
    void init();    //初始化操作
    void initRoomTypeTable();   //初始化主页房间类型展示
    void setImage(QString &roomType);   //根据房间类型设置图片
    void initPageStaff();   //初始化员工信息管理界面
    void initPageRoom();    //初始化房间查询界面
    void updatePageStaff(); //更新员工管理界面
    void showRoom(QVector<QMap<QString, QString>>& list);   //根据list显示room表
    void showUser(QVector<QMap<QString, QString>>& list);   //根据list显示user表
    void initPageUser();    //初始化客房信息登记界面
    //在editText中显示退房账单
    void showCheckOutMessage(QString& checkIn, QString& checkOut, QString& name, QString& Id, QString& roomNumber, QString& consumeMoney);
    void showStaff(QVector<QMap<QString, QString>> &list);  //根据list显示staff表

private slots:
    void on_btnPage1_clicked();

    void on_btnPage2_clicked();

    void on_btnPage3_clicked();

    void on_btnPage4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_btnResetPgS1_clicked();

    void on_comboBoxUserNamePgS2_activated(const QString &arg1);

    void on_btnRegisterPgS1_clicked();

    void on_btnDeletePgS2_clicked();

    void on_btnChangePgS2_clicked();

    void on_btnFlush_clicked();

    void on_editSearchRoom_returnPressed();

    void on_btnResetPgU1_clicked();

    void on_comboBoxRoomTypePgU1_activated(const QString &arg1);

    void on_btnCheckInPgU1_clicked();

    void on_btnResetPgU2_clicked();

    void on_comboBoxRoomIdPgU2_activated(const QString &arg1);

    void on_btnCheckOutPgU2_clicked();

    void on_editSearchUser_returnPressed();

    void on_editSearchStaff_returnPressed();

private:
    Ui::HotelManagement *ui;
    RoomTypeService *m_roomTypeService;
    StaffService *m_staffService;
    RoomService *m_roomService;
    UserService *m_userService;
    QStandardItemModel* m_modelRoomType;
    QStandardItemModel* m_modelRoom;
    QStandardItemModel* m_modelUser;
    QStandardItemModel* m_modelStaff;
};

#endif // HOTELMANAGEMENT_H
