#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Methods for connecting to the database
 * */
void DataBase::connectToDataBase()
{
    if(!QFile("/Users/denystundzher/Documents/Programming IOS/Swift App/Databases/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Methods for restoring the database
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Failed to restore the database";
        return false;
    }
    return false;
}

/* The method to open the database
 * */
bool DataBase::openDataBase()
{
    /* Database opens along a predetermined path and the database name, if it exists
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("/Users/denystundzher/Documents/Programming IOS/Swift App/Databases/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Method for closing database
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* The method for creating a database table
 * */
bool DataBase::createTable()
{
    /* In this case, a forming raw SQL-query with its subsequent execution.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_DATE      " DATE            NOT NULL,"
                            TABLE_TIME      " TIME            NOT NULL,"
                            TABLE_RANDOM    " INTEGER         NOT NULL,"
                            TABLE_MESSAGE   " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* The method to insert records into the database
 * */
bool DataBase::insertIntoTable(const QVariantList &data)
{
    /* SQL Query formed from QVariantList,
     * which are transmitted in data to be inserted into the table.
     * */
    QSqlQuery query;
    /* e SQL query is generated beginning with keys,
     * which then bind with bindValue method for substituting data from QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                                             TABLE_TIME ", "
                                             TABLE_RANDOM ", "
                                             TABLE_MESSAGE " ) "
                  "VALUES (:Date, :Time, :Random, :Message )");
    query.bindValue(":Date",        data[0].toDate());
    query.bindValue(":Time",        data[1].toTime());
    query.bindValue(":Random",      data[2].toInt());
    query.bindValue(":Message",     data[3].toString());
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
