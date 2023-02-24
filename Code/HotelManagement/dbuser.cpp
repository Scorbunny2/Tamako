//-------------------------------------------
//dbuser.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理user表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "dbuser.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DBUser::DBUser(QObject *parent) : QObject(parent)
{
    initDataBase();
}

DBUser::~DBUser()
{
    if(m_db.isOpen())
        m_db.close();
}

//初始化数据库连接
void DBUser::initDataBase()
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
        qDebug() << "[DBUser::initDataBase]:: " << m_db.lastError().text();
        return;
    }
}

//添加用户
bool DBUser::addUser(QMap<QString, QString> &user)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "insert into user values(?, ?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(user["Id"]);
    query.addBindValue(user["name"]);
    query.addBindValue(user["userPhone"]);
    query.addBindValue(user["roomNumber"]);
    query.addBindValue(user["userState"]);
    query.addBindValue(user["userPermission"]);
    query.addBindValue(user["consumeMoney"]);
    query.addBindValue(user["checkIn"]);
    query.addBindValue(user["checkOut"]);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBUser::addUser]:: " << m_db.lastError().text();
    }

    return ok;
}

//获取用户列表
QVector<QMap<QString, QString> > DBUser::getUserList()
{
    bool ok = false;
    QSqlQuery query;
    QVector<QMap<QString, QString>> list;
    QString sql = "select * from user";

    query.prepare(sql);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBUser::getUserList]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["Id"] = query.value(0).toString();
        temMap["name"] = query.value(1).toString();
        temMap["userPhone"] = query.value(2).toString();
        temMap["roomNumber"] = query.value(3).toString();
        temMap["userState"] = query.value(4).toString();
        temMap["userPermission"] = query.value(5).toString();
        temMap["consumeMoney"] = query.value(6).toString();
        temMap["checkIn"] = query.value(7).toString();
        temMap["checkOut"] = query.value(8).toString();
        list.append(temMap);
    }

    return list;
}

//根据搜索内容返回用户列表
QVector<QMap<QString, QString> > DBUser::searchUser(QString &item)
{
    bool ok = false;
    QSqlQuery query;
    QVector<QMap<QString, QString>> list;
    QString sql = "select * from user where Id = ? or name = ? or userPhone = ? or roomNumber = ? "
                  "or userState = ? or userPermission = ? or checkIn = ? or checkOut = ?";
    query.prepare(sql);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBUser::searchUser]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["Id"] = query.value(0).toString();
        temMap["name"] = query.value(1).toString();
        temMap["userPhone"] = query.value(2).toString();
        temMap["roomNumber"] = query.value(3).toString();
        temMap["userState"] = query.value(4).toString();
        temMap["userPermission"] = query.value(5).toString();
        temMap["consumeMoney"] = query.value(6).toString();
        temMap["checkIn"] = query.value(7).toString();
        temMap["checkOut"] = query.value(8).toString();
        list.append(temMap);
    }

    return list;
}

//删除用户
bool DBUser::deleteUser(QString &Id)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "delete from user where userName = ?";

    query.prepare(sql);
    query.addBindValue(Id);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBUser::deleteUser]:: " << m_db.lastError().text();
    }

    return ok;
}

//退房
bool DBUser::checkOut(QString &Id, QString &consumeMoney, QString &checkOut)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "update user set consumeMoney = ? , checkOut = ? , userState = '离店' where Id = ?";
    query.prepare(sql);
    query.addBindValue(consumeMoney);
    query.addBindValue(checkOut);
    query.addBindValue(Id);

    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBUser::checkOut]:: " << m_db.lastError().text();
    }

    return ok;
}

