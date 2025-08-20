#ifndef KUAVO_REAL_HPP
#define KUAVO_REAL_HPP

#include <QWidget>
#include <QPushButton>
#include <QProcess>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QMessageBox>



class KuavoReal : public QWidget {
    Q_OBJECT

public:
    KuavoReal(QWidget *parent = nullptr);
    ~KuavoReal();

private slots:
    void launchRobot();      // 启动机器人
    void stopRobot();       // 清理ROS进程
    void handleOutput();    // 捕获标准输出
    void handleError();     // 捕获标准错误

private:
    QPushButton *launchButton;      // 启动机器人按钮
    QPushButton *stopButton;     // 清理ROS进程按钮
    QPlainTextEdit *outputArea;   // 输出窗口
    
    QProcess *process;
};


#endif
