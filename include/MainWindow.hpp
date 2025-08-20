#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>      
#include <QMessageBox>
#include <qtermwidget5/qtermwidget.h>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 声明你要实现的槽函数
    void panelButtonClicked();
    void panelStartRobot();  
    void panelVRControl();
    void panelStopRobot(); 
    void panelRosbag();
    void panelResetZero();
    
    
    

    void panelError();
    void panelOutput();

private:
    QProcess *process;
    QTextEdit *textOutput;

    QPushButton *btnStartRobot;
    QPushButton *btnStopRobot;
    QPushButton *btnVRControl;
    QPushButton *btnExportLog;
    QPushButton *btnExportRosbag;
    QPushButton *btnResetZero;
    
    QTermWidget *terminal;

    // ... 你可以继续添加更多按钮
};

#endif // MAINWINDOW_H
