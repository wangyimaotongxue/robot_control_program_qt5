#include "MainWindow.hpp"
#include "kuavo_rosbag.hpp"
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <pwd.h>
#include <QFont>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QTextEdit>
#include <QProcess> 
#include <QVBoxLayout>
// #include <QTermWidget>
#include <qtermwidget5/qtermwidget.h>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    process(new QProcess(this))     //初始化QProcess
{
    resize(1280, 720);  // 设置窗口大小
    setWindowTitle("Kuavo_Robot 控制面板");
    
    // 字体统一
    QFont btnFont("Microsoft YaHei", 10);
    QFont textFont("Courier New", 10);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    // 按钮行布局
    QHBoxLayout *btnLayout = new QHBoxLayout();
    // 创建按钮
    btnStartRobot = new QPushButton("启动机器人", this);
    // btnStartRobot->setGeometry(20, 20, 200, 40);
    btnLayout->addWidget(btnStartRobot);
    btnStartRobot->setFont(btnFont);

    btnVRControl = new QPushButton("VR控制", this);
    // btnVRControl->setGeometry(240, 20, 200, 40);
    btnLayout->addWidget(btnVRControl);
    btnVRControl->setFont(btnFont);

    btnStopRobot = new QPushButton("结束控制", this);
    // btnStopRobot->setGeometry(460, 20, 200, 40);
    btnLayout->addWidget(btnStopRobot);
    btnStopRobot->setFont(btnFont);

    btnResetZero = new QPushButton("关节零位标定", this);
    // btnResetZero->setGeometry(20, 80, 200, 40);
    btnLayout->addWidget(btnResetZero);
    btnResetZero->setFont(btnFont);

    btnExportLog = new QPushButton("导出日志", this);
    // btnExportLog->setGeometry(680, 20, 200, 40);
    btnLayout->addWidget(btnExportLog);
    btnExportLog->setFont(btnFont);

    btnExportRosbag = new QPushButton("导出Rosbag", this);
    // btnExportRosbag->setGeometry(900, 20, 200, 40);
    btnLayout->addWidget(btnExportRosbag);
    btnExportRosbag->setFont(btnFont);

    mainLayout->addLayout(btnLayout); // 把按钮行放到主布局

    // 创建终端控件
    // QTermWidget *terminal = new QTermWidget;
    // terminal->setShellProgram("/bin/bash");
    // terminal->setColorScheme("WhiteOnBlack");  // 终端配色
    // terminal->setScrollBarPosition(QTermWidget::ScrollBarRight);
    // layout->addWidget(terminal);
    // setLayout(layout);
    terminal = new QTermWidget();
    terminal->setShellProgram("/bin/bash");
    terminal->setColorScheme("WhiteOnBlack");
    terminal->setScrollBarPosition(QTermWidget::ScrollBarRight);
    mainLayout->addWidget(terminal, 1); // 占满剩余空间


    // 输出框
    textOutput = new QTextEdit(this);
    // textOutput->setGeometry(20, 140, 1320, 650);
    textOutput->setFont(textFont);
    textOutput->setReadOnly(true);

    // 设置高度为5行
    int rowHeight = QFontMetrics(textFont).lineSpacing();
    textOutput->setFixedHeight(rowHeight * 3 + 10); // +10 是上下边距

    QVBoxLayout *layout = new QVBoxLayout(this);
    // layout->addWidget(textOutput);
    mainLayout->addWidget(textOutput); // 这将使输出框位于底部
    setLayout(layout);

    // 信号连接
    connect(btnStartRobot, &QPushButton::clicked, this, &MainWindow::panelButtonClicked);
    connect(btnStopRobot, &QPushButton::clicked, this, &MainWindow::panelButtonClicked);
    connect(btnVRControl, &QPushButton::clicked, this, &MainWindow::panelButtonClicked);
    connect(btnResetZero, &QPushButton::clicked, this, &MainWindow::panelButtonClicked);
    connect(btnExportLog, &QPushButton::clicked, this, &MainWindow::panelButtonClicked);
    connect(btnExportRosbag, &QPushButton::clicked, this, &MainWindow::panelButtonClicked);
    // 输出流
    connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::panelOutput);
    connect(process, &QProcess::readyReadStandardError, this, &MainWindow::panelError);
}

MainWindow::~MainWindow()
{
    if(process && process->state() == QProcess::Running) {
        process->terminate();
        process->waitForFinished();
    }
    // 不需要手动删除process，因为设置了parent为this，QT会自动管理
}


// touch check
void MainWindow::panelButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString text = btn->text();
    textOutput->append(">>> [" + QTime::currentTime().toString() + "] 按下按钮: " + text);

    if (text == "启动机器人") {
        panelStartRobot();
        // terminal->sendText("\x03");
             
    } else if (text == "VR控制"){
        panelVRControl(); 
    } else if (text == "结束控制") {
        // terminal->sendText("\x03");
        panelStopRobot();

    } else if (text == "导出Rosbag") {
    qDebug() << "准备调用panelRosbag";
    qDebug() << "this is: " << this;
    panelRosbag();
    qDebug() << "panelRosbag调用完成";
    } else if (text == "关节零位标定"){
        panelResetZero();

    } else if (text == "3"){
        
    } else if (text == "3"){
        
    } else if (text == "3"){
        
    } else if (text == "3"){
        
    } else if (text == "3"){
        
    } else if (text == "3"){
        
    }

    // ...
}


// robot log output
void MainWindow::panelOutput() {
    QString output = process->readAllStandardOutput();
    textOutput->append(output);
}

void MainWindow::panelError() {
    QString error = process->readAllStandardError();
    textOutput->append("[错误] " + error);
}
