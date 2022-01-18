#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* ³õÊ¼»¯Action²Ëµ¥ */
    QMenu* actionMenu = new QMenu("Action");
    QAction* leftAction = new QAction("Left", this);
    QAction* rightAction = new QAction("Right", this);
    QAction* centerAction = new QAction("Center", this);
    QAction* justifyAction = new QAction("Justify", this);
    QActionGroup* actionGroup = new QActionGroup(this);
    actionMenu->addAction(actionGroup->addAction(leftAction));
    actionMenu->addAction(actionGroup->addAction(rightAction));
    actionMenu->addAction(actionGroup->addAction(centerAction));
    actionMenu->addAction(actionGroup->addAction(justifyAction));
 
    ui->menubar->addMenu(actionMenu);

    QAction* leftAlignAct = new QAction("leftAlignAct", this);
    QAction* rightAlignAct = new QAction("rightAlignAct", this);
    QAction* justifyAct = new QAction("justifyAct", this);
    QAction* centerAct = new QAction("centerAct", this);

    QActionGroup* alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
    ui->menubar->addActions(alignmentGroup->actions());

}

MainWindow::~MainWindow()
{
    delete ui;
}

