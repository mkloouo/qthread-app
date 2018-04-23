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

	void setRadius(int radius);
    void setBounds(const QRect &bounds);
    void setColor(int r, int g, int b);

public slots:
    void updateImage(QPointF pos);

signals:
	void updatedImage(QImage image);
    void boundsUpdated(QRect bounds);

private:
	QPointF pos_;
	QRect bounds_;
	QColor color_;
	int radius_;
	QImage image_;

};

#endif // BALLWIDGET_H
