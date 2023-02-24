//-------------------------------------------
//userservice.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理和user表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include "dbuser.h"
#include "roomservice.h"

class UserService : public QObject
{
    Q_OBJECT
public:
    explicit UserService(QObject *parent = nullptr);
    ~UserService();
    void updateUserList();  //更新暂存的用户列表
    QVector<QMap<QString, QString>> getUserList();  //获取用户列表
    bool isExist(QString& Id);  //判断用户是否存在
    bool deleteUser(QString& Id);   //删除用户
    bool addUser(QMap<QString, QString>& user); //添加用户
    bool checkOut(QString &Id, QString &consumeMoney, QString &checkOut, QString& roomId);  //退房操作
    bool checkIn(QMap<QString, QString>& user, QString& roomId);    //登记入住操作
    QVector<QMap<QString, QString>> searchUser(QString& item);  //根据内容搜索用户返回用户列表

private:
    DBUser* m_dbUser;
    RoomService* m_roomService;
    QVector<QMap<QString, QString>> m_userList;

signals:

public slots:
};

#endif // USERSERVICE_H
