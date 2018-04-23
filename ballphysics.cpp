#include "ballphysics.h"

#include <QThread>
#include <QDebug>

BallPhysics::BallPhysics(QPointF pos, QPointF dir,
						 QRect bounds, QObject *parent)
	: QObject(parent), position_(pos), direction_(dir),
      bounds_(bounds), db_("ball.db"), speed_(10)
{
    if (db_.ballTableExists()) {
        db_.getBallData(position_, direction_, speed_);
    } else {
        db_.createBallTable();
        db_.insertBallData(position_, direction_, speed_);
    }
}

BallPhysics::~BallPhysics()
{
    db_.updateBallData(position_, direction_, speed_);
}

void BallPhysics::speedUp()
{
    if (speed_ > 0) {
        speed_ -= 1;
    }
}

void BallPhysics::speedDown()
{
    speed_ += 1;
}

void BallPhysics::getNewPosition()
{
	if (position_.x() > bounds_.right() || position_.x() < bounds_.left()) {
		direction_.rx() *= -1;
	} else if (position_.y() > bounds_.bottom() || position_.y() < bounds_.top()) {
		direction_.ry() *= -1;
	}

	position_ += direction_;

    this->thread()->msleep(speed_);
    emit newPosition(position_);
}

void BallPhysics::updateBounds(QRect bounds)
{
    bounds_ = bounds;
}
