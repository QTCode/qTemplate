#pragma once
#include <QObject>

class qMyTemplatePrivate;
class  qMyTemplate : public QObject
{
	Q_OBJECT
public:
	qMyTemplate(QObject* parent = 0);
	~qMyTemplate();

public slots:

signals:

protected:
	QScopedPointer<qMyTemplatePrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(qMyTemplate);
	Q_DISABLE_COPY(qMyTemplate);
};
