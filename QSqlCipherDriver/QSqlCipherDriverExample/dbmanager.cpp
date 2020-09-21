#include "dbmanager.h"

#include "dbschema.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QPluginLoader>
#include <QSqlDriverPlugin>

#include <QDebug>

static const char * const kDatabaseFileName = "db.dat";

QString sqliteLibraryPath()
{

#ifdef QT_DEBUG
    //QString filePath = "/path/to/qtsqlitecipherd";
    //QString filePath = "/home/dev/test/QtSQLiteCipher/build-QtSQLiteCipher-Desktop_Qt_5_6_2_GCC_64bit-Debug/libqtsqlitecipherd.so";
    //QString filePath = "/home/dev/Qt/5.6/gcc_64/plugins/sqldrivers/libsqlitecipherd.so";
    QString filePath = "/home/dev/test/QSqlCipherDriver/build-sqlcipher-Desktop_Qt_5_6_2_GCC_64bit-Debug/libQSqlCipherDriver.so";
#else
    //QString filePath = "/path/to/qtsqlitecipher";
    QString filePath = "/root/libQSqlCipherDriver.so";
#endif

    return filePath;
}

DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
    //openDb();
}

DbManager::~DbManager()
{
    QString connectionName = m_db.connectionName();
    m_db.close();
    m_db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connectionName);
}

bool DbManager::loadSqlCipherDriver(QSqlDatabase& db, bool bIsLoadCipher, bool bIsOpenssl, bool bIffailThenLoadDef, const QString& strPasswd)
{
    QSqlDriverPlugin *sqlPlugin = NULL;
    QObject *plugin = NULL;

    if ((bIsLoadCipher == true) && (bIsOpenssl == true))
    {
        qCritical() << "Try to Load sqlcipher with openssl plugin";

        QPluginLoader loader(DRIVER_OPENSSL);

        plugin = loader.instance();
        if (!plugin)
        {
            qCritical() << "Loading plugin failed => " << DRIVER_OPENSSL;

            if (bIffailThenLoadDef) {
                db = QSqlDatabase::addDatabase("QSQLITE");
                if (db.isValid()) {
                    qCritical() << "Loading sqlite default plugin success";
                    return true;
                } else
                    qCritical() << "Loading sqlite default plugin failed";
            }
            return false;
        }

        sqlPlugin  = qobject_cast<QSqlDriverPlugin *>(plugin);
        if (!sqlPlugin )
        {
            qCritical() << "Loading sqlite plugin failed => " << DRIVER_OPENSSL;

            if (bIffailThenLoadDef) {
                db = QSqlDatabase::addDatabase("QSQLITE");
                if (db.isValid()) {
                    qCritical() << "Loading sqlite default plugin success";
                    return true;
                } else
                    qCritical() << "Loading sqlite default plugin failed";
            }
            return false;
        }
    }
    else if ((bIsLoadCipher == true) && (bIsOpenssl == false))
    {
        qCritical() << "Try to Load sqlcipher with aria plugin";

        QPluginLoader loader(DRIVER_ARIA);

        plugin = loader.instance();
        if (!plugin)
        {
            qCritical() << "Loading plugin failed => " << DRIVER_ARIA;

            if (bIffailThenLoadDef) {
                db = QSqlDatabase::addDatabase("QSQLITE");
                if (db.isValid()) {
                    qCritical() << "Loading sqlite default plugin success";
                    return true;
                } else
                    qCritical() << "Loading sqlite default plugin failed";
            }
            return false;
        }

        sqlPlugin  = qobject_cast<QSqlDriverPlugin *>(plugin);
        if (!sqlPlugin )
        {
            qCritical() << "Loading sqlite plugin failed => " << DRIVER_ARIA;

            if (bIffailThenLoadDef) {
                db = QSqlDatabase::addDatabase("QSQLITE");
                if (db.isValid()) {
                    qCritical() << "Loading sqlite default plugin success";
                    return true;
                } else
                    qCritical() << "Loading sqlite default plugin failed";
            }
            return false;
        }
    }
    else
    {
        qCritical() << "Try to Load sqlite default plugin";

        if (bIffailThenLoadDef) {
            db = QSqlDatabase::addDatabase("QSQLITE");
            if (db.isValid()) {
                qCritical() << "Loading sqlite default plugin success";
                return true;
            } else
                qCritical() << "Loading sqlite default plugin failed";
        }
        return false;
    }

    db = QSqlDatabase::addDatabase(sqlPlugin->create("QSQLCIPHER"));
    if (strPasswd.length())
        db.setPassword(strPasswd);
    else
        db.setPassword("ktnc0118!!");

    if (db.isValid())
        return true;
    else
        return false;
}

void DbManager::openDb()
{
    QString filePath = sqliteLibraryPath();
    QPluginLoader loader(filePath);
    QObject *plugin = loader.instance();

    if (!plugin)
    {
        qCritical() << "Loading plugin failed";
        return;
    }

    QSqlDriverPlugin *sqlPlugin  = qobject_cast<QSqlDriverPlugin *>(plugin);

    if (!sqlPlugin )
    {
        qCritical() << "Loading sqlite plugin failed";
        return;
    }

    //m_db = QSqlDatabase::addDatabase(sqlPlugin->create("QtSQLiteCipher"));
    m_db = QSqlDatabase::addDatabase(sqlPlugin->create("QSQLCIPHER"));
    m_db.setPassword("1234567890");

    m_db.setConnectOptions("QSQLITE_BUSY_TIMEOUT=20000");
    m_db.setDatabaseName(kDatabaseFileName);
    if (!m_db.open())
    {
        QString errorText(m_db.lastError().text());
        qCritical() << errorText;
        return;
    }

    QSqlQuery sqlQuery(m_db);
    sqlQuery.exec("PRAGMA foreign_keys = ON;");
    if (m_db.tables(QSql::Tables).isEmpty())
        createTables();
}

void DbManager::createTables()
{
    int tablesCount = arraySize(kCreationScriptsList);
    for (int i = 0; i < tablesCount; ++i)
    {
        QSqlQuery sqlQuery(m_db);
        bool result = sqlQuery.exec(kCreationScriptsList[i]);
        Q_ASSERT_X(result,
                   Q_FUNC_INFO,
                   sqlQuery.lastError().text().toLocal8Bit());
    }
}

QSqlDatabase DbManager::sqlDatabase() const
{
    return m_db;
}

