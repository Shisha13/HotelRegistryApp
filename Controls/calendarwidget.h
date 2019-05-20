#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QCalendarWidget>
#include <QPen>
#include <QBrush>
#include <QList>
#include <QPainter>

class DatesEditDialog;

struct BookDaysData
{
    BookDaysData(const QDate& _dateIn, const QDate& _dateOut)
        : dateIn(_dateIn),
          dateOut(_dateOut)
    {}
    bool checkDate(const QDate& date) const
    {
        if(date >= dateIn && date <= dateOut)
        {
            return true;
        }
        return false;
    }
    QDate dateIn;
    QDate dateOut;
};

class CalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget* parent = nullptr);
    BookDaysData getBookData() const;
    void refresh();
protected:
    struct DateDrawData
    {
        QPen pen;
        QBrush brush;
    };
    void forceRedraw();
    void paintCell(QPainter* painter, const QRect& rect, const QDate& date) const override;

    QDate _dateInSelected;
    QDate _dateOutSelected;

    DateDrawData _selectedDraw;
    DateDrawData _bookedDraw;

    DatesEditDialog* _parent = nullptr;

protected slots:
    void onSelectionChanged(const QDate& date);

signals:
    void dateChanged(const BookDaysData& data);
    void checkControls();
};

#endif // CALENDARWIDGET_H
