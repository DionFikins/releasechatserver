#include "publicchat.hpp"
#include "ui_publicchat.h"

PublicChat::PublicChat(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PublicChat)
{
  ui->setupUi(this);

  QVector<QString> val;
  val.push_back("ID");
  val.push_back("Name");
  val.push_back("Message");

  QSqlQueryModel *query = new QSqlQueryModel(this);
  query->setQuery("select id_message, us.name_user, message_chatall from all_chat as ac inner join users as us on us.id_user = ac.id_user");
  if(query->lastError().isValid())
    qDebug() << query->lastError();

  for(int i = 0, j = 0; i < query->columnCount(); i++, j++)
    query->setHeaderData(i,Qt::Horizontal,val[j]);

  ui->tableView->setModel(query);
  ui->tableView->setColumnHidden(0,true);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
 }

PublicChat::~PublicChat()
{
  qDebug() << "Exit public chat";
  delete ui;
}

