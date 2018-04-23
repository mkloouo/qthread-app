#ifndef BALLCONTROLLER_H
#define BALLCONTROLLER_H

#include <QObject>
#include <QThread>

#include "ballphysics.h"
#include "ballwidget.h"

class BallController : public QObject
{
	Q_OBJECT
public:
	BallController(QObject* parent = nullptr);
	~BallController();

public slots:
	void startBall();
	void stopBall();

signals:
	void getBallImage();
	void updatedImage(QImage picture);

private:
	QThread widgetThread_;
	QThread physicsThread_;
	BallWidget ballWidget_;
	BallPhysics ballPhysics_;
	bool isRunning_;

};

#endif // BALLCONTROLLER_H
