#include "balldb.h"
#include <QDebug>
#include <QSqlQuery>

BallDb::BallDb(QString path, QObject* parent)
	: QObject(parent)
{
	db_ = QSqlDatabase::addDatabase("QSQLITE");
	db_.setDatabaseName(path);

	if (!db_.open()) {
		qDebug() << "Error loading database from" << path;
	}
	query_ = QSqlQuery(db_);
}

BallDb::~BallDb()
{
	db_.close();
}

bool BallDb::createTable()
{
	query_.prepare("CREATE TABLE IF NOT EXISTS ball_table ("
				   "ball_app_id integer PRIMARY KEY,"
				   "pos_x integer NOT NULL,"
				   "pos_y integer NOT NULL,"
				   "dir_x real NOT NULL,"
				   "dir_y real NOT NULL"
				   ");");
	return (query_.exec());
}

bool BallDb::tableExists()
{
	auto tables = db_.tables();
	return tables.contains(tr("ball_table"));
}
