#ifndef BALLPHYSICS_H
#define BALLPHYSICS_H

#include <QObject>
#include <QPoint>
#include <QRect>

class BallPhysics : public QObject
{
	Q_OBJECT
public:
	explicit BallPhysics(QPointF pos, QPointF dir,
						 QRect bounds, QObject *parent = nullptr);
	~BallPhysics();

public slots:
	void getNewPosition();

signals:
	void newPosition(QPointF position);

private:
	QPointF position_;
	QPointF direction_;
	QRect bounds_;

};

#endif // BALLPHYSICS_H
