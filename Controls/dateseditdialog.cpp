
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

    connect(ui->orderList,&RoomDataList::checkControls, this, &DatesEditDialog::checkControlsState);
    connect(ui->calendarWidget, &CalendarWidget::checkControls, this, &DatesEditDialog::checkControlsState);

    connect(ui->dateInEdit, &QDateEdit::dateChanged, this, &DatesEditDialog::checkControlsStateDate);
    connect(ui->dateOutEdit, &QDateEdit::dateChanged, this, &DatesEditDialog::checkControlsStateDate);
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

void DatesEditDialog::addRoomOrders(const QList<logic::Order>& dataList)
{
    ui->orderList->setData(dataList);
    for(const auto& order : dataList)
    {
        _bookedList.push_back(std::move(BookDaysData(order.dateIn, order.dateOut)));
    }
}

const QList<logic::Order> &DatesEditDialog::getRoomOrders() const
{
    return ui->orderList->getData();
}

bool DatesEditDialog::event(QEvent* event)
{
    return QDialog::event(event);
}

void DatesEditDialog::checkControlsState()
{
    bool datesAlreadyBooked = false;
    const QDate& currentDateIn = ui->dateInEdit->date();
    const QDate& currentDateOut = ui->dateOutEdit->date();

    const auto& currentOrders = ui->orderList->getData();
    for(const auto& order : currentOrders)
    {
        if(currentDateIn >= order.dateIn && currentDateIn <= order.dateOut)
        {
            datesAlreadyBooked = true;
            break;
        }
        if(currentDateOut >= order.dateIn && currentDateOut <= order.dateOut)
        {
            datesAlreadyBooked = true;
            break;
        }
    }

    ui->addButton->setEnabled(!datesAlreadyBooked);
}

void DatesEditDialog::checkControlsStateDate(const QDate &date)
{
    Q_UNUSED(date);
    checkControlsState();
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
    ui->calendarWidget->refresh();
}

void DatesEditDialog::on_propertiesButton_clicked()
{
    auto dialog = new AddPersonsDialog(this);
    logic::Order data = ui->orderList->getCurrentItemData();
    for(const auto& person : data.persons)
    {
       dialog->addPerson(person);
    }
    auto result = dialog->exec();
    if(QDialog::DialogCode::Accepted == result)
    {
        data.persons = dialog->getPersons();
        ui->orderList->setData(ui->orderList->currentRow(), data);
    }
}

void DatesEditDialog::on_removeButton_clicked()
{
    const int row = ui->orderList->currentRow();
    if(row >= 0 && row < _bookedList.size())
    {
        _bookedList.removeAt(row);
    }
    ui->orderList->onRemoveOrder();
}
