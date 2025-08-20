#include "MainWindow.hpp"
#include <iostream>
#include <QFont>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QTextEdit>
#include <QProcess> 


// 清理进程
// void MainWindow::panelStopRobot() {

//     if (process->state() == QProcess::Running) {
//         process->terminate(); // 发送 SIGTERM 信号 (类 Unix) 或 WM_CLOSE (Windows)
//         // 通常会给进程一点时间来清理
//         textOutput->append ("[INFO] 正在清理");
//         if (!process->waitForFinished(10000)) { // 等待3秒
//             textOutput->append("[WARNING] 清理超时，正在强制杀死进程...");
//             // 3秒内没有结束，强制杀死
//             process->kill(); // 发送 SIGKILL 信号 (类 Unix) 或 TerminateProcess (Windows)
//             process->waitForFinished(1000); // 再等待1秒确保结束
//             QMessageBox::critical(this, "完成", "机器人进程已清理");
//         }else
//         {
//             QMessageBox::critical(this, "错误", "清理失败，请打开任意终端执行“pkill ros”继续完成进程释放。");
//         }
        
//         textOutput->append("[INFO] 机器人进程已停止。");

//         std::cout << "清理完成" << std::endl;
//     }
// }

void MainWindow::panelStopRobot() {
    if (process->state() == QProcess::Running) {
        textOutput->append("[INFO] 正在停止机器人进程...");
        
        // 通过终端发送Ctrl+C
        terminal->sendText("\x03\n");  // Ctrl+C
        // terminal->sendText("exit\n");  // 退出终端
        
        // 等待进程结束
        if (process->waitForFinished(3000)) {
            textOutput->append("[INFO] 机器人进程已通过终端停止");
            QMessageBox::information(this, "完成", "机器人进程已停止");
            return;
        }
        
        // 如果终端方式失败，回退到程序化终止
        process->terminate();
        if (process->waitForFinished(1000)) {
            textOutput->append("[INFO] 机器人进程已停止");
            return;
        }
        
        process->kill();
        if (!process->waitForFinished(1000)) {
            textOutput->append("[ERROR] 无法停止进程，请手动终止");
            QMessageBox::critical(this, "错误", 
                "无法停止进程，请尝试以下方法:\n"
                "1. 在终端中执行: pkill roslaunch\n"
                "2. 或者执行: pkill -f kuavo");
        }
    } else {
        textOutput->append("[INFO] 没有运行的机器人进程需要停止");
    }
}