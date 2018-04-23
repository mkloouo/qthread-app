#include "ballcontroller.h"
#include <QDebug>

BallController::BallController(int width, int height, QObject* parent)
    : QObject(parent), ballWidget_(width, height),
      ballPhysics_(QPoint(width / 2, height / 2), QPointF(0.7f, 0.3f), ballWidget_.bounds()),
	  isRunning_(false)
{

	ballWidget_.moveToThread(&widgetThread_);
	ballPhysics_.moveToThread(&physicsThread_);

	QObject::connect(&physicsThread_, &QThread::started,
					 &ballPhysics_, &BallPhysics::getNewPosition);
	QObject::connect(this, &BallController::getBallImage,
					 &ballPhysics_, &BallPhysics::getNewPosition);
	QObject::connect(&ballPhysics_, &BallPhysics::newPosition,
					 &ballWidget_, &BallWidget::updateImage, Qt::DirectConnection);

	QObject::connect(&ballWidget_, &BallWidget::updatedImage,
					 this, &BallController::updatedImage, Qt::DirectConnection);
    QObject::connect(&ballWidget_, &BallWidget::boundsUpdated,
                     &ballPhysics_, &BallPhysics::updateBounds, Qt::DirectConnection);

	ballWidget_.setRadius(30);
}

BallController::~BallController()
{
	stopBall();
}

void BallController::startBall(const QRect& bounds)
{
	if (!isRunning_) {
        ballWidget_.setBounds(bounds);
		widgetThread_.start();
		physicsThread_.start();
		isRunning_ = true;
	}
}

void BallController::stopBall()
{
	if (isRunning_) {
		widgetThread_.quit();
		physicsThread_.quit();
		widgetThread_.wait();
		physicsThread_.wait();
		isRunning_ = false;
    }
}

void BallController::changeColor()
{
    ballWidget_.setColor(qrand() % 255, qrand() % 255, qrand() % 255);
}

void BallController::speedUp()
{
    ballPhysics_.speedUp();
}

void BallController::speedDown()
{
    ballPhysics_.speedDown();
}
