#ifndef ROOM_H
#define ROOM_H
#include<QtWidgets>

namespace logic
{
    enum class COLUMNS
    {
        NUMBER,
        LIVING_SPACE,
        PRICE,
        BOOK_DAYS,
        FREE_TODAY,
        COUNT
    };
    struct Person
    {
        QString name;
    };
    struct BookDay
    {
        QDate dateIn;
        QDate dateOut;
        QString getData()
        {
            const QString& frmt = "dd/MM/yyyy";
            QString info = QString("from:%1  till:%2").arg(dateIn.toString(frmt),dateOut.toString(frmt));
            return info;
        }
    };
    class Room
    {
    public:
        QVariant getData(COLUMNS type) const;
        void setData(COLUMNS type ,QVariant data);

    private:
        int _number = 0;
        int _livivngSpace = 0;
        int _price = 0;
        QList<BookDay> _bookDays;
        QList<Person> _persons;
    };
}
#endif // ROOM_H
