//-------------------------------------------
//roomtype.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理和roomType表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef ROOMTYPESERVICE_H
#define ROOMTYPESERVICE_H

#include <QObject>
#include <dbroomtype.h>
#include <QVector>
#include <QMap>

class RoomTypeService : public QObject
{
    Q_OBJECT
public:
    explicit RoomTypeService(QObject *parent = nullptr);
    ~RoomTypeService();
    QVector<QMap<QString, QString>> getRoomTypeList();  //获取房间类型列表
    QString getPrice(QString& userPermission, QString& roomType);   //根据房间类型和用户身份获取价格

private:
    DBRoomType * m_dbRoomType;
    QVector<QMap<QString, QString>> m_roomTypeList;

signals:

public slots:
};

#endif // ROOMTYPESERVICE_H
