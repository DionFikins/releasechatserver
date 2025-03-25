## Программа была переделана под Qt с нуля.

### Разработка велась на Debian 12.7 при использовании компилятора GCC и QT6.
#### P.S. Разрабатывалась на Линукс лишь потому, что на Windows без впн невозможно скачать QT.
#### Есть вариант того, что проект может не заработать на MCVS, если такое случится, отпишите об этом.

### Синтаксис программы
CMakeLists.txt
``` txt
find_package(PostgreSQL REQUIRED) //осталось ещё с первых наработок, когда пытался работать исключительно с postgresql без использования внутреннего функционала qt creator
target_include_directories(releasechat PRIVATE ${PostgreSQL_INCLUDE_DIRS}) //чтобы нашёл где все исполняемые файлы самостоятельно

target_link_libraries(releasechat PRIVATE Qt6::Sql) // для работы с QSQL библиотеками
target_link_libraries(releasechat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(releasechat PRIVATE ${PostgreSQL_LIBRARIES})
```
##### Примечание, если у Вас линукс, возможно Вам понадобиться доставить некоторые библиотеки. Вот список:
``` bash
apt install libqt4-dev libqt5sql5-psql postgresql
```
##### Это часть, которая может понадобиться, так же есть и библиотеки в самом qt, которые также завязаны на postgresql.

### Пример загрузки данных в своеобразный dataGrid.
``` c++
void MainWindow::tableviewLoad()
{
  QVector<QString> val; //вектор для Headers
  val.push_back("ID");
  val.push_back("Login");
  val.push_back("Password");
  val.push_back("Name");
  val.push_back("Enabled");

  QSqlQueryModel *query = new QSqlQueryModel(this); //объявляем модель запроса
  query->setQuery("select * from users order by 1"); //задаём сам запрсо
  if(query->lastError().isValid()) //проверка на выполнение запроса
    qDebug() << query->lastError(); //если невалиден, то выдаст в отладку сообщение почему

  for(int i = 0, j = 0; i < query->columnCount(); i++, j++) //цикл для объявления Header на каждую колонку
    query->setHeaderData(i,Qt::Horizontal,val[j]);

  ui->tableView->setModel(query); //задаём модель на использование в наш tableview
  ui->tableView->setColumnHidden(0,true); //скрываем не нужные столбцы
  ui->tableView->setColumnHidden(2,true);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
}
```
#### Аналогия и в других формах. Единственный рабочий вариант, который я нашёл.
