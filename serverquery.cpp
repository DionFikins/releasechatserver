#include "serverquery.hpp"

ServerQuery::ServerQuery() {}

ServerQuery::~ServerQuery() {}

void ServerQuery::RegUser()
{
  QSqlQuery query;
  query.prepare("");
}

void ServerQuery::LoginUser(int _loginId)
{

}

void ServerQuery::SendMessagePublic(int _loginId)
{

}

void ServerQuery::SendMessagePrivate(int _loginId)
{

}

void ServerQuery::RebindLogin(int _loginId)
{

}

void ServerQuery::RebindPassword(int _loginId)
{

}

void ServerQuery::RebindName(int _loginId)
{

}
