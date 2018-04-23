#ifndef BALLDB_H
#define BALLDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPoint>

class BallDb : public QObject
{
	Q_OBJECT
public:
	explicit BallDb(QString path, QObject *parent = nullptr);
	~BallDb();

    bool createBallTable();
    bool ballTableExists();

    bool getBallData(QPointF& pos, QPointF& dir, int& speed);
    bool insertBallData(QPointF pos, QPointF dir, int speed);
    bool updateBallData(QPointF pos, QPointF dir, int speed);

private:
	QSqlDatabase db_;
	QSqlQuery query_;

};

#endif // BALLDB_H
