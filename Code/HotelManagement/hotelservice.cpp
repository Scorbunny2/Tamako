//-------------------------------------------
//hotelmangement.cpp
//创建者：黄天宇
//创建时间：2022/6/14
//进行数据库初始化操作
//Copyright 2022 黄天宇
//-------------------------------------------

#include "hotelservice.h"

HotelService::HotelService(QObject *parent) : QObject(parent)
{
    m_dbHotel = new DBHotel;
}

HotelService::~HotelService()
{
    delete  m_dbHotel;
}
