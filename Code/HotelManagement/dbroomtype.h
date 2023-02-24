//-------------------------------------------
//dbroomtype.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理roomType表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef DBROOMTYPE_H
#define DBROOMTYPE_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QMap>

class DBRoomType : public QObject
{
    Q_OBJECT
public:
    explicit DBRoomType(QObject *parent = nullptr);
    ~DBRoomType();
    void initDatabase();    //初始化数据库连接
    QVector<QMap<QString, QString>> getRoomTypeList();  //获取roomType表

private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DBROOMTYPE_H
