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
  void queryUpdate(std::string str);
  void unbanQuery(std::string str);
  void loadData(std::string str);
  void queryData(std::string str);
};
#endif // DATABASECONNECTION_H
