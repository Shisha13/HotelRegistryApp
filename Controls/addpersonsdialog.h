#ifndef ADDPERSONSDIALOG_H
#define ADDPERSONSDIALOG_H

#include <QDialog>
#include "Logic/room.h"

namespace Ui {
class AddPersonsDialog;
}

class AddPersonsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonsDialog(QWidget* parent = nullptr);
    ~AddPersonsDialog();

    const QList<logic::Person>& getPersons() const { return _persons; }
    void addPerson(const logic::Person& person);

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

private:
    void refresh();

    QList<logic::Person> _persons;
    Ui::AddPersonsDialog *ui;
};

#endif // ADDPERSONSDIALOG_H
