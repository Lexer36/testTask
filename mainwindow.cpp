#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Worker *worker = new Worker;

    connect(worker, &Worker::modelReady, this, &MainWindow::showModel);
    // модель создаем и заполняем в отдельном потоке и передаем ее через сигнал
    connect(&_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(ui->btnConnect, &QPushButton::released, worker, &Worker::connectToDbAndUpdate);
    connect(ui->btnDisconnect, &QPushButton::released, worker, &Worker::closeDbConnection);

    worker->moveToThread(&_workerThread);
    _workerThread.start();
    ui->btnDisconnect->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_released()
{
    ui->btnConnect->setDisabled(true);
    ui->btnDisconnect->setDisabled(false);
}

void MainWindow::on_btnDisconnect_released()
{
    ui->btnConnect->setDisabled(false);
    ui->btnDisconnect->setDisabled(true);
}

void MainWindow::showModel(QSqlQueryModel *model)
{
    ui->tableView->setModel(model);
}
