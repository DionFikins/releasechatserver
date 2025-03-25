#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <iostream>
#include <QDebug>
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QSqlError>

using namespace std;

class DataBaseConnection {
public:
  bool createConnection();
  void exitConnection();
  void queryUpdate(QString str);
  void unbanQuery(QString str);
  void loadData(QString str);
};
#endif // DATABASECONNECTION_H
