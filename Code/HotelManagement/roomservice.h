//-------------------------------------------
//roomservice.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理和room表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "dbroom.h"

class RoomService : public QObject
{
    Q_OBJECT
public:
    explicit RoomService(QObject *parent = nullptr);
    ~RoomService();
    QVector<QMap<QString, QString>> getRoomList();  //获取房间列表
    QVector<QMap<QString, QString> > searchRoom(QString &item); //根据搜索的内容返回房间列表
    bool checkIn(QString& roomId, QString& userId); //登记入住操作
    bool checkOut(QString& roomId); //退房操作
    QString getRoomType(QString& roomNumber); //根据房间号码获取房间类型

private:
    DBRoom *m_dbRoom;


signals:

public slots:
};

#endif // ROOMSERVICE_H
