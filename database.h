#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QSqlQuery>

/* frame id, frame name and time */

class Database : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;
    QSqlQuery *query;
    bool opened;
    int counter;

public:
    explicit Database(QString dbName,QString userName,
                      QString password, int port, QString hostType, QObject *parent = 0 );
    ~Database();

    bool Connect();
    void AddTable(QString tableName);
    void AddRecord(QString tableName, QString name);
    void Change(QString table, QString what, QString newValue, QString condition);
    void TakeData(QString what, QString from);
    void Reset(QString tableName, QString toDelete);

signals:

public slots:
};

#endif // DATABASE_H
