#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Logic/model.h"
#include"Logic/filterproxymodel.h"
#include "Logic/delegate.h"
#include "Controls/roomseditdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new logic::Model(this);
    _filterModel = new logic::FilterProxyModel(this);
    _filterModel->setSourceModel(_model);
    _model->LoadFromXML("Config/roomsConfig.xml");
    ui->tableView->setItemDelegate(new logic::Delegate(this));
    ui->tableView->setModel(_filterModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->filterGroup->setId(ui->allRoomsRB, static_cast<int>(logic::Filter::ALL_ROOMS));
    ui->filterGroup->setId(ui->freeRoomsRB, static_cast<int>(logic::Filter::FREE_ROOMS));
    ui->filterGroup->setId(ui->bookedRoomsRb, static_cast<int>(logic::Filter::BOOKED_ROOMS));
    ui->allRoomsRB->setChecked(true);

    ui->searchGroup->setId(ui->personRB, static_cast<int>(logic::SearchFilter::PERSON));
    ui->searchGroup->setId(ui->freeDateRB, static_cast<int>(logic::SearchFilter::FREE_DATE));
    ui->searchGroup->setId(ui->classRB, static_cast<int>(logic::SearchFilter::CLASS));
    ui->personRB->setChecked(true);

    const QDate& today = QDate::currentDate();
    ui->dateEdit->setDate(today);
    ui->dateEdit->setMinimumDate(today);

    QList<QWidget*> searchWidgets = {
      ui->dateEdit,
      ui->searchLineEdit,
      ui->classComboBox,
    };
    connect(ui->filterGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),[this](int id)
    {
        _filterModel->setFilter(static_cast<logic::Filter>(id));
    });
    connect(ui->searchGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),[searchWidgets](int id)
    {
        for(int i = 0; i < searchWidgets.size(); ++i )
        {
            auto& widget = searchWidgets[i];
            widget->setEnabled(id == i);
        }
    });

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

void MainWindow::on_searchLineEdit_textChanged(const QString& text)
{
    if(text.isEmpty())
    {
        _filterModel->setSearchFilter(logic::SearchFilter::NONE,"");
        return;
    }
    _filterModel->setSearchFilter(static_cast<logic::SearchFilter>(ui->searchGroup->checkedId()), text);

}

void MainWindow::on_classComboBox_currentTextChanged(const QString &arg1)
{
    _filterModel->setSearchFilter(static_cast<logic::SearchFilter>(ui->searchGroup->checkedId()), arg1);
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    _filterModel->setSearchFilter(static_cast<logic::SearchFilter>(ui->searchGroup->checkedId()), date);
}
