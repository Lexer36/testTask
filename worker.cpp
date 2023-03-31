#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
}

void Worker::connectToDbAndUpdate()
{
    if(!_db.database().isValid()){
        _db = QSqlDatabase::addDatabase("QPSQL");
        _db.setHostName(HOSTNAME);
        _db.setUserName(USERNAME);
        _db.setPassword(PASSWORD);
        _db.setDatabaseName(DBNAME);
    }
    if(!_db.open())
        return;
    if (!_db.driver()->subscribeToNotification("mymessage"))
        qDebug() << "NOT subscribed";

    connect(_db.driver(), SIGNAL(notification(const QString&)), this, SLOT(setupModel()));
    QSqlQuery query;
    query.exec(UPDATE);
    //this->thread()->msleep(50);  //(?) подождать пока бд выполнит запрос
    setupModel();
}

void Worker::setupModel()
{
    _model = new QSqlQueryModel(this);
    _model->setQuery(SELECT);

    emit modelReady(_model);
}

void Worker::closeDbConnection()
{
    _db.driver()->unsubscribeFromNotification("mymessage");
    _db.close();
}
