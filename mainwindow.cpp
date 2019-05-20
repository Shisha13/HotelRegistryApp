#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Logic/model.h"
#include "Logic/delegate.h"
#include "Controls/roomseditdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new logic::Model(this);
    _model->LoadFromXML("Config/roomsConfig.xml");
    ui->tableView->setItemDelegate(new logic::Delegate(this));
    ui->tableView->setModel(_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRemoveNumber(int roomNumber)
{

}

void MainWindow::onRegistryRoom(const logic::Room &room)
{

}

void MainWindow::on_actionsave_triggered()
{
    _model->saveToXmlConfig();
}

void MainWindow::on_actionRegistry_triggered()
{
    auto dialog = new RoomsEditDialog(_model, this);
    auto result = dialog->exec();
    if(QDialog::DialogCode::Accepted == result)
    {
    }
}
