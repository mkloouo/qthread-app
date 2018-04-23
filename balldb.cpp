#include "balldb.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

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

bool BallDb::createBallTable()
{
    query_.prepare("CREATE TABLE IF NOT EXISTS phys_table ("
                   "id integer PRIMARY KEY,"
                   "px integer NOT NULL,"
                   "py integer NOT NULL,"
                   "dx real NOT NULL,"
                   "dy real NOT NULL,"
                   "speed int NOT NULL )");
    bool success = query_.exec();
    if (!success) {
        qDebug() << "Error creating table: " << query_.lastError();
    }
    return (success);
}

bool BallDb::ballTableExists()
{
	auto tables = db_.tables();
    return tables.contains("phys_table");
}

bool BallDb::getBallData(QPointF& pos, QPointF& dir, int& speed)
{
    Q_UNUSED(pos)
    Q_UNUSED(dir)
    query_.prepare("SELECT * FROM phys_table WHERE id = 1");
    bool success = query_.exec();
    if (success) {
        query_.next();
        pos.rx() = query_.value(1).toFloat();
        pos.ry() = query_.value(2).toFloat();
        dir.rx() = query_.value(3).toFloat();
        dir.ry() = query_.value(4).toFloat();
        speed = query_.value(5).toInt();
    } else {
        qDebug() << "Error getting ball data: " << query_.lastError();
    }
    return success;
}

bool BallDb::insertBallData(QPointF pos, QPointF dir, int speed)
{
    query_.prepare("INSERT INTO phys_table (px, py, dx, dy, speed) VALUES (:posx, :posy, :dirx, :diry, :speed)");
    query_.bindValue(":posx", pos.x());
    query_.bindValue(":posy", pos.y());
    query_.bindValue(":dirx", dir.x());
    query_.bindValue(":diry", dir.y());
    query_.bindValue(":speed", speed);

    bool success = query_.exec();
    if (!success) {
        qDebug() << "Error inserting ball data: " << query_.lastError();
    }
    return success;
}

bool BallDb::updateBallData(QPointF pos, QPointF dir, int speed)
{
    query_.prepare("UPDATE phys_table SET px = :posx, py = :posy, dx = :dirx, dy = :diry, speed = :speed WHERE id = 1");
    query_.bindValue(":posx", pos.x());
    query_.bindValue(":posy", pos.y());
    query_.bindValue(":dirx", dir.x());
    query_.bindValue(":diry", dir.y());
    query_.bindValue(":speed", speed);

    bool success = query_.exec();
    if (!success) {
        qDebug() << "Error updating ball: " << query_.lastError();
    }
    return success;
}
