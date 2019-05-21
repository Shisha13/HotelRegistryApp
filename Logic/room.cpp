#include "room.h"

using namespace logic;
namespace
{
    QList<QString> roomClassStr = {
        "econom",
        "premium",
        "lux"
    };
}

QVariant Room::getData(COLUMNS type) const
{
    switch (type)
    {
    case  COLUMNS::NUMBER:
        return  _number;
    case  COLUMNS::CLASS:
        return  convertClassType(_roomClass);
    case  COLUMNS::PRICE:
        return  _price;
    case  COLUMNS::ORDERS:
    {
        OrdersList list;
        list.orders = _orders;
        QVariant var;
        var.setValue(list);
        return var;
    }
    case  COLUMNS::LIVING_SPACE:
        return  _livivngSpace;
    case  COLUMNS::FREE_TODAY:
    {
        const auto& today = QDate::currentDate();
        for(const auto& order : _orders)
        {
            if(today >= order.dateIn && today <= order.dateOut)
            {
                return false;
            }
        }
        return true;
    }
    default:
        return QVariant();
    }
}

void Room::setData(COLUMNS type, QVariant data)
{
    bool isOk = true;
    switch (type)
    {
    case  COLUMNS::NUMBER:
        _number = data.toInt(&isOk);
        break;
    case  COLUMNS::CLASS:
        _roomClass = convertClassStr(data.toString());
        break;
    case  COLUMNS::PRICE:
        _price = data.toInt(&isOk);
        break;
    case  COLUMNS::LIVING_SPACE:
        _livivngSpace = data.toInt(&isOk);
        break;
    case  COLUMNS::ORDERS:
        _orders = data.value<OrdersList>().orders;
        break;
    }
}

RoomClass Room::convertClassStr(const QString& classStr) const
{
    const int typeIndex = roomClassStr.indexOf(classStr);
    if(typeIndex >= 0 && typeIndex < roomClassStr.size())
    {
        return static_cast<RoomClass>(typeIndex);
    }
    return RoomClass::NONE;
}

QString Room::convertClassType(RoomClass classType) const
{
    const int typeInt = static_cast<int>(classType);
    if(typeInt < roomClassStr.size())
    {
        return  roomClassStr[typeInt];
    }
    return "";
}
