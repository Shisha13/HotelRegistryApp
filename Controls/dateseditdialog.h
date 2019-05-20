#ifndef DATESEDITDIALOG_H
#define DATESEDITDIALOG_H

#include <QDialog>
#include <QList>
#include <QDate>
#include <QListWidgetItem>
#include "calendarwidget.h"

namespace Ui
{
    class DatesEditDialog;
}

namespace logic
{
    struct Order;
}

class DatesEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatesEditDialog(QWidget *parent = nullptr);
    ~DatesEditDialog();
    const QList<BookDaysData>& getDatesBookList() const { return _bookedList; }
    void setDatesBookList(const QList<BookDaysData>& list) { _bookedList = list;}
    void addBookData(const BookDaysData& date);
    void addRoomOrders(const QList<logic::Order>& dataList);
    const QList<logic::Order>& getRoomOrders() const;
protected:
    bool event(QEvent* event) override;

    QList<BookDaysData> _bookedList;

private slots:
    void checkControlsState();
    void checkControlsStateDate(const QDate& date);
    void on_refreshButton_clicked();
    void onDateChanged(const BookDaysData& data);

    void onOrderItemClicked(QListWidgetItem* item);
    void on_addButton_clicked();
    void on_propertiesButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::DatesEditDialog* ui = nullptr;
};

#endif // DATESEDITDIALOG_H
