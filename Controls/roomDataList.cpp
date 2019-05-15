#include "roomDataList.h"
#include "calendarwidget.h"


RoomOrderPropertiesWidget::RoomOrderPropertiesWidget(QWidget *parent)
    : QTreeWidget(parent)
{

}

void RoomOrderPropertiesWidget::onOrderItemClicked(const logic::BookDay& data)
{
    clear();
    {//dates
        QTreeWidgetItem* datesItem = new QTreeWidgetItem();
        datesItem->setText(0, "Dates");
        addTopLevelItem(datesItem);
        auto datesInItem = new QTreeWidgetItem();
        auto datesOutItem = new QTreeWidgetItem();
        datesInItem->setText(0, data.dateIn.toString("dd.MM.yyyy"));
        datesOutItem->setText(0, data.dateOut.toString("dd.MM.yyyy"));
        datesItem->addChild(datesInItem);
        datesItem->addChild(datesOutItem);
    }
    {//persons
        QTreeWidgetItem* personsItem = new QTreeWidgetItem();
        personsItem->setText(0, "Persons");
        addTopLevelItem(personsItem);
        for(const auto& person : data.persons)
        {
            auto personItem = new QTreeWidgetItem();
            personItem->setText(0, person.name);
            personsItem->addChild(personItem);
        }
    }
    expandAll();
}

RoomDataList::RoomDataList(QWidget* parent)
    :QListWidget (parent)
{

}

void RoomDataList::addBookDates(const BookDaysData& data)
{
    logic::BookDay newOrder;
    newOrder.dateIn = data.dateIn;
    newOrder.dateOut = data.dateOut;
    _orders.push_back(newOrder);
    refresh();
}

void RoomDataList::setData(int index, const logic::BookDay &data)
{
    if(index >= _orders.size())
    {
        return;
    }

    _orders[index] = data;
    refresh();
}

const logic::BookDay &RoomDataList::getCurrentItemData() const
{
    const int row = currentRow();
    return _orders[row];
}

void RoomDataList::refresh()
{
    clear();
    for(const auto& order : _orders)
    {
        QString label;
        if(order.persons.empty())
        {
            label.append("date In: ").append(order.dateIn.toString("yyyy.MM.dd")).append(" date Out: ").append(order.dateOut.toString("yyyy.MM.dd"));
        }
        else
        {
           label.append(order.persons.front().name);
        }
        addItem(label);
    }
}

