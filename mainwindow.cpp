#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);

  serv->StartServer();
  tableviewLoad();
}

MainWindow::~MainWindow() {
  serv->ExitProgram();
  delete ui;
}

void MainWindow::tableviewLoad() {
  QVector<QString> val;
  val.push_back("ID");
  val.push_back("Login");
  val.push_back("Password");
  val.push_back("Name");
  val.push_back("Enabled");

  QSqlQueryModel *query = new QSqlQueryModel(this);
  query->setQuery("select * from users order by 1");
  if(query->lastError().isValid())
    qDebug() << query->lastError();

  for(int i = 0, j = 0; i < query->columnCount(); i++, j++)
    query->setHeaderData(i,Qt::Horizontal,val[j]);

  ui->tableView->setModel(query);
  ui->tableView->setColumnHidden(0,true);
  ui->tableView->setColumnHidden(2,true);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
}
void MainWindow::on_mb_btn_exit_triggered() {
  qDebug() << "Program exit";
  this->close();
}

void MainWindow::on_btn_blockuser_clicked() {
  serv->getinfo->queryUpdate(ui->le_user->text());
  tableviewLoad();
}
void MainWindow::on_btn_unblockuser_clicked() {
  serv->getinfo->unbanQuery(ui->le_user->text());
  tableviewLoad();
}

void MainWindow::on_btn_openallchat_clicked() {
  qDebug() << "Open public chat";
  PublicChat puc;
  puc.exec();
}
void MainWindow::on_btn_openprivatechat_clicked() {
  qDebug() << "Open private chat";
  PrivateChat prc;
  prc.exec();
}

void MainWindow::on_newConnection_triggered() {
  serv->AnyConnection();
  std::string val = serv->OnMessage();
  int v = db->queryIntData(val);
  serv->EnterMessage(std::to_string(v));
}
