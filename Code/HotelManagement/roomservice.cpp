//-------------------------------------------
//roomservice.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理和room表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "roomservice.h"

RoomService::RoomService(QObject *parent) : QObject(parent)
{
    m_dbRoom = new DBRoom;
}

RoomService::~RoomService()
{
    delete m_dbRoom;
}

//获取房间列表
QVector<QMap<QString, QString> > RoomService::getRoomList()
{
    return m_dbRoom->getRoomList();
}

//根据搜索的内容返回房间列表
QVector<QMap<QString, QString> > RoomService::searchRoom(QString& item)
{
    return m_dbRoom->searchRoom(item);
}

//登记入住操作
bool RoomService::checkIn(QString &roomId, QString &userId)
{
    return m_dbRoom->checkIn(roomId, userId);
}

//退房操作
bool RoomService::checkOut(QString &roomId)
{
    return m_dbRoom->checkOut(roomId);
}

//根据房间号码获取房间类型
QString RoomService::getRoomType(QString &roomNumber)
{
    QString roomType;

    QVector<QMap<QString, QString> > roomList = m_dbRoom->getRoomList();
    for(int i = 0; i < roomList.size(); i++)
    {
        if(roomList[i]["roomId"] == roomNumber)
        {
           roomType = roomList[i]["roomType"];
           break;
        }
    }

    return roomType;
}
