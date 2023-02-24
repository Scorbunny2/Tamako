//-------------------------------------------
//hotelmangement.h
//创建者：黄天宇
//创建时间：2022/6/14
//进行数据库初始化操作
//Copyright 2022 黄天宇
//-------------------------------------------

#ifndef HOTELSERVICE_H
#define HOTELSERVICE_H

#include <QObject>
#include "dbhotel.h"

class HotelService : public QObject
{
    Q_OBJECT
public:
    explicit HotelService(QObject *parent = nullptr);
    ~HotelService();

private:
    DBHotel* m_dbHotel;

signals:


public slots:
};

#endif // HOTELSERVICE_H
