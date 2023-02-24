//-------------------------------------------
//dbstaff.h
//创建者：黄天宇
//创建时间：2022/6/14
//处理staff表的数据库操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef DBSTAFF_H
#define DBSTAFF_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QMap>

class DBStaff : public QObject
{
    Q_OBJECT
public:
    explicit DBStaff(QObject *parent = nullptr);
    ~DBStaff();
    void initDatabase();    //初始化数据库连接
    QVector<QMap<QString, QString>> getStaffList(); //获取员工表
    bool deleteStaff(QString& userName);    //删除员工
    bool addStaff(QMap<QString, QString>& staff);   //添加员工
    bool checkStaff(QString& userName, QString& passwd);    //检查员工账号密码是否匹配
    QVector<QMap<QString, QString>> serachStaff(QString& item); //根据内容返回搜索到的员工表

private:
    QSqlDatabase m_db;

signals:

public slots:
};

#endif // DBSTAFF_H
