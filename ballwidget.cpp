#include "ballwidget.h"
#include <QPainter>
#include <QDebug>
#include <QImage>

BallWidget::BallWidget(int width, int height, QObject* parent)
	: QObject(parent), bounds_(QRect(0, 0, width, height)),
      color_(QColor(255, 255, 255)),
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

void BallWidget::setColor(int r, int g, int b)
{
    color_ = QColor(r, g, b);
}

void BallWidget::setBounds(const QRect &bounds)
{
    bounds_ = bounds;
    image_ = QImage(bounds.width(), bounds.height(), QImage::Format_RGB32);
    emit boundsUpdated(bounds);
}

void BallWidget::setRadius(int radius)
{
    radius_ = radius;
}

QRect BallWidget::bounds() const
{
	return bounds_;
}
