#pragma once
#include <QWidget>
#include <QProcess>

class WidgetPrivate;
class  Widget : public QWidget
{
	Q_OBJECT
public:
	Widget(QWidget* parent = 0);
	~Widget();

protected slots:

	void nnuNetOutput();
	void nnuNetError();
	void nnuNetCmdFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void startCmd();

	bool ExecDosCmd();

signals:

protected:
	QScopedPointer<WidgetPrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(Widget);
	Q_DISABLE_COPY(Widget);
};