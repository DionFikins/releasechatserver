#include "serversetting.hpp"

ServerSetting::ServerSetting() {}

ServerSetting::~ServerSetting() {}

void ServerSetting::StartServer() {
  if((_server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      qDebug() << "Socket failed";
  }
  if(setsockopt(_server, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt))) {
     qDebug() << "Setsockopt error";
  }
  _address.sin_family = AF_INET;
  _address.sin_addr.s_addr = INADDR_ANY;
  _address.sin_port = htons(PORT);

  if(bind(_server, (struct sockaddr*)&_address, sizeof(_address)) < 0) {
    qDebug() << "Bind failed";
  }
  qDebug() << "Server is active";

  getinfo->createConnection();
}

bool ServerSetting::AnyConnection() {
  if(listen(_server, 3) < 0) {
    qDebug() << "Listen error";
    return false;
  }
  qDebug() << "Server waiting any connection...";

  if((_socket = accept(_server, (struct sockaddr*)&_address, (socklen_t*)&_address)) < 0) {
    qDebug() << "accept error";
    return false;
  }
  qDebug() << "User online.";
  return true;
}

void ServerSetting::ExitProgram() {
  getinfo->exitConnection();
  close(_socket);
  qDebug() << "Server shutdown";
  exit(1);
}

void ServerSetting::EnterMessage(std::string response) {
  send(_socket, response.c_str(), response.length(), 0);
}

std::string ServerSetting::OnMessage() {
  memset(_buffer, 0, sizeof(_buffer));
  int bytes = read(_socket, _buffer, 1024);
  if(bytes <= 0) {
    qDebug() << "User is offline";
    return "User is offline";
  }
  qDebug() << _buffer;
  return _buffer;
}
