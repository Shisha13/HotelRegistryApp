#ifndef DATESLIST_H
#define DATESLIST_H

#include <QDate>
#include <QListWidget>
#include <QTreeWidget>
#include "Logic/room.h"

struct BookDaysData;

class RoomOrderPropertiesWidget : public QTreeWidget
{
    Q_OBJECT
public:
    RoomOrderPropertiesWidget(QWidget* parent = nullptr);
    void onOrderItemClicked(const logic::BookDay& data);
};

class RoomDataList : public QListWidget
{
    Q_OBJECT
public:
    explicit RoomDataList(QWidget* parent = nullptr);
    void addBookDates(const BookDaysData& data);
    const QList<logic::BookDay>& getData() const { return _orders; }
    void setData(int index, const logic::BookDay& data);
    const logic::BookDay &getCurrentItemData() const;
protected:
    void refresh();

    QList<logic::BookDay> _orders;
};

#endif // DATESLIST_H
