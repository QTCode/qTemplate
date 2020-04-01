#include "widget.h"
#include "ui_widget.h"
#include <QObject>

class WidgetPrivate: public Ui_Widget
{
	Q_DECLARE_PUBLIC(Widget);
protected:
	Widget* const q_ptr;

public:
	WidgetPrivate(Widget* object);
	~WidgetPrivate();
};

WidgetPrivate::WidgetPrivate(Widget* object)
	:q_ptr(object)
{
	::system("ipconfig");
}

WidgetPrivate::~WidgetPrivate()
{

}

Widget::Widget(QWidget* parent)
	:QWidget(parent), d_ptr(new WidgetPrivate(this))
{
	Q_D(Widget);
	d->setupUi(this);

}

Widget::~Widget()
{
	Q_D(Widget);

}
