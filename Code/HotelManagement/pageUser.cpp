//-------------------------------------------
//pageuser.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//客房信息登记界面逻辑
//Copyright 2022 黄天宇
//-------------------------------------------

#include "hotelmanagement.h"
#include "ui_hotelmanagement.h"

#include <QMessageBox>

//初始化客房信息登记界面
void HotelManagement::initPageUser()
{
    ui->tableViewUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVector<QMap<QString,QString>> roomTypelist = m_roomTypeService->getRoomTypeList();

    for(int i = 0; i < roomTypelist.size(); i++)
    {
        ui->comboBoxRoomTypePgU1->addItem(roomTypelist[i]["roomType"]);
    }

    ui->dateEditCheckInPgU1->setDisplayFormat("yyyy/MM/dd");
    ui->dateEditCheckOutPgU2->setDisplayFormat("yyyy/MM/dd");

    ui->buttonGroup->setId(ui->radioButton, 1);
    ui->buttonGroup->setId(ui->radioButton_2, 2);

    ui->editNamePgU2->setReadOnly(true);
    ui->editIdPgU2->setReadOnly(true);
    ui->editCheckOutMessagePgU2->setReadOnly(true);

    on_btnResetPgU1_clicked();
    on_btnResetPgU2_clicked();
}

//在editText中显示退房账单
void HotelManagement::showCheckOutMessage(QString &checkIn, QString &checkOut, QString &name, QString &Id, QString &roomNumber, QString &consumeMoney)
{
    ui->editCheckOutMessagePgU2->append("-------------------退房账单-------------------");
    ui->editCheckOutMessagePgU2->append("           姓    名: " + name);
    ui->editCheckOutMessagePgU2->append("           身份证号: " + Id);
    ui->editCheckOutMessagePgU2->append("           房 间 号: " + roomNumber);
    ui->editCheckOutMessagePgU2->append("           入住时间: " + checkIn);
    ui->editCheckOutMessagePgU2->append("           退房时间: " + checkOut);
    ui->editCheckOutMessagePgU2->append("           消费价格: " + consumeMoney);
    ui->editCheckOutMessagePgU2->append("----------------------------------------------");
    ui->editCheckOutMessagePgU2->append("");
}

//重置按钮点击事件
void HotelManagement::on_btnResetPgU1_clicked()
{
    ui->editIdPgU1->clear();
    ui->editNamePgU1->clear();
    ui->editPhonePgU1->clear();
    ui->comboBoxRoomIdPgU1->clear();
    ui->comboBoxRoomTypePgU1->setCurrentIndex(-1);
    ui->dateEditCheckInPgU1->setDateTime(QDateTime::currentDateTime());
}

//房间类型下拉菜单选择事件
void HotelManagement::on_comboBoxRoomTypePgU1_activated(const QString &arg1)
{
    ui->comboBoxRoomIdPgU1->clear();

    QVector<QMap<QString,QString>> roomList = m_roomService->getRoomList();

    for(int i = 0; i < roomList.size(); i++)
    {
        if(roomList[i]["roomType"] == arg1 && roomList[i]["roomStatus"] == "空闲")
        {
            ui->comboBoxRoomIdPgU1->addItem(roomList[i]["roomId"]);
        }
    }

    ui->comboBoxRoomIdPgU1->setCurrentIndex(-1);
}

//登记按钮点击事件
void HotelManagement::on_btnCheckInPgU1_clicked()
{
    QString Id = ui->editIdPgU1->text();
    QString name = ui->editNamePgU1->text();
    QString phone = ui->editPhonePgU1->text();
    QString roomId = ui->comboBoxRoomIdPgU1->currentText();
    QString checkIn = ui->dateEditCheckInPgU1->text();
    QString userState = "入住";
    QString userPermission = "";
    int btnId = ui->buttonGroup->checkedId();
    if(btnId == 1)
    {
        userPermission = "普通用户";
    }
    else if(btnId == 2)
    {
        userPermission = "会员用户";
    }

    QMap<QString, QString> temMap;
    temMap["Id"] = Id;
    temMap["name"] = name;
    temMap["userPhone"] = phone;
    temMap["roomNumber"] = roomId;
    temMap["checkIn"] = checkIn;
    temMap["userState"] = userState;
    temMap["userPermission"] = userPermission;
    temMap["checkOut"] = "无";
    temMap["consumeMoney"] = "无";

    if(Id == "" || name == "" || phone == "" || roomId == ""
            || checkIn == "" || userState == "" || userPermission == "")
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("信息输入不完整"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
    else
    {
        bool ok;
        ok = m_userService->checkIn(temMap, roomId);
        if(!ok)
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("登记失败"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this,
                tr("提示"),
                tr("登记成功"),
                QMessageBox::Ok | QMessageBox::Cancel,
                QMessageBox::Ok);
            on_btnResetPgU1_clicked();
            on_btnResetPgU2_clicked();
            on_btnFlush_clicked();
            m_userService->updateUserList();
        }
    }
}

//重置按钮点击事件
void HotelManagement::on_btnResetPgU2_clicked()
{
    ui->comboBoxRoomIdPgU2->clear();

    QVector<QMap<QString,QString>> roomList = m_roomService->getRoomList();

    for(int i = 0; i < roomList.size(); i++)
    {
        if(roomList[i]["roomStatus"] == "占用")
        {
            ui->comboBoxRoomIdPgU2->addItem(roomList[i]["roomId"]);
        }
    }

    ui->comboBoxRoomIdPgU2->setCurrentIndex(-1);
    ui->editNamePgU2->clear();
    ui->editIdPgU2->clear();
    ui->dateEditCheckOutPgU2->setDateTime(QDateTime::currentDateTime());
}

//房间号下拉菜单选择事件
void HotelManagement::on_comboBoxRoomIdPgU2_activated(const QString &arg1)
{
    QVector<QMap<QString, QString>> userList = m_userService->getUserList();

    for(int i = 0; i < userList.size(); i++)
    {
        if(userList[i]["roomNumber"] == arg1)
        {
            ui->editIdPgU2->setText(userList[i]["Id"]);
            ui->editNamePgU2->setText(userList[i]["name"]);
        }
    }
}

//退房按钮点击事件
void HotelManagement::on_btnCheckOutPgU2_clicked()
{
    QString roomNumber = ui->comboBoxRoomIdPgU2->currentText();
    QString checkOut = ui->dateEditCheckOutPgU2->text();
    QString Id = ui->editIdPgU2->text();
    QString name = ui->editNamePgU2->text();
    QString userPermission;
    QString checkIn;
    QString roomType;
    int price = 0;

    if(Id == "" || checkOut == "")
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("信息输入不完整"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }

    QVector<QMap<QString, QString>> userList = m_userService->getUserList();
    for(int i = 0; i < userList.size(); i++)
    {
        if(userList[i]["Id"] == Id)
        {
            checkIn = userList[i]["checkIn"];
            userPermission = userList[i]["userPermission"];
            break;
        }
    }

    roomType = m_roomService->getRoomType(roomNumber);
    price = m_roomTypeService->getPrice(userPermission, roomType).toInt();

    QDateTime checkInTime = QDateTime::fromString(checkIn, "yyyy/mm/dd");
    QDateTime checkOutTime = QDateTime::fromString(checkOut, "yyyy/mm/dd");
    int days = checkInTime.daysTo(checkOutTime);
    int totalPrice = days * price;
    QString consumeMoney = QString::number(totalPrice);


    bool ok = m_userService->checkOut(Id, consumeMoney, checkOut, roomNumber);

    if(ok)
    {
        showCheckOutMessage(checkIn, checkOut, name, Id, roomNumber, consumeMoney);
        QMessageBox::information(this,
            tr("提示"),
            tr("退房成功"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        on_btnFlush_clicked();
        on_btnResetPgU1_clicked();
        on_btnResetPgU2_clicked();
        m_userService->updateUserList();
    }
    else
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("退房失败"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }


}

//用户搜索按钮回车事件
void HotelManagement::on_editSearchUser_returnPressed()
{
    QString item = ui->editSearchUser->text();
    QVector<QMap<QString, QString>> list = m_userService->searchUser(item);
    if(list.empty())
    {
        QMessageBox::information(this,
            tr("提示"),
            tr("未找到结果"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
    }
    else
    {
        showUser(list);
    }
}

 //根据list显示user表
void HotelManagement::showUser(QVector<QMap<QString, QString> > &list)
{
    m_modelUser = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("姓名,身份证号,手机号,用户权限,房间号,状态,入住时间,退房时间,消费金额").simplified().split(",");
    m_modelUser->setHorizontalHeaderLabels(labels);

    //定义item
    QStandardItem* item;
    for(int i = 0;i < list.size();i++){
        item = new QStandardItem(list[i]["name"]);
        m_modelUser->setItem(i,0,item);
        item = new QStandardItem(list[i]["Id"]);
        m_modelUser->setItem(i,1,item);
        item = new QStandardItem(list[i]["userPhone"]);
        m_modelUser->setItem(i,2,item);
        item = new QStandardItem(list[i]["userPermission"]);
        m_modelUser->setItem(i,3,item);
        item = new QStandardItem(list[i]["roomNumber"]);
        m_modelUser->setItem(i,4,item);
        item = new QStandardItem(list[i]["userState"]);
        m_modelUser->setItem(i,5,item);
        item = new QStandardItem(list[i]["checkIn"]);
        m_modelUser->setItem(i,6,item);
        item = new QStandardItem(list[i]["checkOut"]);
        m_modelUser->setItem(i,7,item);
        item = new QStandardItem(list[i]["consumeMoney"]);
        m_modelUser->setItem(i,8,item);
        if(list[i]["userState"] == "入住")
        {
            m_modelUser->item(i, 5)->setForeground(QBrush(QColor(170, 255, 0)));
        }
        else
        {
            m_modelUser->item(i, 5)->setForeground(QBrush(QColor(255, 85, 0)));
        }

        if(list[i]["userPermission"] == "会员用户")
        {
            m_modelUser->item(i, 3)->setForeground(QBrush(QColor(255, 255, 127)));
        }
    }


    ui->tableViewUser->setModel(m_modelUser);
    ui->tableViewUser->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewUser->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#455364;}");
    ui->tableViewUser->verticalHeader()->hide();

    ui->tableViewUser->show();
}
