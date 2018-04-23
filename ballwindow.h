#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QImage>

#include "ballcontroller.h"

namespace Ui {
	class BallWindow;
}

class BallWindow : public QWidget
{
	Q_OBJECT

public:
	explicit BallWindow(QWidget *parent = 0);
	~BallWindow();

protected:
	void changeEvent(QEvent *e);

protected slots:
	void updateLabel(QImage picture);

signals:
	void updated();

private:
	Ui::BallWindow *ui;
	BallController controller_;

};

#endif // MAINWINDOW_H
