//-------------------------------------------
//dbroom.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理room表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "dbroom.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DBRoom::DBRoom(QObject *parent) : QObject(parent)
{
    initDatabase();
}

DBRoom::~DBRoom()
{
    if(m_db.isOpen())
            m_db.close();
}

//初始化数据库
void DBRoom::initDatabase()
{
    bool ok;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("Hotel.db");
    }

    ok = m_db.open();
    if(!ok)
    {
        qDebug() << "[Admin::initDataBase]:: " << m_db.lastError().text();
        return;
    }
}

//获取room表
QVector<QMap<QString, QString> > DBRoom::getRoomList()
{
    bool ok = false;
    QSqlQuery query;
    QVector<QMap<QString, QString>> list;
    QString sql = "select * from room";

    query.prepare(sql);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBRoom::getRoomList]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["roomId"] = query.value(0).toString();
        temMap["roomStatus"] = query.value(1).toString();
        temMap["userId"] = query.value(2).toString();
        temMap["roomType"] = query.value(3).toString();
        list.append(temMap);
    }

    return list;
}

//根据搜索的内容返回room表
QVector<QMap<QString, QString> > DBRoom::searchRoom(QString& item)
{
    bool ok = false;
    QSqlQuery query;
    QVector<QMap<QString, QString>> list;
    QString sql = "select * from room where roomId = ? or roomType = ? or roomStatus = ?";
    query.prepare(sql);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBRoom::searchRoom]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["roomId"] = query.value(0).toString();
        temMap["roomStatus"] = query.value(1).toString();
        temMap["userId"] = query.value(2).toString();
        temMap["roomType"] = query.value(3).toString();
        list.append(temMap);
    }

    return list;
}

//登记操作
bool DBRoom::checkIn(QString &roomId, QString &userId)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "update room set roomStatus = '占用' , userId = ? where roomId = ?";
    query.prepare(sql);
    query.addBindValue(userId);
    query.addBindValue(roomId);

    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBRoom::checkIn]:: " << m_db.lastError().text();
    }

    return ok;
}

//退房操作
bool DBRoom::checkOut(QString &roomId)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "update room set roomStatus = '空闲' , userId = '无' where roomId = ?";
    query.prepare(sql);
    query.addBindValue(roomId);

    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBRoom::checkOut]:: " << m_db.lastError().text();
    }

    return ok;
}
