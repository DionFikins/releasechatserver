#include "DataBaseConnection.hpp"

bool DataBaseConnection::createConnection() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
  db.setDatabaseName("Ваша база данных");
  db.setUserName("Ваш пользователь от базы данных");
  db.setPassword("Ваш пароль от базы данных");

  if(!db.open()) {
    qDebug() << "Connection in database failed";
    return false;
  }
  else {
    qDebug() << "Connection in database complited!";
    return true;
  }
}

void DataBaseConnection::exitConnection()
{
  QSqlDatabase db;
  db.close();
  qDebug() << "Connection close";
}

void DataBaseConnection::queryUpdate(QString str)
{
  QSqlQuery query;
  query.prepare("update users set enable_user = 'false' where name_user = :login");
  query.bindValue(":login", str);
  if(query.lastError().isValid())
    qDebug() << query.lastError();
  qDebug() << str;
  query.exec();
}

void DataBaseConnection::unbanQuery(QString str)
{
  QSqlQuery query;
  query.prepare("update users set enable_user = 'true' where name_user = :login");
  query.bindValue(":login", str);
  if(query.lastError().isValid())
    qDebug() << query.lastError();
  qDebug() << str;
  query.exec();
}

void DataBaseConnection::queryData(QString str) {
  QSqlQuery query;
  query.prepare(str);
  if(query.lastError().isValid())
    qDebug() << query.lastError();
  qDebug() << str;
  query.exec();
}
