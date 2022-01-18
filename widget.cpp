#include "widget.h"
#include "ui_widget.h"

#include <windows.h>
#include <fstream>

#include <conio.h>

#include <QObject>
#include <QProcess>
#include <QMessageBox>
#include <iostream>

#define EXECDOSCMD "C:\\v3r\\visualsdk-build\\bin\\Release\\nnUNet.bat"
class WidgetPrivate: public Ui_Widget
{
	Q_DECLARE_PUBLIC(Widget);
protected:
	Widget* const q_ptr;

public:
	WidgetPrivate(Widget* object);
	~WidgetPrivate();
	QProcess* m_nnuNetProcess;
};

WidgetPrivate::WidgetPrivate(Widget* object)
	:q_ptr(object)
{
	
	//::system("start C:\\v3r\\visualsdk-build\\bin\\Release\\nnUNet.bat");
	//::WinExec
	//::system("start C:/Users/Visual/Anaconda3/Scripts/activate.bat & python C:/v3r/nnunet-pc/nnunet/inference/predict_simple.py -i C:/inferimages -o C:/infer/segs -t Task01_AcousticNeuroma -tr nnUNetTrainer -m 3d_fullres");
}


WidgetPrivate::~WidgetPrivate()
{

}

Widget::Widget(QWidget* parent)
	:QWidget(parent), d_ptr(new WidgetPrivate(this))
{
	Q_D(Widget);
	d->setupUi(this);
	// Init the process for docker interaction
	d->m_nnuNetProcess = new QProcess(this);
	QObject::connect(d->m_nnuNetProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(nnuNetOutput()));
	QObject::connect(d->m_nnuNetProcess, SIGNAL(readyReadStandardError()), this, SLOT(nnuNetError()));
	QObject::connect(d->m_nnuNetProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		[=](int exitCode, QProcess::ExitStatus exitStatus) { nnuNetCmdFinished(exitCode, exitStatus); });
	QObject::connect(d->testBtn, SIGNAL(clicked()), this, SLOT(startCmd()));

	//ExecDosCmd();
	//::system("start C:\\v3r\\visualsdk-build\\bin\\Release\\nnUNet.bat");
	//C:&&cd C:/v3r/tractseg-pc/bin&&SlicerPython.exe  bin/TractSeg.py -i examples/Diffusion.nii.gz --home /home/visual --raw_diffusion_inpu
	//::system("echo %PATH% && C:/Users/Visual/Anaconda3/Scripts/activate.bat && python C:/v3r/nnunet-pc/nnunet/inference/predict_simple.py  -i C:/infer/images -o C:/infer/segs -t Task01_AcousticNeuroma -tr nnUNetTrainer -m 3d_fullres");
	//::system("C:&&cd C:/v3r/tractseg-pc&&SlicerPython.exe  bin/TractSeg -i examples/Diffusion.nii.gz --home /home/visual --raw_diffusion_inpu");
	
}

Widget::~Widget()
{
	Q_D(Widget);
	if (d->m_nnuNetProcess)
	{
		d->m_nnuNetProcess->close();
		d->m_nnuNetProcess->waitForFinished();
	}

}

void Widget::nnuNetOutput()
{
	Q_D(Widget);
	std::string dockerinfo = d->m_nnuNetProcess->readAllStandardOutput().data();
	//d->dockerInfo->append(d->m_Process->readAllStandardOutput().data());
	std::cout << dockerinfo << std::endl;
}

void Widget::nnuNetError()
{
	Q_D(Widget);
	std::cout << d->m_nnuNetProcess->readAllStandardError().data() << std::endl;
	QMessageBox::information(0, "Error", d->m_nnuNetProcess->readAllStandardError().data());
}

void Widget::nnuNetCmdFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	//QStringList fileList;
	//if (QProcess::NormalExit == exitCode)
	//{
	//	VisualDirHelper::GetFileInfo(TRACTSEG_OUTPUT_DIR, fileList);
	//	emit tractSegFinished(fileList);
	//	QMessageBox::information(0, "Success", "docker process finished!");
	//}
	//else
	//{
	//	QMessageBox::information(0, "Failed", "docker process finished!");
	//}

}

void Widget::startCmd()
{
	Q_D(Widget);
	//QStringList cmdList;
	//cmdList.append("C:\\v3r\\visualsdk-build\\bin\\Release\\nnUNet.bat");
	//d->m_nnuNetProcess->start("cmd", cmdList);

	//C:&&cd C:/v3r/tractseg-pc&&SlicerPython.exe  bin/TractSeg -i examples/Diffusion.nii.gz --home /home/visual --raw_diffusion_inpu
	QStringList trkCmd;
	//trkCmd.append("C:");
	//trkCmd.append("&&");
	//trkCmd.append("cd C:/v3r/tractseg-pc");
	//trkCmd.append("&&");
	//trkCmd.append("SlicerPython.exe");
	trkCmd.append("bin/TractSeg");
	trkCmd.append("-i");
	trkCmd.append("examples/Diffusion.nii.gz");
	trkCmd.append("--home");
	trkCmd.append("/home/visual");
	trkCmd.append("--raw_diffusion_input");
	QString path = QApplication::applicationDirPath();
	QString dir = "C:/v3r/tractseg-pc";
	TCHAR chCurDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, chCurDir);
	SetCurrentDirectory(dir.toStdString().c_str());

	//d->m_nnuNetProcess->start("cmd", trkCmd);
	d->m_nnuNetProcess->start("SlicerPython.exe", trkCmd);
	SetCurrentDirectory(chCurDir);

}

bool Widget::ExecDosCmd()
{
	SECURITY_ATTRIBUTES   sa;
	::HANDLE   hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return   FALSE;
	}

	STARTUPINFO   si;
	PROCESS_INFORMATION   pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN 
	if (!CreateProcess(NULL, EXECDOSCMD
		, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		return   FALSE;
	}
	CloseHandle(hWrite);

	char   buffer[4096] = { 0 };
	DWORD   bytesRead;
	//ofstream outfile("log.txt");

	//while (true)
	//{
	//	if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
	//		break;
	//	//buffer中就是执行的结果，可以保存到文本，也可以直接输出 
	//	//printf(buffer); 
	//	outfile << buffer << std::endl;
	//	Sleep(200);
	//}

	//outfile.close();

	return   TRUE;
}

