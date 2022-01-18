#include "qMyTemplateWidget.h"
#include "ui_qMyTemplateWidget.h"



class qMyTemplateWidgetPrivate: public Ui_qMyTemplateWidget
{
	Q_DECLARE_PUBLIC(qMyTemplateWidget);
protected:
	qMyTemplateWidget* const q_ptr;

public:
	qMyTemplateWidgetPrivate(qMyTemplateWidget& object);
	~qMyTemplateWidgetPrivate();
};

qMyTemplateWidgetPrivate::qMyTemplateWidgetPrivate(qMyTemplateWidget& object)
	:q_ptr(&object)
{

}

qMyTemplateWidgetPrivate::~qMyTemplateWidgetPrivate()
{

}

qMyTemplateWidget::qMyTemplateWidget(QWidget* parent)
	:QWidget(parent), d_ptr(new qMyTemplateWidgetPrivate(*this))
{
	Q_D(qMyTemplateWidget);

}

qMyTemplateWidget::~qMyTemplateWidget()
{
	Q_D(qMyTemplateWidget);

}
