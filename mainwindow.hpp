#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <iostream>
#include <QMainWindow>
#include <QMenuBar>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include "DataBaseConnection.hpp"
#include "publicchat.hpp"
#include "privatechat.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  static MainWindow* createPublic();
  static MainWindow* createPrivate();

  DataBaseConnection *getinfo = new DataBaseConnection;
  QSqlTableModel *model = new QSqlTableModel;
  QTableView *view = new QTableView;

private slots:
  void tableviewLoad();

  void on_mb_btn_exit_triggered();

  void on_btn_blockuser_clicked();
  void on_btn_unblockuser_clicked();

  void on_btn_openallchat_clicked();
  void on_btn_openprivatechat_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
