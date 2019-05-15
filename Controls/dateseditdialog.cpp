
#include "dateseditdialog.h"
#include "ui_dateseditdialog.h"
#include "roomDataList.h"
#include "Logic/room.h"
#include "addpersonsdialog.h"

#include <QPainter>

DatesEditDialog::DatesEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatesEditDialog)
{
    ui->setupUi(this);

    connect(ui->calendarWidget, &CalendarWidget::dateChanged, this, &DatesEditDialog::onDateChanged);
    connect(ui->orderList, &RoomDataList::itemClicked,this, &DatesEditDialog::onOrderItemClicked);
    //connect(this, &DatesEditDialog::orderItemClicked, ui->propertiesWidget, &RoomOrderPropertiesWidget::onOrderItemClicked);
}

DatesEditDialog::~DatesEditDialog()
{
    delete ui;
}

void DatesEditDialog::addBookData(const BookDaysData& date)
{
    _bookedList.append(date);
    ui->orderList->addBookDates(date);
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

void DatesEditDialog::onOrderItemClicked(QListWidgetItem *item)
{
    const int row = ui->orderList->row(item);
    const auto& orders = ui->orderList->getData();
    if(row > orders.size())
    {
        assert(false);
    }
    ui->propertiesWidget->onOrderItemClicked(orders[row]);
}

void DatesEditDialog::on_addButton_clicked()
{
    addBookData(ui->calendarWidget->getBookData());
}

void DatesEditDialog::on_propertiesButton_clicked()
{
    auto dialog = new AddPersonsDialog(this);
    auto result = dialog->exec();
    if(QDialog::DialogCode::Accepted == result)
    {
        logic::BookDay newData = ui->orderList->getCurrentItemData();
        newData.persons = dialog->getPersons();
        ui->orderList->setData(ui->orderList->currentRow(), newData);
    }
}
