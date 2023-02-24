//-------------------------------------------
//satffservice.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理和staff表相关的功能和操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef STAFFSERVICE_H
#define STAFFSERVICE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "dbstaff.h"

class StaffService : public QObject
{
    Q_OBJECT
public:
    explicit StaffService(QObject *parent = nullptr);
    ~StaffService();
    QVector<QMap<QString, QString>> getStaffList(); //获取员工列表
    QVector<QMap<QString, QString>> searchStaff(QString& item); //根据搜索到内容返回员工列表
    void updateStaffList(); //更新类中暂时存储的员工列表
    bool isExist(QString& userName);    //判断员工是否已经存在
    bool deleteStaff(QString& userName);    //删除员工信息
    bool addStaff(QMap<QString, QString>& staff);   //添加员工信息
    bool checkStaff(QString& userName, QString& passwd);    //判断员工账户密码是否匹配

private:
    DBStaff* m_dbStaff;
    QVector<QMap<QString, QString>> m_staffList;

signals:

public slots:
};

#endif // STAFFSERVICE_H
