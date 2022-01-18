#pragma once
#include <QWidget>

class qMyTemplateWidgetPrivate;
class  qMyTemplateWidget : public QWidget
{
	Q_OBJECT
public:
	qMyTemplateWidget(QWidget* parent = 0);
	~qMyTemplateWidget();

public slots:

signals:

protected:
	QScopedPointer<qMyTemplateWidgetPrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(qMyTemplateWidget);
	Q_DISABLE_COPY(qMyTemplateWidget);
};
