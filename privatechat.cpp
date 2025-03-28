#include "privatechat.hpp"
#include "ui_privatechat.h"

PrivateChat::PrivateChat(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PrivateChat)
{
  ui->setupUi(this);
}

PrivateChat::~PrivateChat()
{
  qDebug() << "Exit private chat";
  delete ui;
}

void PrivateChat::on_btn_search_clicked()
{
  tableviewLoad(ui->lb_who->text(), ui->lb_towhom->text());
}

void PrivateChat::tableviewLoad(QString str1, QString str2)
{
  QVector<QString> val;
  val.push_back("ID");
  val.push_back("Name");
  val.push_back("Message");

  QSqlQueryModel *query = new QSqlQueryModel(this);
  query->setQuery("select msg.id_message_chat, us.name_user, msg.message_chat from chat_users as cu \
                  inner join msg_usr_chat as msg on cu.id_chat = msg.id_chat \
                  inner join users as us on us.id_user = msg.id_user_upload \
                  where cu.id_useroutput = (select id_user from users where name_user = '" + str1 + "') \
                  and cu.id_userinput = (select id_user from users where name_user = '" + str2 + "')");
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
