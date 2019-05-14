
#include "dateseditdialog.h"
#include "ui_dateseditdialog.h"

#include <QPainter>

DatesEditDialog::DatesEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatesEditDialog)
{
    ui->setupUi(this);

    connect(ui->calendarWidget, &CalendarWidget::dateChanged, this, &DatesEditDialog::onDateChanged);
}

DatesEditDialog::~DatesEditDialog()
{
    delete ui;
}

void DatesEditDialog::addBookData(const BookDaysData &date)
{
    _bookedList.append(date);
}


void DatesEditDialog::on_refreshButton_clicked()
{
    ui->calendarWidget->refresh();
}

void DatesEditDialog::onDateChanged(const BookDaysData &data)
{
    ui->dateInEdit->setDate(data.dateIn);
    ui->dateOutEdit->setDate(data.dateOut);
}
