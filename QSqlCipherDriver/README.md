2020.07.17 changed by Hwang
========================================

1. Caution of compile
   1) Compile with openssl
       (1) open "sqlcipher.pro"
	   (2) go to 8 line
	   (3) remove comment "TARGET = QSqlCipherDriver_openssl"
	   (4) go to 4 line
	   (5) comment "#DEFINES += SQLCIPHER_CRYPTO_ARIA=1"
	   (6) go to 5 line
	   (7) comment "#TARGET = QSqlCipherDriver_aria"
	   (8) open "sqlit3.c"
	   (9) go to 34 line
	   (10) comment "//#define SQLCIPHER_CRYPTO_ARIA"
   1) Compile with aria
       (1) open "sqlcipher.pro"
	   (2) go to 8 line
	   (3) comment "#TARGET = QSqlCipherDriver_openssl"
	   (4) go to 4 line
	   (5) remove comment "DEFINES += SQLCIPHER_CRYPTO_ARIA=1"
	   (6) go to 5 line
	   (7) remove comment "TARGET = QSqlCipherDriver_aria"
	   (8) open "sqlit3.c"
	   (9) go to 34 line
	   (10) remove comment "#define SQLCIPHER_CRYPTO_ARIA"



2020.07.13 Changed by Hwang
========================================

1. Directory and file
  1) Project directory - ./QSqlCipherDriver
  2) sqlcipher source and project file and directory - ./QSqlCipherDriver/QSqlCipherDriver/sqlit3
  3) Qt project and interface source directory - ./QSqlCipherDriver
  4) Qt sql driver name file - openssl => ./QSqlCipherDriver/QSqlCipherDriver/QSqlCipherDriverPlugin_openssl.json
                               aria => ./QSqlCipherDriver/QSqlCipherDriver/QSqlCipherDriverPlugin_aria.json
							   project file => ./QSqlCipherDriver/QSqlCipherDriver/sqlcipher.pro
  5) Example directory - ./QSqlCipherDriver/QSqlCipherDriverExample
  6) output directory - ./QSqlCipherDriver/buid-xxx

2. For Qt plugin(sql driver) names
  1) openssl => ./QSqlCipherDriver/QSqlCipherDriver/QSqlCipherDriverPlugin_openssl.json
  2) aria => ./QSqlCipherDriver/QSqlCipherDriver/QSqlCipherDriverPlugin_aria.json

3. For Qt interface sources
  1) ./QSqlCipherDriver/QSqlCipherDriver/sqlcachedresult_p.h
  2) ./QSqlCipherDriver/QSqlCipherDriver/sqlcipher_global.h
  3) ./QSqlCipherDriver/QSqlCipherDriver/sqlcipher_p.h
  4) ./QSqlCipherDriver/QSqlCipherDriver/smain.cpp
  5) ./QSqlCipherDriver/QSqlCipherDriver/sqlcachedresult.cpp
  6) ./QSqlCipherDriver/QSqlCipherDriver/sqlcipher.cpp

4. ARIA cipher source
  1) ./QSqlCipherDriver/QSqlCipherDriver/sqlit3/src/Aria.c
  2) ./QSqlCipherDriver/QSqlCipherDriver/sqlit3/src/Aria.h

5. How to compile
  1) prerequsite
     (1) openssl 1.0.2 static or shared for linux(ubuntu 16.04) and arm
	 (2) qt 5.6.1 for linux(ubuntu 16.04) and arm
	 (3) ubuntu 16.04 x64 cross compile environment
	 (4) nitrogen 6x buildroot - cross tool chain (arm-linux-gnueabihf-gcc v6.4.1)
	 (5) tcltk - 8.5.19
	 (6) gcc 6.5 for x32/64
  2) nitorgen 6x x32 with qt creator
     (1) open qt creator
	 (2) open qt project in ./QSqlCipherDriver/QSqlCipherDriver/sqlcipher.pro
	 (3) qt project already have configuration with cross tool chain.
	 
	 
	 
2020.06.29 Changed by Hwang
========================================

Requirements and Enviroments

1. Cross Desktop Enviroments
    1) Ubuntu 16.04 x64
    2) openssl 1.0.2g
	3) Qt 5.6.2
	4) Qt Creator 4.7.2
	5) gcc 6.5
	6) qt sqlite3 driver based wxSQLite3 - 0.6
	7) sqlcipher 4.4.0
	8) additional cipher algorithm is ARIA of KISA
	
2. Target Environments
    1) nitrogen6x x32
    1) Freescale i.MX6 Quad/DualLite - ARMv7 Processor rev 10 (v7l)
    2) buildroot 2017.02.11
	3) openssl 1.0.2o
	4) Qt 5.6.3
	5) Qt Creator 4.7.2
	6) gcc 6.4(arm-linux-gnueabihf)
	7) qt sqlite3 driver based wxSQLite3 - 0.6
	8) sqlcipher 4.4.0
	9) additional cipher algorithm is ARIA of KISA
	
3. comment by hwang
I referenced most code with tag version 0.6 of "https://github.com/devbean/QtCipherSqlitePlugin.git".
Because upper version than 0.6 version is not compiled within Qt 5.6.2 ~ 5.6.3 of my environments.




QtCipherSqlitePlugin
====================

A Qt plugin for cipher SQLite which is based on SQLite source and wxSQLite3 in wxWidget.

Qt is a full development framework with tools designed to streamline the creation of applications and user interfaces for desktop, embedded and mobile platforms. You could find more details at https://www.qt.io.

SQLite is a software library that implements a self-contained, serverless, zero-configuration, transactional SQL database engine. SQLite is the most widely deployed SQL database engine in the world. The source code for SQLite is in the public domain. You could find more details at http://www.sqlite.org/.

wxSQLite3 is a C++ wrapper around the public domain SQLite 3.x database and is specifically designed for use in programs based on the wxWidgets library. wxSQLite3 includes an optional extension for SQLite supporting key based database file encryption using 128 bit AES encryption. You could find more details at http://utelle.github.io/wxsqlite3. wxSQLite3 is released under wxWindows Library Licence.

You could find how to compile this plugin at http://qtciphersqliteplugin.galaxyworld.org.

Please read [Wiki](https://github.com/devbean/QtCipherSqlitePlugin/wiki) for more details.



