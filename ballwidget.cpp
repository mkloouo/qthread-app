#include "ballwidget.h"
#include <QPainter>
#include <QDebug>
#include <QImage>

BallWidget::BallWidget(int width, int height, QObject* parent)
	: QObject(parent), bounds_(QRect(0, 0, width, height)),
	  color_(QColor(255, 0, 0)), image_(QImage(width, height,
											   QImage::Format_RGB32))
{
}

void BallWidget::updatePosition(QPointF pos)
{
	pos_ = pos;
	updateImage();
}

void BallWidget::updateBounds(QRect bounds)
{
	bounds_ = bounds;
	updateImage();
}

void BallWidget::updateColor(QColor color)
{
	color_ = color;
	updateImage();
}

void BallWidget::updateRadius(int radius)
{
	radius_ = radius;
	updateImage();
}

void BallWidget::updateImage()
{
	QPainter painter(&image_);
	painter.fillRect(image_.rect(),QColor(Qt::black));
	painter.setPen(color_);
	painter.drawEllipse(pos_, radius_, radius_);
	emit movedBall(image_);
}

QRect BallWidget::bounds() const
{
	return bounds_;
}
