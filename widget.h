#pragma once
#include <QWidget>

class WidgetPrivate;
class  Widget : public QWidget
{
	Q_OBJECT
public:
	Widget(QWidget* parent = 0);
	~Widget();

public slots:

signals:

protected:
	QScopedPointer<WidgetPrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(Widget);
	Q_DISABLE_COPY(Widget);
};