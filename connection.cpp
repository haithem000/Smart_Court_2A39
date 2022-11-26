<<<<<<< Updated upstream
#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("wejden");//inserer nom de l'utilisateur
db.setPassword("wejden");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

=======
#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("wejden");//inserer nom de l'utilisateur
db.setPassword("wejden");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

>>>>>>> Stashed changes
