#ifndef SERVERQUERY_HPP
#define SERVERQUERY_HPP

#include "serversetting.hpp"
#include <QSql>
#include <QSqlError>

class ServerQuery
{
public:
  ServerQuery();
  ~ServerQuery();

  ServerSetting *serv = new ServerSetting();

  void RegUser();
  void LoginUser(int _loginId);
  void SendMessagePublic(int _loginId);
  void SendMessagePrivate(int _loginId);
  void RebindLogin(int _loginId);
  void RebindPassword(int _loginId);
  void RebindName(int _loginId);

  int _loginId;
};

#endif // SERVERQUERY_HPP
