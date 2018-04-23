#include "ballcontroller.h"
#include <QDebug>

BallController::BallController(QObject* parent)
	: QObject(parent), ballWidget_(400, 400),
	  ballPhysics_(QPoint(200, 200), QPointF(0.7f, 0.3f), ballWidget_.bounds()),
	  started_(false)
{

	ballWidget_.moveToThread(&widgetThread_);
	ballPhysics_.moveToThread(&physicsThread_);

	QObject::connect(&physicsThread_, &QThread::started,
					 &ballPhysics_, &BallPhysics::getNewPosition);
	QObject::connect(this, &BallController::updateImage,
					 &ballPhysics_, &BallPhysics::getNewPosition);
	QObject::connect(&ballPhysics_, &BallPhysics::newPosition,
					 &ballWidget_, &BallWidget::updatePosition, Qt::DirectConnection);

	QObject::connect(&ballWidget_, &BallWidget::movedBall,
					 this, &BallController::updatedImage, Qt::DirectConnection);

	ballWidget_.updateRadius(30);
}

BallController::~BallController()
{
	stopThreads();
}

void BallController::startThreads()
{
	if (!started_) {
		widgetThread_.start();
		physicsThread_.start();
		started_ = true;
	}
}

void BallController::stopThreads()
{
	if (started_) {
		widgetThread_.quit();
		physicsThread_.quit();
		widgetThread_.wait();
		physicsThread_.wait();
		started_ = false;
		emit threadsFinished();
	}
}
