//-------------------------------------------
//dbstaff.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理staff表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "dbstaff.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DBStaff::DBStaff(QObject *parent) : QObject(parent)
{
    initDatabase();
}

DBStaff::~DBStaff()
{
    if(m_db.isOpen())
        m_db.close();
}

//初始化数据库连接
void DBStaff::initDatabase()
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
        qDebug() << "[DBStaff::initDataBase]:: " << m_db.lastError().text();
        return;
    }
}

//获取员工表
QVector<QMap<QString, QString> > DBStaff::getStaffList()
{
    bool ok = false;
    QSqlQuery query;
    QVector<QMap<QString, QString>> list;
    QString sql = "select * from staff";

    query.prepare(sql);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBStaff::getStaffList]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["userName"] = query.value(0).toString();
        temMap["passwd"] = query.value(1).toString();
        temMap["name"] = query.value(2).toString();
        temMap["phoneNumber"] = query.value(3).toString();
        temMap["sex"] = query.value(4).toString();
        temMap["birthday"] = query.value(5).toString();
        temMap["address"] = query.value(6).toString();
        temMap["email"] = query.value(7).toString();
        list.append(temMap);
    }

    return list;
}

//删除员工
bool DBStaff::deleteStaff(QString &userName)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "delete from staff where userName = ?";

    query.prepare(sql);
    query.addBindValue(userName);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBStaff::deleteStaff]:: " << m_db.lastError().text();
    }

    return ok;
}

//添加员工
bool DBStaff::addStaff(QMap<QString, QString> &staff)
{
    bool ok = false;
    QSqlQuery query;
    QString sql = "insert into staff values(?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(staff["userName"]);
    query.addBindValue(staff["passwd"]);
    query.addBindValue(staff["name"]);
    query.addBindValue(staff["phoneNumber"]);
    query.addBindValue(staff["sex"]);
    query.addBindValue(staff["birthday"]);
    query.addBindValue(staff["address"]);
    query.addBindValue(staff["email"]);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBStaff::addStaff]:: " << m_db.lastError().text();
    }

    return ok;
}

//检查员工账号密码是否匹配
bool DBStaff::checkStaff(QString &userName, QString &passwd)
{
    bool ok;
    QSqlQuery query;
    QString temPasswd;

    QString sql = "select passwd from staff where userName = ?";
    query.prepare(sql);
    query.addBindValue(userName);

    ok = query.exec();

    if(!ok)
    {
        return false;
    }

    while(query.next())
    {
        temPasswd = query.value(0).toString();
    }

    if(passwd == temPasswd)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//根据内容返回搜索到的员工表
QVector<QMap<QString, QString> > DBStaff::serachStaff(QString &item)
{
    bool ok = false;
    QSqlQuery query;
    QVector<QMap<QString, QString>> list;
    QString sql = "select * from staff where userName = ? or name = ? or phoneNumber = ? or sex = ? or birthday = ? or email = ?";
    query.prepare(sql);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    query.addBindValue(item);
    ok = query.exec();
    if(!ok)
    {
        qDebug() << "[DBStaff::searchStaff]:: " << m_db.lastError().text();
        return list;
    }
    while(query.next())
    {
        QMap<QString, QString> temMap;
        temMap["userName"] = query.value(0).toString();
        temMap["passwd"] = query.value(1).toString();
        temMap["name"] = query.value(2).toString();
        temMap["phoneNumber"] = query.value(3).toString();
        temMap["sex"] = query.value(4).toString();
        temMap["birthday"] = query.value(5).toString();
        temMap["address"] = query.value(6).toString();
        temMap["email"] = query.value(7).toString();
        list.append(temMap);
    }

    return list;
}

