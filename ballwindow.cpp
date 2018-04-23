#include "ballwindow.h"
#include "ui_ballwindow.h"

#include <QDebug>

BallWindow::BallWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BallWindow)
{
	ui->setupUi(this);

	QObject::connect(ui->startPushButton, &QPushButton::clicked,
					 &ballController_, &BallController::startBall);
	QObject::connect(ui->stopPushButton, &QPushButton::clicked,
					 &ballController_, &BallController::stopBall);

	QObject::connect(&ballController_, &BallController::updatedImage,
					 this, &BallWindow::updateLabel);
	QObject::connect(this, &BallWindow::updatedLabel,
					 &ballController_, &BallController::getBallImage);
}

BallWindow::~BallWindow()
{
	delete ui;
}

void BallWindow::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void BallWindow::updateLabel(QImage image)
{
	ui->imageLabel->setPixmap(QPixmap::fromImage(image));
	emit updatedLabel();
}
