#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQueryModel>
#include <QThread>
#include <worker.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
     void showModel(QSqlQueryModel *model);
private slots:
    void on_btnConnect_released();
    void on_btnDisconnect_released();
private:
    Ui::MainWindow *ui;
    QThread _workerThread;
};
#endif // MAINWINDOW_H
