//-------------------------------------------
//userservice.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理和user表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "userservice.h"

UserService::UserService(QObject *parent) : QObject(parent)
{
    m_dbUser = new DBUser;
    m_roomService = new RoomService;
    updateUserList();
}

UserService::~UserService()
{
    delete m_dbUser;
    delete m_roomService;
}

//更新暂存的用户列表
void UserService::updateUserList()
{
    m_userList = m_dbUser->getUserList();
}

//获取用户列表
QVector<QMap<QString, QString> > UserService::getUserList()
{
    return m_userList;
}

//判断用户是否存在
bool UserService::isExist(QString &Id)
{
    bool isExist = false;

    for(int i = 0; i < m_userList.size(); i++)
    {
        if(Id == m_userList[i]["Id"])
        {
            isExist = true;
        }
    }

    return isExist;
}

//删除用户
bool UserService::deleteUser(QString &Id)
{
    bool ok;

    if(isExist(Id))
    {
        ok = m_dbUser->deleteUser(Id);
        updateUserList();
    }
    else
    {
        ok = false;
    }

    return ok;
}

//添加用户
bool UserService::addUser(QMap<QString, QString> &user)
{
    bool ok;
    if(isExist(user["Id"]))
    {
        ok = false;
        updateUserList();
    }
    else
    {
        ok = m_dbUser->addUser(user);
    }

    return ok;
}

//退房操作
bool UserService::checkOut(QString &Id, QString &consumeMoney, QString &checkOut, QString &roomId)
{
    bool ok;
    ok = m_dbUser->checkOut(Id, consumeMoney, checkOut);
    if(!ok) return ok;

    ok = m_roomService->checkOut(roomId);
    return ok;
}

//登记入住操作
bool UserService::checkIn(QMap<QString, QString> &user, QString &roomId)
{
    bool ok;
    if(isExist(user["Id"]))
    {
        ok = deleteUser(user["Id"]);
        if(!ok) return ok;

        ok = addUser(user);
        if(!ok) return ok;
    }
    else
    {
        ok = addUser(user);
        if(!ok) return ok;
    }

    ok = m_roomService->checkIn(roomId, user["Id"]);
    return ok;
}

//根据内容搜索用户返回用户列表
QVector<QMap<QString, QString> > UserService::searchUser(QString &item)
{
    return m_dbUser->searchUser(item);
}
