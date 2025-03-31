### Разработка ведётся на Debian 12.7 с использованием qtcreator

### Код:
``` c++
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL"); // Здесь указывается какая база данных будет использоваться. В моём случае PostgreSQL
  db.setDatabaseName("Ваша база данных");
  db.setUserName("Ваш пользователь от базы данных");
  db.setPassword("Ваш пароль от базы данных");

  if(!db.open()) { // Проверка на соединение с базой
    qDebug() << "Connection in database failed";
    return false;
  }
  else {
    qDebug() << "Connection in database complited!";
    return true;
  }
```

### Из mainwindow
``` c++
void MainWindow::tableviewLoad() { // Для загрузки данных в таблицу. Решил сделать в таблице, так как привычный для меня вариант просмотра.
  QVector<QString> val; // Объявляем здесь вектор header's
  val.push_back("ID"); // Заполняем его названиями столбцов
  val.push_back("Login");
  val.push_back("Password");
  val.push_back("Name");
  val.push_back("Enabled");

  QSqlQueryModel *query = new QSqlQueryModel(this); // Создаём модель в которую будет загружен запрос, чего именно мы хотим отобразить в таблице
  query->setQuery("select * from users order by 1");
  if(query->lastError().isValid()) // Проверяем запрос на ошибки
    qDebug() << query->lastError();

  for(int i = 0, j = 0; i < query->columnCount(); i++, j++) // Определяем данные хедеров
    query->setHeaderData(i,Qt::Horizontal,val[j]);

  ui->tableView->setModel(query); // Загружаем нашу модель в таблицу
  ui->tableView->setColumnHidden(0,true); // Скрываем не нужные столбцы
  ui->tableView->setColumnHidden(2,true);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Устанавливаем автоматическую размерность ячеек и столбцов. За всё отвечает дальнейшее
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
}
```
