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
