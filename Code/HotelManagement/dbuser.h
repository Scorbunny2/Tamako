//-------------------------------------------
//dbuser.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理user表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef DBUSER_H
#define DBUSER_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QMap>

class DBUser : public QObject
{
    Q_OBJECT
public:
    explicit DBUser(QObject *parent = nullptr);
    ~DBUser();
    void initDataBase();    //初始化数据库连接
    bool addUser(QMap<QString, QString>& user); //添加用户
    QVector<QMap<QString, QString>> getUserList();  //获取用户列表
    QVector<QMap<QString, QString>> searchUser(QString& item);  //根据搜索内容返回用户列表
    bool deleteUser(QString &Id);   //删除用户
    bool checkOut(QString& Id, QString& consumeMoney, QString& checkOut);   //退房


private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DBUSER_H
