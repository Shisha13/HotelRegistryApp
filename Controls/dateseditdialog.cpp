
#include "dateseditdialog.h"
#include "ui_dateseditdialog.h"

#include <QPainter>

DatesEditDialog::DatesEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatesEditDialog)
{
    ui->setupUi(this);
}

DatesEditDialog::~DatesEditDialog()
{
    delete ui;
}

void DatesEditDialog::addBookData(const BookDaysData &date)
{
    _bookedList.append(date);
}

