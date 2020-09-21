#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>

// driver default path
#ifdef QT_DEBUG
#define DRIVER_OPENSSL  "/home/dev/test/QSqlCipherDriver/build-sqlcipher-Desktop_Qt_5_6_2_GCC_64bit-Debug/libQSqlCipher_openssl.so"
#define DRIVER_ARIA     "/home/dev/test/QSqlCipherDriver/build-sqlcipher-Desktop_Qt_5_6_2_GCC_64bit-Debug/libQSqlCipher_aria.so"
#else
#define DRIVER_OPENSSL  "/root/libQSqlCipherDriver_openssl.so"  //"/usr/lib/qt/plugins/sqldrivers/libQSqlCipherDriver_openssl.so"
#define DRIVER_ARIA     "/root/libQSqlCipherDriver_aria.so"     //"/usr/lib/qt/plugins/sqldrivers/libQSqlCipherDriver_aria.so"
#endif
// sqlicpher default passwd
#define DEF_PASSWD      "ktnc0118!!"

class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QObject *parent = 0);
    ~DbManager();

    QSqlDatabase sqlDatabase() const;

    bool loadSqlCipherDriver(QSqlDatabase& db, bool bIsLoadCipher=true, bool bIsOpenssl=true, bool bIffailThenLoadDef=true, const QString& strPasswd = "ktnc0118!!");

private:
    void openDb();
    void createTables();

    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
