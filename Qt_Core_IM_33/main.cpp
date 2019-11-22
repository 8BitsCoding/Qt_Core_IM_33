#include <QtCore/QCoreApplication>

#include <qdatastream.h>
#include <qdebug.h>
#include <qdir.h>
#include <qfile.h>
#include "test.h"

bool saveFile(test* t, QString path) {
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly)) return false;

	QDataStream ds(&file);
	ds.setVersion(QDataStream::Qt_5_9);
	ds << *t;
	/*
	ds << t->name();
	ds << t->map();
	// 동일하게 동작
	// 하지만 순서에 주의해야한다.
	// 차라리 ds << *t쓰는게 맘편함.
	*/

	file.close();

	return true;
}

bool loadFile(QString path) {
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly)) return false;

	QDataStream ds(&file);
	test t;
	ds >> t;

	file.close();
	qInfo() << "Name: " << t.name();
	foreach(QString key, t.map().keys()) {
		qInfo() << key << " :" << t.map().value(key);
	}
	return true;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString path = "test.txt";

	test t;
	t.fill();

	if (saveFile(&t, path)) {
		qInfo() << "Save!!";
		loadFile(path);
	}

	return a.exec();
}
