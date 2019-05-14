
#include "dateseditdialog.h"
#include "calendarwidget.h"

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
//    connect(this,SIGNAL(clicked(const QDate&)),this, SLOT(onSelectionChanged(const QDate&)));
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

void CalendarWidget::paintCell(QPainter* painter, const QRect& rect, const QDate& date) const
{
    if(date >= _dateInSelected && date <= _dateOutSelected)
    {
        painter->setPen(_selectedDraw.pen);
        painter->setBrush(_selectedDraw.brush);
    }
    const auto& bookedDates = _parent->getDatesBookList();
    auto it = std::find_if(bookedDates.cbegin(), bookedDates.cend(), [date](const BookDaysData& bookData)
    {
        return bookData.checkDate(date);
    });
    if(it != bookedDates.cend())
    {
        painter->setPen(_bookedDraw.pen);
        painter->setBrush(_bookedDraw.brush);
    }
    QCalendarWidget::paintCell(painter, rect, date);
}

void CalendarWidget::onSelectionChanged(const QDate &date)
{
    if(_dateInSelected.isNull() || _dateOutSelected.isNull())
    {
        _dateInSelected = _dateOutSelected = date;
    }
    if(date <= _dateOutSelected)
    {
        _dateInSelected = date;
    }
    if(date >= _dateOutSelected)
    {
        _dateInSelected = _dateOutSelected;
        _dateOutSelected = date;
    }
}
