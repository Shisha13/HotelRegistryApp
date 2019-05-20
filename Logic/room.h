#ifndef ROOM_H
#define ROOM_H
#include<QtWidgets>
#include<QMetaType>

namespace logic
{
    enum class COLUMNS
    {
        NUMBER,
        CLASS,
        LIVING_SPACE,
        PRICE,
        ORDERS,
        FREE_TODAY,
        COUNT
    };

    enum class RoomClass
    {
        ECONOM,
        PREMIUM,
        LUX,
        NONE
    };

    struct Person
    {
        QString name;
    };
    struct Order
    {
        QDate dateIn;
        QDate dateOut;
        QList<Person> persons;

        QString getDatesStr() const
        {
            const QString& frmt = "dd/MM/yyyy";
            QString info = QString("from: %1  till: %2").arg(dateIn.toString(frmt),dateOut.toString(frmt));
            return info;
        }
    };
    struct OrdersList
    {
        QList<Order> orders;
    };

    class Room
    {
    public:
        QVariant getData(COLUMNS type) const;
        void setData(COLUMNS type ,QVariant data);

    private:
        RoomClass convertClassStr(const QString& classStr) const;
        QString convertClassType(RoomClass classType) const;

        int _number = 0;
        int _livivngSpace = 0;
        int _price = 0;
        QList<Order> _orders;
        RoomClass _roomClass = RoomClass::ECONOM;
    };
}

Q_DECLARE_METATYPE(logic::OrdersList);

#endif // ROOM_H
