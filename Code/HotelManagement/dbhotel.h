//-------------------------------------------
//dbhotel.h
//创建者：黄天宇
//创建时间：2022/6/14
//初始化数据库
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef DBHOTEL_H
#define DBHOTEL_H

#include <QObject>
#include <QSqlDatabase>

class DBHotel
{
public:
    DBHotel();
    ~DBHotel();

    void initDatabase();    //初始化数据库
    void createTables();    //创建表
    void addAdmin();        //添加管理员账户
    void addRoomType();     //添加roomType默认数据
    void addRoom();         //添加room默认数据

private:
    QSqlDatabase m_db;
};

#endif // DBHOTEL_H
