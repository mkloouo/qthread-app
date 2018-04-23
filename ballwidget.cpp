#include "ballwidget.h"
#include <QPainter>
#include <QDebug>
#include <QImage>

BallWidget::BallWidget(int width, int height, QObject* parent)
	: QObject(parent), bounds_(QRect(0, 0, width, height)),
	  color_(QColor(255, 255, 0)),
	  image_(QImage(width, height, QImage::Format_RGB32))
{
}

void BallWidget::updateImage(QPointF pos)
{
	pos_ = pos;
	QPainter painter(&image_);
	painter.fillRect(image_.rect(),QColor(Qt::black));
	painter.setPen(color_);
	painter.drawEllipse(pos_, radius_, radius_);
	emit updatedImage(image_);
}

void BallWidget::setRadius(int radius)
{
	radius_ = radius;
}

QRect BallWidget::bounds() const
{
	return bounds_;
}
