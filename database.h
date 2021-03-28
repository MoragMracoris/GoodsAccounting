#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QStyle>

/* Directive table names, fields, tables, and databases */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "UkrainianRevolutionGuideDb.db"

#define TABLE                   "Persons"
#define TABLE_DATE              "Date"
#define TABLE_TIME              "Time"
#define TABLE_MESSAGE           "Message"
#define TABLE_RANDOM            "Random"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Methods for direct work with the class to connect
     * to a database and insert records into the table
     * */
    void connectToDataBase();
    bool insertIntoTable(const QVariantList &data);

private:
    // The very object database, which will be work
    QSqlDatabase    db;

private:
    /* Internal methods for working with database
     * */
    bool openDataBase();
    void closeDataBase();

    bool createTable();
    bool restoreDataBase();
};

#endif // DATABASE_H
