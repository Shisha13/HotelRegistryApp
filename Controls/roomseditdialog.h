#ifndef ROOMSEDITDIALOG_H
#define ROOMSEDITDIALOG_H

#include <QDialog>

namespace Ui {
class RoomsEditDialog;
}

namespace  logic
{
    class Model;
}

class RoomsEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoomsEditDialog(logic::Model* model, QWidget *parent = nullptr);
    ~RoomsEditDialog();
protected:
    bool event(QEvent* event) override;
private slots:
    void on_registryButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::RoomsEditDialog *ui;
    logic::Model* _model = nullptr;
};

#endif // ROOMSEDITDIALOG_H
