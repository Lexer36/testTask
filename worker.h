#ifndef WORKER_H
#define WORKER_H

#define HOSTNAME ""
#define USERNAME ""
#define PASSWORD ""          // DB connection and SQL requests setup
#define DBNAME   ""
#define UPDATE "UPDATE ... SET flag = 'false' WHERE flag = 'true'"
#define SELECT "SELECT id, data, flag FROM ..."

#include <QObject>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
public slots:
    void setupModel();
    void closeDbConnection();
    void connectToDbAndUpdate();
signals:
    void modelReady(QSqlQueryModel* q);
private:
    QSqlDatabase _db;
    QSqlQueryModel *_model;
};

#endif // WORKER_H
