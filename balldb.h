#ifndef BALLDB_H
#define BALLDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class BallDb : public QObject
{
	Q_OBJECT
public:
	explicit BallDb(QString path, QObject *parent = nullptr);
	~BallDb();

	bool createTable();
	bool tableExists();

//	bool getBallData(QPointF pos, QPointF dir);
//	bool storeBallData(QPointF pos, QPointF dir);

private:
	QSqlDatabase db_;
	QSqlQuery query_;

};

#endif // BALLDB_H
