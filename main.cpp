#include <QApplication>

#include "ballwindow.h"
#include "ballcontroller.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BallWindow w;
	w.show();

	return a.exec();
}
