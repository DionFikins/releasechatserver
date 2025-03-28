#ifndef PRIVATECHAT_HPP
#define PRIVATECHAT_HPP

#include <QDialog>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include "DataBaseConnection.hpp"

namespace Ui {
  class PrivateChat;
}

class PrivateChat : public QDialog
{
  Q_OBJECT

public:
  explicit PrivateChat(QWidget *parent = nullptr);
  ~PrivateChat();

private slots:
  void on_btn_search_clicked();

private:
  void tableviewLoad(QString str1, QString str2);
  Ui::PrivateChat *ui;
};

#endif // PRIVATECHAT_HPP
