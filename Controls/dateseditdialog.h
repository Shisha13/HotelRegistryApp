#ifndef DATESEDITDIALOG_H
#define DATESEDITDIALOG_H

#include <QDialog>
#include <QList>
#include <QDate>
#include "calendarwidget.h"

namespace Ui
{
    class DatesEditDialog;
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

protected:
    QList<BookDaysData> _bookedList;

private:
    Ui::DatesEditDialog* ui = nullptr;
};

#endif // DATESEDITDIALOG_H
