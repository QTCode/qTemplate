#pragma once
#include "VisualCoreExport.h"
#include <QObject>

class VisualTempletePrivate;
class VISUAL_VISUALCORE_EXPORT VisualTemplete : public QObject
{
	Q_OBJECT
public:
	VisualTemplete(QObject* parent = 0);
	~VisualTemplete();

public slots:

signals:

protected:
	QScopedPointer<VisualTempletePrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(VisualTemplete);
	Q_DISABLE_COPY(VisualTemplete);
};
