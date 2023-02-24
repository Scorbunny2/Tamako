//-------------------------------------------
//roomtype.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理和roomType表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "roomtypeservice.h"

RoomTypeService::RoomTypeService(QObject *parent) : QObject(parent)
{
    m_dbRoomType = new DBRoomType;
    m_roomTypeList = m_dbRoomType->getRoomTypeList();
}

RoomTypeService::~RoomTypeService()
{
    delete m_dbRoomType;
}

//获取房间类型列表
QVector<QMap<QString, QString> > RoomTypeService::getRoomTypeList()
{
    return m_roomTypeList;
}

//根据房间类型和用户身份获取价格
QString RoomTypeService::getPrice(QString &userPermission, QString &roomType)
{
    QString price;
    for(int i = 0; i < m_roomTypeList.size(); i++)
    {
        if(m_roomTypeList[i]["roomType"] == roomType)
        {
            if(userPermission == "普通用户")
            {
                price = m_roomTypeList[i]["todayPrice"];
                break;
            }
            else if(userPermission == "会员用户")
            {
                price = m_roomTypeList[i]["vipPrice"];
                break;
            }
        }
    }

    return price;
}
