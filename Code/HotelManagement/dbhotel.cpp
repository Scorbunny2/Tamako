//-------------------------------------------
//dbhotel.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//初始化数据库
//Copyright 2022 黄天宇
//-------------------------------------------

#include "dbhotel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DBHotel::DBHotel()
{
    initDatabase();
    createTables();
    addAdmin();
    addRoomType();
    addRoom();
}

DBHotel::~DBHotel()
{
    if(m_db.isOpen())
        m_db.close();
}

//初始化数据库
void DBHotel::initDatabase()
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

//创建表
void DBHotel::createTables()
{
    bool ok;
    QSqlQuery query;

    QString sql = "CREATE TABLE IF NOT EXISTS staff(userName text primary key,"
                                     "passwd text not null,"
                                     "name text not null,"
                                     "phoneNumber text not null,"
                                     "sex text not null,"
                                     "birthday text not null,"
                                     "address text not null,"
                                     "email text not null)";

    ok = query.exec(sql); //执行 SQL 语句
    if(!ok)
    {
        qDebug() << "[Admin::createTables:satff]: " << query.lastError().text();
        return;
    }

    sql = "CREATE TABLE IF NOT EXISTS roomType(type text primary key,"
                                                "todayPrice text not null,"
                                                "normalPrice text not null,"
                                                "vipPrice text not null,"
                                                "image text not null)";

    ok = query.exec(sql); //执行 SQL 语句
    if(!ok)
    {
        qDebug() << "[Admin::createTables:roomType]: " << query.lastError().text();
        return;
    }

    sql = "CREATE TABLE IF NOT EXISTS room(roomId text primary key,"
                                                "roomStatus text not null,"
                                                "userId text not null,"
                                                "roomType text not null)";

    ok = query.exec(sql); //执行 SQL 语句
    if(!ok)
    {
        qDebug() << "[Admin::createTables:room]: " << query.lastError().text();
        return;
    }

    sql = "CREATE TABLE IF NOT EXISTS user(Id text primary key,"
                                                "name text not null,"
                                                "userPhone text not null,"
                                                "roomNumber text not null,"
                                                "userState text not null,"
                                                "userPermission text not null,"
                                                "consumeMoney text not null,"
                                                "checkIn text not null,"
                                                "checkOut text not null)";

    ok = query.exec(sql); //执行 SQL 语句
    if(!ok)
    {
        qDebug() << "[Admin::createTables:user]: " << query.lastError().text();
        return;
    }
}

//添加管理员账户
void DBHotel::addAdmin()
{
    bool ok;
    QSqlQuery query;

    QString sql = "insert or ignore into staff values('admin', 'admin', '黄天宇', '15272755297', "
                  "'男', '2001/6/1', '武汉科技大学', '1755879757@qq.com')";
    ok = query.exec(sql); //执行 SQL 语句
    if(!ok)
    {
        qDebug() << "[Admin::addAdmin]: " << query.lastError().text();
        return;
    }
}

//添加roomType默认数据
void DBHotel::addRoomType()
{
    QSqlQuery query;
    QString sql;
    sql = "insert or ignore into roomType values ('单人间', '120', '160', '100', ':/room/single.jpg')";
    query.exec(sql);
    sql = "insert or ignore into roomType values ('标准间', '180', '220', '160', ':/room/double.jpg')";
    query.exec(sql); //执行 SQL 语句
    sql = "insert or ignore into roomType values ('大床房', '160', '200', '140', ':/room/kingbed.jpg')";
    query.exec(sql); //执行 SQL 语句
    sql = "insert or ignore into roomType values ('商务套间', '200', '240', '180', ':/room/business.jpg')";
    query.exec(sql);
    sql = "insert or ignore into roomType values ('豪华套间', '300', '340', '280', ':/room/suite.jpg')";
    query.exec(sql);
}

//添加room默认数据
void DBHotel::addRoom()
{
    QSqlQuery query;
    QString sql;
    sql = "insert or ignore into room values ('101', '空闲', '无', '单人间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('102', '空闲', '无', '单人间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('103', '空闲', '无', '单人间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('104', '空闲', '无', '单人间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('105', '空闲', '无', '单人间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('106', '空闲', '无', '单人间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('201', '空闲', '无', '标准间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('202', '空闲', '无', '标准间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('203', '空闲', '无', '标准间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('204', '空闲', '无', '标准间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('205', '空闲', '无', '标准间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('206', '空闲', '无', '标准间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('301', '空闲', '无', '大床房')";
    query.exec(sql);
    sql = "insert or ignore into room values ('302', '空闲', '无', '大床房')";
    query.exec(sql);
    sql = "insert or ignore into room values ('303', '空闲', '无', '大床房')";
    query.exec(sql);
    sql = "insert or ignore into room values ('304', '空闲', '无', '大床房')";
    query.exec(sql);
    sql = "insert or ignore into room values ('305', '空闲', '无', '大床房')";
    query.exec(sql);
    sql = "insert or ignore into room values ('306', '空闲', '无', '大床房')";
    query.exec(sql);
    sql = "insert or ignore into room values ('401', '空闲', '无', '商务套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('402', '空闲', '无', '商务套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('403', '空闲', '无', '商务套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('404', '空闲', '无', '商务套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('405', '空闲', '无', '商务套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('406', '空闲', '无', '商务套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('501', '空闲', '无', '豪华套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('502', '空闲', '无', '豪华套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('503', '空闲', '无', '豪华套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('504', '空闲', '无', '豪华套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('505', '空闲', '无', '豪华套间')";
    query.exec(sql);
    sql = "insert or ignore into room values ('506', '空闲', '无', '豪华套间')";
    query.exec(sql);
}
