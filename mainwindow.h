#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}
namespace logic
{
    class Model;
    class FilterProxyModel;
    class Room;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onRemoveNumber(int roomNumber);
    void onRegistryRoom(const logic::Room& room);

private slots:
    void on_actionsave_triggered();
    void on_actionRegistry_triggered();

    void on_searchLineEdit_textChanged(const QString& text);

    void on_classComboBox_currentTextChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    logic::Model* _model = nullptr;
    logic::FilterProxyModel* _filterModel = nullptr;
};

#endif // MAINWINDOW_H
