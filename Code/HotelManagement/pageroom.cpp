//-------------------------------------------
//pageroom.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//客房信息查询界面逻辑
//Copyright 2022 黄天宇
//-------------------------------------------

#include "hotelmanagement.h"
#include "ui_hotelmanagement.h"

#include <QMessageBox>

//搜索框回车事件
void HotelManagement::on_editSearchRoom_returnPressed()
{
    QString str = ui->editSearchRoom->text();
    if(str == "")
    {
        on_btnFlush_clicked();
    }
    else
    {
        QVector<QMap<QString, QString>> list = m_roomService->searchRoom(str);
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
            showRoom(list);
        }

    }
}


//刷新按钮点击事件
void HotelManagement::on_btnFlush_clicked()
{
    ui->editSearchRoom->clear();
    QVector<QMap<QString, QString>> list = m_roomService->getRoomList();
    showRoom(list);
}

//根据list显示room表
void HotelManagement::showRoom(QVector<QMap<QString, QString> > &list)
{
    m_modelRoom = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("房间号,房间状态,房间类型").simplified().split(",");
    m_modelRoom->setHorizontalHeaderLabels(labels);

    //定义item
    QStandardItem* item;
    for(int i = 0;i < list.size();i++){
        item = new QStandardItem(list[i]["roomId"]);
        m_modelRoom->setItem(i,0,item);
        item = new QStandardItem(list[i]["roomStatus"]);
        m_modelRoom->setItem(i,1,item);
        item = new QStandardItem(list[i]["roomType"]);
        m_modelRoom->setItem(i,2,item);
        if(list[i]["roomStatus"] == "空闲")
        {
            m_modelRoom->item(i, 1)->setForeground(QBrush(QColor(170, 255, 0)));
        }
        else
        {
            m_modelRoom->item(i, 1)->setForeground(QBrush(QColor(255, 85, 0)));
        }
    }


    ui->tableViewRoom->setModel(m_modelRoom);
    ui->tableViewRoom->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewRoom->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#455364;}");
    ui->tableViewRoom->verticalHeader()->hide();

    ui->tableViewRoom->show();
}


//初始化房间查询界面
void HotelManagement::initPageRoom()
{
    ui->tableViewRoom->setEditTriggers(QAbstractItemView::NoEditTriggers);
    on_btnFlush_clicked();
}
