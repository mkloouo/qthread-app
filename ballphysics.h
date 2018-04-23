#ifndef BALLPHYSICS_H
#define BALLPHYSICS_H

#include <QObject>
#include <QPoint>
#include <QRect>

#include "balldb.h"

class BallPhysics : public QObject
{
	Q_OBJECT
public:
	explicit BallPhysics(QPointF pos, QPointF dir,
						 QRect bounds, QObject *parent = nullptr);
	~BallPhysics();

    void speedUp();
    void speedDown();

public slots:
    void getNewPosition();
    void updateBounds(QRect bounds);

signals:
	void newPosition(QPointF position);

private:
	QPointF position_;
	QPointF direction_;
	QRect bounds_;
	BallDb db_;
    int speed_;

};

#endif // BALLPHYSICS_H
