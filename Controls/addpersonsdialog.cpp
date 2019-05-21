#include "addpersonsdialog.h"
#include "ui_addpersonsdialog.h"

AddPersonsDialog::AddPersonsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonsDialog)
{
    ui->setupUi(this);
    refresh();
}

AddPersonsDialog::~AddPersonsDialog()
{
    delete ui;
}

void AddPersonsDialog::addPerson(const logic::Person &person)
{
    _persons.push_back(person);
}

void AddPersonsDialog::on_addButton_clicked()
{
    const QString& name = ui->lineEdit->text();
    if(name.isEmpty())
    {
        return;
    }
    for(int i = 0; i < _persons.size(); ++i)
    {
        if(_persons[i].name.toLower() == name.toLower())
        {
            return;
        }
    }

    _persons.append({name});
    refresh();
    ui->lineEdit->clear();
}

void AddPersonsDialog::refresh()
{
   if(ui->personsList)
   {
        ui->personsList->clear();
        for(const auto& person : _persons)
        {
            ui->personsList->addItem(person.name);
        }
   }
}

void AddPersonsDialog::on_removeButton_clicked()
{
    auto current = ui->personsList->currentItem();
    if(nullptr == current)
    {
        return;
    }
    const int currentRow = ui->personsList->currentRow();
    _persons.removeAt(currentRow);
    refresh();
}
