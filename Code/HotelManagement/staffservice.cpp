//-------------------------------------------
//staffservice.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//处理和staff表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "staffservice.h"

StaffService::StaffService(QObject *parent) : QObject(parent)
{
    m_dbStaff = new DBStaff;
    updateStaffList();
}

StaffService::~StaffService()
{
    delete  m_dbStaff;
}

//获取员工列表
QVector<QMap<QString, QString> > StaffService::getStaffList()
{
    return m_staffList;
}

//根据搜索到内容返回员工列表
QVector<QMap<QString, QString> > StaffService::searchStaff(QString &item)
{
    return m_dbStaff->serachStaff(item);
}

//更新类中暂时存储的员工列表
void StaffService::updateStaffList()
{
    m_staffList = m_dbStaff->getStaffList();
}

//判断员工是否已经存在
bool StaffService::isExist(QString &userName)
{
    for(int i = 0; i < m_staffList.size(); i++)
    {
        if(m_staffList[i]["userName"] == userName)
        {
            return true;
        }
    }

    return false;
}

//删除员工信息
bool StaffService::deleteStaff(QString &userName)
{
    bool ok = isExist(userName);
    if(ok)
    {
        ok = m_dbStaff->deleteStaff(userName);
        return ok;
    }
    else
    {
        return false;
    }
}

//添加员工信息
bool StaffService::addStaff(QMap<QString, QString> &staff)
{
    updateStaffList();
    bool ok = isExist(staff["userName"]);
    if(ok)
    {
        return false;
    }
    else
    {
        ok = m_dbStaff->addStaff(staff);
        return ok;
    }
}

//判断员工账户密码是否匹配
bool StaffService::checkStaff(QString &userName, QString &passwd)
{
    bool ok = m_dbStaff->checkStaff(userName, passwd);
    return ok;
}
