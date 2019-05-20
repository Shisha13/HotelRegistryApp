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

private:
    Ui::MainWindow *ui;
    logic::Model* _model = nullptr;
};

#endif // MAINWINDOW_H
