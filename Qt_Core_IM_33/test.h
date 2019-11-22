#pragma once

#include <QObject>
#include <qdebug.h>
#include <qmap.h>
#include <qdatastream.h>

class test : public QObject
{
	Q_OBJECT

public:
	explicit test(QObject *parent = nullptr);
	~test();

	void fill();
	QString name();
	void setName(QString value);
	QMap<QString, QString> map();

	friend QDataStream& operator <<(QDataStream& stream, const test &t) {
		qInfo() << "Overload <<";
		stream << t.m_name;
		stream << t.m_map;
		return stream;
	}

	friend QDataStream& operator >>(QDataStream& stream, test& t) {
		qInfo() << "Overload >>";
		stream >> t.m_name;
		stream >> t.m_map;
		return stream;
	}

signals:

public slots:

private:
	QString m_name;
	QMap<QString, QString> m_map;
};
