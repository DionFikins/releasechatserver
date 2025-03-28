#ifndef SERVERSETTING_HPP
#define SERVERSETTING_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <QDebug>
#include <QString>
#include "DataBaseConnection.hpp"

#define PORT 7777

class ServerSetting
{
protected:
  int _server, _socket;
  struct sockaddr_in _address;
  int _opt = 1;
  int _addrlen = sizeof(_address);
  char _buffer[1024] = {0};

public:
  ServerSetting();
  ~ServerSetting();

  DataBaseConnection *getinfo = new DataBaseConnection;

  void StartServer();
  bool AnyConnection();
  void ExitProgram();
  void EnterMessage(std::string response);
  std::string OnMessage();
  void RegistUser();
};

#endif // SERVERSETTING_HPP
