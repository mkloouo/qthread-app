#ifndef BALLWIDGET_H
#define BALLWIDGET_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QRect>

class BallWidget : public QObject
{
	Q_OBJECT

public:
	explicit BallWidget(int width, int height, QObject* parent = 0);

	QRect bounds() const;

public slots:
	void updatePosition(QPointF pos);
	void updateBounds(QRect bounds);
	void updateColor(QColor color);
	void updateRadius(int radius);
	void updateImage();

signals:
	void movedBall(QImage image);

private:
	QPointF pos_;
	QRect bounds_;
	QColor color_;
	int radius_;
	QImage image_;

};

#endif // BALLWIDGET_H
