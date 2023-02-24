//-------------------------------------------
//dbroomtype.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理roomType表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "dbroomtype.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DBRoomType::DBRoomType(QObject *parent) : QObject(parent)
{
    initDatabase();
}

DBRoomType::~DBRoomType()
{
    if(m_db.isOpen())
        m_db.close();
}

//初始化数据库连接
void DBRoomType::initDatabase()
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
        qDebug() << "[DBRoomType::initDataBase]:: " << m_db.lastError().text();
        return;
    }
}

//获取roomType表
QVector<QMap<QString, QString> > DBRoomType::getRoomTypeList()
{
    QVector<QMap<QString, QString>> list;
    bool ok = false;
    QSqlQuery query;
    QString sql = "select * from roomType";
    query.prepare(sql);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBRoomType::getRoomTypeList]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["roomType"] = query.value(0).toString();
        temMap["todayPrice"] = query.value(1).toString();
        temMap["normalPrice"] = query.value(2).toString();
        temMap["vipPrice"] = query.value(3).toString();
        temMap["image"] = query.value(4).toString();
        list.append(temMap);
    }
    return list;
}
