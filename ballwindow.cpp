#include "ballwindow.h"
#include "ui_ballwindow.h"

#include <QDebug>

BallWindow::BallWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BallWindow)
{
	ui->setupUi(this);

	QObject::connect(ui->startPushButton, &QPushButton::clicked,
					 &controller_, &BallController::startThreads);
	QObject::connect(ui->stopPushButton, &QPushButton::clicked,
					 &controller_, &BallController::stopThreads);

	QObject::connect(&controller_, &BallController::updatedImage,
					 this, &BallWindow::updateLabel);
	QObject::connect(this, &BallWindow::updated,
					 &controller_, &BallController::updateImage);
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
	emit updated();
}
