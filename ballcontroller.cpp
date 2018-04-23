#include "ballcontroller.h"
#include <QDebug>

BallController::BallController(QObject* parent)
	: QObject(parent), ballWidget_(400, 400),
	  ballPhysics_(QPoint(200, 200), QPointF(0.7f, 0.3f), ballWidget_.bounds()),
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

	ballWidget_.setRadius(30);
}

BallController::~BallController()
{
	stopBall();
}

void BallController::startBall()
{
	if (!isRunning_) {
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
