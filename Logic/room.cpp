#include "room.h"

using namespace logic;

QVariant Room::getData(COLUMNS type) const
{
    switch (type)
    {
    case  COLUMNS::NUMBER:
        return  _number;
    case  COLUMNS::PRICE:
        return  _price;
    case  COLUMNS::LIVING_SPACE:
        return  _livivngSpace;
    case  COLUMNS::FREE_TODAY:
        return  false;
    default:
        return QVariant();
    }
}

void Room::setData(COLUMNS type,QVariant data)
{
    bool isOk = true;
    switch (type)
    {
    case  COLUMNS::NUMBER:
        _number = data.toInt(&isOk);
        break;
    case  COLUMNS::PRICE:
        _price = data.toInt(&isOk);
        break;
    case  COLUMNS::LIVING_SPACE:
        _livivngSpace = data.toInt(&isOk);
        break;
    case  COLUMNS::FREE_TODAY:
        //_number;
        break;
    }
}
