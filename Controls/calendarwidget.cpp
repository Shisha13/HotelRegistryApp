
#include "dateseditdialog.h"
#include "calendarwidget.h"

#include <QTextCharFormat>

CalendarWidget::CalendarWidget(QWidget *parent)
    : QCalendarWidget(parent),
      _parent(dynamic_cast<DatesEditDialog*>(parent))
{
    if(!_parent)
    {
        assert(false);
    }

    _selectedDraw.pen.setColor(QColor(Qt::blue));
    _selectedDraw.brush.setColor(Qt::transparent);

    _bookedDraw.pen.setColor(QColor(Qt::red));
    _bookedDraw.brush.setColor(Qt::transparent);

    connect(this, &QCalendarWidget::clicked, this, &CalendarWidget::onSelectionChanged);
}

BookDaysData CalendarWidget::getBookData() const
{
    if(_dateInSelected.isNull() || _dateOutSelected.isNull())
    {
        return BookDaysData(QDate(), QDate());
    }
    return BookDaysData(_dateInSelected, _dateOutSelected);
}

void CalendarWidget::refresh()
{
    _dateInSelected = _dateOutSelected = QDate();
    forceRedraw();
}

void CalendarWidget::forceRedraw()
{
    setVisible(false);
    setVisible(true);
}

void CalendarWidget::paintCell(QPainter* painter, const QRect& rect, const QDate& date) const
{
    QCalendarWidget::paintCell(painter, rect, date);

    const auto& bookedDates = _parent->getDatesBookList();
    auto it = std::find_if(bookedDates.cbegin(), bookedDates.cend(), [date](const BookDaysData& bookData)
    {
        return bookData.checkDate(date);
    });

    if(it != bookedDates.cend())
    {
        painter->setPen(_bookedDraw.pen);
        painter->setBrush(_bookedDraw.brush);
        painter->drawRect(rect.adjusted(0, 0, -1, -1));
    }
    if(date >= _dateInSelected && date <= _dateOutSelected)
    {
        painter->setPen(_selectedDraw.pen);
        painter->setBrush(_selectedDraw.brush);
        painter->drawRect(rect.adjusted(0, 0, -1, -1));
    }
}

void CalendarWidget::onSelectionChanged(const QDate &date)
{
    if(_dateInSelected.isNull() || _dateOutSelected.isNull())
    {
        _dateInSelected = _dateOutSelected = date;
        return;
    }
    if(date <= _dateOutSelected)
    {
        _dateInSelected = date;
    }
    else if(date > _dateOutSelected)
    {
        _dateInSelected = _dateOutSelected;
        _dateOutSelected = date;
    }
    emit dateChanged(BookDaysData(_dateInSelected, _dateOutSelected));

    forceRedraw();
}
