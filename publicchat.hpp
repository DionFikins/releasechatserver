#ifndef PUBLICCHAT_HPP
#define PUBLICCHAT_HPP

#include <QDialog>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include "DataBaseConnection.hpp"

namespace Ui {
  class PublicChat;
}

class PublicChat : public QDialog
{
  Q_OBJECT

public:
  explicit PublicChat(QWidget *parent = nullptr);
  ~PublicChat();

private:
  Ui::PublicChat *ui;
};

#endif // PUBLICCHAT_HPP
