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
    void onOrderItemClicked(const logic::Order& data);
};

class RoomDataList : public QListWidget
{
    Q_OBJECT
public:
    explicit RoomDataList(QWidget* parent = nullptr);
    void addBookDates(const BookDaysData& data);
    const QList<logic::Order>& getData() const { return _orders; }
    void setData(const QList<logic::Order>& data) { _orders = data; refresh(); }
    void setData(int index, const logic::Order& data);
    const logic::Order &getCurrentItemData() const;
    void onRemoveOrder();
protected:
    void refresh();

    QList<logic::Order> _orders;
signals:
    void checkControls();
};

#endif // DATESLIST_H
