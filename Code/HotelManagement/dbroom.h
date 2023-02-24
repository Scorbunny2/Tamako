//-------------------------------------------
//dbroom.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理room表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef DBROOM_H
#define DBROOM_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QMap>

class DBRoom : public QObject
{
    Q_OBJECT
public:
    explicit DBRoom(QObject *parent = nullptr);
    ~DBRoom();
    void initDatabase();    //初始化数据库
    QVector<QMap<QString, QString>> getRoomList();  //获取room表
    QVector<QMap<QString, QString>> searchRoom(QString& item);  //根据搜索的内容返回room表
    bool checkIn(QString& roomId, QString& userId); //登记操作
    bool checkOut(QString& roomId); //退房操作

private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DBROOM_H
