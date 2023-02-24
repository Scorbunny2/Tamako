//-------------------------------------------
//pagehome.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//当日价格查询界面逻辑
//Copyright 2022 黄天宇
//-------------------------------------------

#include "hotelmanagement.h"
#include "ui_hotelmanagement.h"

//初始化主页房间类型展示
void HotelManagement::initRoomTypeTable()
{
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_modelRoomType = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("房型,今日价格,门市价格,会员价格").simplified().split(",");
    m_modelRoomType->setHorizontalHeaderLabels(labels);
    QVector<QMap<QString,QString>> list = m_roomTypeService->getRoomTypeList();

    //定义item
    QStandardItem* item;
    for(int i = 0;i < list.size();i++){
        item = new QStandardItem(list[i]["roomType"]);
        m_modelRoomType->setItem(i,0,item);
        item = new QStandardItem(list[i]["todayPrice"]);
        m_modelRoomType->setItem(i,1,item);
        item = new QStandardItem(list[i]["normalPrice"]);
        m_modelRoomType->setItem(i,2,item);
        item = new QStandardItem(list[i]["vipPrice"]);
        m_modelRoomType->setItem(i,3,item);
    }
    ui->tableView->setModel(m_modelRoomType);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#455364;}");
    ui->tableView->QTableView::verticalHeader()->hide();
    setImage(list[0]["roomType"]);
    ui->tableView->show();
}

//根据房间类型设置图片
void HotelManagement::setImage(QString &roomType)
{
    QVector<QMap<QString,QString>> list = m_roomTypeService->getRoomTypeList();
    for(int i = 0;i < list.size();i++){
        if(list[i]["roomType"] == roomType)
        {
            QPixmap image(list[i]["image"]);
            ui->labelImage->setPixmap(image);
            break;
        }
    }
}

//表格点击事件，根据选择的内容显示相应的图片
void HotelManagement::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QString cellText = index.data().toString();
    }

    QModelIndex index2 = m_modelRoomType->index(index.row(), 0);
    QString roomType = m_modelRoomType->data(index2).toString();

    setImage(roomType);
}
