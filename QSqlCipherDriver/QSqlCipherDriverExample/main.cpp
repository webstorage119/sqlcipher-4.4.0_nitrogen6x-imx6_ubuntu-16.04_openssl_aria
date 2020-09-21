#include "dbmanager.h"

#include <QCoreApplication>

#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

#include "dbschema.h"

#define PRINT_STATE(ok) { qDebug() << (ok ? "...Done" : "...Failed"); }

void HowTo()
{
    qInfo() << "./QSqlCipherDriverExample -cipher [openssl/aria]";
    return;
}

int main(int argc, char *argv[])
{
    DbManager dbManager;
    QSqlDatabase db;

    QString strParam1 = "-cipher";
    QString strOpenssl = "openssl";
    QString strAria = "aria";

    QCoreApplication a(argc, argv);

    qDebug() << "Drviers : " << QSqlDatabase::drivers();

    //db = QSqlDatabase::addDatabase("QSQLCIPHER_OPENSSL");
    db = QSqlDatabase::addDatabase("QSQLCIPHER_ARIA");

//    if (argc <= 2) {
//        // load default driver
//        if (dbManager.loadSqlCipherDriver(db, false) == false) {
//            return 0;
//        }
//    } else if (argc == 3) {
//        if (strParam1.compare(argv[1], Qt::CaseInsensitive) == 0) {
//            if (strOpenssl.compare(argv[2], Qt::CaseInsensitive) == 0) {
//                // load openssl or default driver
//                if (dbManager.loadSqlCipherDriver(db, true, true, false, "1111") == false) {
//                    return 0;
//                }
//            } else if (strAria.compare(argv[2], Qt::CaseInsensitive) == 0) {
//                // load aria or default driver
//                if (dbManager.loadSqlCipherDriver(db, true, false, false, "2222") == false) {
//                    return 0;
//                }
//            } else {
//                // load openssl or default driver
//                if (dbManager.loadSqlCipherDriver(db, true, true, false, "1111") == false) {
//                    return 0;
//                }
//            }
//        } else {
//            // load default driver
//            if (dbManager.loadSqlCipherDriver(db, false) == false) {
//                return 0;
//            }
//        }
//    } else {
//        HowTo();
//        return 0;
//    }

    //QSqlDatabase db = dbManager.sqlDatabase();
    //QSqlDatabase db1 = QSqlDatabase::addDatabase("QtSQLiteCipher");


    //=====================================================
    if (db.isValid()) {

        db.setPassword("1111");

        if (strOpenssl.compare(argv[2], Qt::CaseInsensitive) == 0)
            db.setDatabaseName("test_openssl.db");
        else if (strAria.compare(argv[2], Qt::CaseInsensitive) == 0)
            db.setDatabaseName("test_aria.db");
        else
            db.setDatabaseName("test.db");
        if (!db.open()) {
            qCritical() << "Open db failed";
            return 0;
        }

        QSqlQuery sqlQuery(db);
        if (db.tables(QSql::Tables).isEmpty()) {
            int tablesCount = arraySize(kCreationScriptsList);
            for (int i = 0; i < tablesCount; ++i)
            {
                QSqlQuery sqlQuery(db);
                bool result = sqlQuery.exec(kCreationScriptsList[i]);
                Q_ASSERT_X(result, Q_FUNC_INFO, sqlQuery.lastError().text().toLocal8Bit());
            }
        }

    } else {
        qCritical() << "db is not available";
        return 0;
    }
    //=====================================================


    //=====================================================
    qDebug() << "Test insert";
    QSqlQuery sqlQuery(db);
    bool ok = sqlQuery.exec("INSERT INTO profile(profile_name, email) "
                            "VALUES('test_profile', 'example@mail.com')");
    PRINT_STATE(ok);
    if (!ok)
    {
        qCritical() << "Cannot execute INSERT query " << sqlQuery.lastError().text();
        return 0;
    }

    //=====================================================
    qDebug() << "Test select";
    ok = sqlQuery.exec("SELECT profile_name, email FROM profile");
    PRINT_STATE(ok);
    if (!ok)
    {
        qCritical() << "Cannot execute SELECT query " << sqlQuery.lastError().text();
        return 0;
    }
    while (sqlQuery.next())
    {
        qDebug() << "profile_name: " << sqlQuery.value(0).toString();
        qDebug() << "email: " << sqlQuery.value(1).toString();
    }

    //=====================================================
//    qDebug() << "Test delete";
//    ok = sqlQuery.exec("DELETE FROM profile WHERE profile_name = 'test_profile'");
//    PRINT_STATE(ok);
//    if (!ok)
//    {
//        qCritical() << "Cannot execute DELETE query " << sqlQuery.lastError().text();
//        return 0;
//    }

    return 1;
}
