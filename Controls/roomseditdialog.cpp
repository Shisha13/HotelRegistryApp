#include "roomseditdialog.h"
#include "ui_roomseditdialog.h"
#include "Logic/model.h"
#include <QValidator>

RoomsEditDialog::RoomsEditDialog(logic::Model* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomsEditDialog),
    _model(model)
{
    if(nullptr == _model)
    {
        assert(false);
    }
    ui->setupUi(this);
    const auto& settings = _model->getHotelSettings();

    ui->regNumber->setMinimum(settings.minRoom);
    ui->regNumber->setMaximum(settings.maxRoom);

    ui->removeNumber->setMinimum(settings.minRoom);
    ui->removeNumber->setMaximum(settings.maxRoom);

    ui->price->setValidator(new QDoubleValidator(settings.minPrice, settings.maxPrice, 5, ui->price));
}

RoomsEditDialog::~RoomsEditDialog()
{
    delete ui;
}

bool RoomsEditDialog::event(QEvent *event)
{
    if(!ui || !ui->removeButton || !ui->registryButton)
    {
        return QDialog::event(event);
    }
    const auto& settings = _model->getHotelSettings();
    bool removeEnabled =  _model->hasRoom(ui->removeNumber->text().toInt());

    const int regNum = ui->regNumber->text().toInt();
    const int price = ui->price->text().toInt();

    bool regEnabled = !_model->hasRoom(regNum) && regNum >= settings.minRoom && regNum <= settings.maxRoom;

    regEnabled |=  price >= settings.minPrice && price <= settings.maxPrice;

    ui->removeButton->setEnabled(removeEnabled);
    ui->registryButton->setEnabled(regEnabled);

    return QDialog::event(event);
}

void RoomsEditDialog::on_registryButton_clicked()
{
    logic::Room newRoom;
    newRoom.setData(logic::COLUMNS::NUMBER, ui->regNumber->text().toInt());
    newRoom.setData(logic::COLUMNS::CLASS, ui->typesCombo->currentText());
    newRoom.setData(logic::COLUMNS::PRICE, ui->price->text().toInt());
    newRoom.setData(logic::COLUMNS::LIVING_SPACE, ui->livingSpace->text().toInt());

    _model->registryRoom(newRoom);
}

void RoomsEditDialog::on_removeButton_clicked()
{
    _model->removeRoom(ui->removeNumber->text().toInt());
}
