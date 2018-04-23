#ifndef BALLDB_H
#define BALLDB_H

#include <QObject>

class BallDb : public QObject
{
	Q_OBJECT
public:
	explicit BallDb(QString dbFile, QObject *parent = nullptr);

signals:

public slots:
};

#endif // BALLDB_H
