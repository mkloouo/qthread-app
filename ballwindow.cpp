#include "ballwindow.h"
#include "ui_ballwindow.h"

#include <QDebug>

BallWindow::BallWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BallWindow)
{
	ui->setupUi(this);

    ballController_ = new BallController(ui->imageLabel->width(),
                                         ui->imageLabel->height(), this);
	QObject::connect(ui->startPushButton, &QPushButton::clicked,
                     this, &BallWindow::clickedStart);
    QObject::connect(this, &BallWindow::startBallBounds,
                     ballController_, &BallController::startBall);
	QObject::connect(ui->stopPushButton, &QPushButton::clicked,
                     ballController_, &BallController::stopBall);

    QObject::connect(ballController_, &BallController::updatedImage,
					 this, &BallWindow::updateLabel);
	QObject::connect(this, &BallWindow::updatedLabel,
                     ballController_, &BallController::getBallImage);

    QObject::connect(ui->colorPushButton, &QPushButton::clicked,
                     ballController_, &BallController::changeColor);
    QObject::connect(ui->speedUpPushButton, &QPushButton::clicked,
                     ballController_, &BallController::speedUp);
    QObject::connect(ui->speedDownPushButton, &QPushButton::clicked,
                     ballController_, &BallController::speedDown);
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

void BallWindow::clickedStart()
{
    emit startBallBounds(ui->imageLabel->geometry());
}
