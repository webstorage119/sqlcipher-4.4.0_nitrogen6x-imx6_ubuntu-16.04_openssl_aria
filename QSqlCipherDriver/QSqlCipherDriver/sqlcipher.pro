
############################################
# When use cipher aria
#DEFINES += SQLCIPHER_CRYPTO_ARIA=1
#TARGET = QSqlCipherDriver_aria

# When use cipher openssl aes-cbc-256
TARGET = QSqlCipherDriver_openssl
############################################

#CONFIG(debug, debug|release) {
#	TARGET = QSqlCipherDriver
#}else{
#	TARGET = QSqlCipherDriver
#}


android {
    TEMPLATE = app
} else {
    TEMPLATE = lib
}

QT      *= core sql

CONFIG  += c++11 plugin

include($$PWD/sqlite3/sqlite3.pri)

target.path = $$[QT_INSTALL_PLUGINS]/sqldrivers/
INSTALLS += target

HEADERS  += \
    $$PWD/sqlcipher_p.h \
    $$PWD/sqlcachedresult_p.h \
    $$PWD/sqlcipher_global.h
SOURCES  += \
    $$PWD/smain.cpp \
    $$PWD/sqlcipher.cpp \
    $$PWD/sqlcachedresult.cpp
OTHER_FILES +=

!system-sqlite:!contains( LIBS, .*sqlite.* ) {
    CONFIG(release, debug|release):DEFINES *= NDEBUG
	#DEFINES += SQLITE_OMIT_LOAD_EXTENSION SQLITE_OMIT_COMPLETE QT_PLUGIN
	DEFINES += QT_PLUGIN
    blackberry: DEFINES += SQLITE_ENABLE_FTS3 SQLITE_ENABLE_FTS3_PARENTHESIS SQLITE_ENABLE_RTREE
    wince*: DEFINES += HAVE_LOCALTIME_S=0
} else {
    LIBS *= $$QT_LFLAGS_SQLITE
    QMAKE_CXXFLAGS *= $$QT_CFLAGS_SQLITE
}

LIBS += -lcrypto

DISTFILES += \
    QSqlCipherDriverPlugin_aria.json \
    QSqlCipherDriverPlugin_openssl.json
