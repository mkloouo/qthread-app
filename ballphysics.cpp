#include "ballphysics.h"

#include <QThread>

BallPhysics::BallPhysics(QPointF pos, QPointF dir,
						 QRect bounds, QObject *parent)
	: QObject(parent), position_(pos), direction_(dir),
	  bounds_(bounds)
{
}

BallPhysics::~BallPhysics()
{

}

void BallPhysics::getNewPosition()
{
	if (position_.x() > bounds_.right() || position_.x() < bounds_.left()) {
		direction_.rx() *= -1;
	} else if (position_.y() > bounds_.bottom() || position_.y() < bounds_.top()) {
		direction_.ry() *= -1;
	}

	position_ += direction_;

	this->thread()->msleep(10);
	emit newPosition(position_);
}
