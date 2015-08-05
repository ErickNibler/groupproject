#include "database.h"
#include <QBoxLayout>
#include <QVBoxLayout>

Database::Database (QString dbName,  QString userName,
                    QString password, int port, QString hostType, QObject *parent) : QObject(parent)
{
    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setDatabaseName(dbName);
    this->db.setUserName(userName);
    this->db.setPassword(password);
    this->db.setHostName(hostType);
    this->db.setPort(port);

    this->opened = this->Connect();
    if (!opened)
    {
        QSqlError err = this->db.lastError();
        qDebug() << err.databaseText();
    }
    qDebug() << opened;

    this->query = new QSqlQuery(/*this->db*/);
}

Database::~Database()
{
    this->db.close();
    this->db.removeDatabase("QPSQL");
}

bool Database::Connect()
{
    bool toRet = this->db.open();
    return toRet;
}

void Database::AddTable(QString tableName)
{
    this->query->exec(QString("CREATE TABLE " + tableName
                            + "( ID SERIAL PRIMARY KEY, name text NOT NULL);" ));

    qDebug() << tableName;
}

void Database::Change(QString table, QString what, QString newValue, QString condition)
{
    //bool cond = false;
    query->exec(QString(" UPDATE " + table +
                        " SET " + what + " = " + newValue +
                        " WHERE " + condition + ";"));
}

void Database::AddRecord(QString tableName, QString name)
{
    query->exec(QString("INSERT INTO " + tableName + " (name) VALUES ('" + name + "');"));
}

void Database::TakeData(QString what, QString from)
{
    query->exec(QString("SELECT " + what + " FROM " + from + ";"));
    while(query->next())
    {
        QString name = query->value(0).toString();
        qDebug() << name;
    }
}

void Database::Reset(QString tableName,QString toDelete)        // вписывается условие;
{
    query->exec(QString("DELETE FROM " + tableName + " WHERE " + toDelete));
}
