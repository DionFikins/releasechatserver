#include "DataBaseConnection.hpp"
/*
void ExitWithError(PGconn* con) {
  qDebug() << PQerrorMessage(con);
  PQfinish(con);
  exit(1);
}
void ExitConnection(PGconn* con) {
  qDebug() << "Disconnect database complited";
  PQfinish(con);
}
PGconn* ConDB() {
  const char* coninfo = "host=localhost port=5432 dbname=ai user=diofik password=garbe527_pech";
  //const char* coninfo = "host=localhost port=5432 dbname=Ваша база данных user=Ваш Логин password=Ваш пароль";
  PGconn* con = PQconnectdb(coninfo);

  if(PQstatus(con) != CONNECTION_OK) ExitWithError(con);
  qDebug() << "Connection in database complited!";
  return con;
}
void ErrorQuery(PGconn* con, PGresult* res) {
  qDebug() << "Query error complited: " << PQerrorMessage(con);
  PQclear(res);
  PQfinish(con);
}

int QueryDB(PGconn* con, const char* query) {
  PGresult* res = PQexec(con, query);
  if(PQresultStatus(res) != PGRES_COMMAND_OK) {
    ErrorQuery(con, res);
    return -1;
  }
  return 0;
}
int QueryDBInt(PGconn* con, const char* query) {
  PGresult* res = PQexec(con, query);
  if(PQresultStatus(res) != PGRES_TUPLES_OK) {
    ErrorQuery(con, res);
    return -1;
  }
  return atoi(PQgetvalue(res, 0,0));
}
std::string QueryDBString(PGconn* con, const char* query) {
  PGresult* res = PQexec(con, query);
  if(PQresultStatus(res) != PGRES_TUPLES_OK) {
      ErrorQuery(con, res);
      return "";
  }
  return PQgetvalue(res, 0,0);
}
bool QueryDBBool(PGconn* con, const char* query) {
  PGresult* res = PQexec(con, query);
  if(PQresultStatus(res) != PGRES_TUPLES_OK) {
      ErrorQuery(con, res);
      return false;
  }
  int rows = PQntuples(res);
  if(rows == 1) {
    char* value = PQgetvalue(res,0,0);
    bool isEnable = (std::string(value) == "t");
    PQclear(res);
    return isEnable;
  } else {
    char* value = PQgetvalue(res,0,0);
    bool isEnable = (std::string(value) == "f");
    PQclear(res);
    return isEnable;
  }
}
*/
bool DataBaseConnection::createConnection() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
  db.setDatabaseName("ai");
  db.setUserName("diofik");
  db.setPassword("garbe527_pech");
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
