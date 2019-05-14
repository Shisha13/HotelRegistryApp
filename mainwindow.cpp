#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Logic/model.h"
#include "Logic/delegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto model = new logic::Model(this);
    model->LoadFromXML("Config/roomsConfig.xml");
    ui->tableView->setItemDelegate(new logic::Delegate(this));
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
