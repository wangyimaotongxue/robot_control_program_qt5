#include "MainWindow.hpp"
#include <iostream>
#include <QFont>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QTextEdit>
#include <QProcess> 
#include <QInputDialog>

// 启动进程
void MainWindow::panelResetZero() {
    QStringList items;
    items << "全身标定模式" << "仅上半身标定模式";
    
    bool ok;
    QString item = QInputDialog::getItem(this, "选择校准模式", 
                                       "请选择要使用的校准模式:", 
                                       items, 0, false, &ok);
    
    if (!ok) {
        return; // 用户取消
    }
    
    QString cali_arm = "false";
    QString cali_leg = "false";
    if (item == "全身标定模式") {
        cali_leg = "true";
        cali_arm = "true";
    }
    else if (item == "仅上半身标定模式"){
        cali_arm = "true";
    } 
    
    
    QString cmd = "bash";
    QStringList args;
    args << "-c"
        << QString("cd /home/cc/kuavo-ros-opensource/ && source ./devel/setup.bash && roslaunch humanoid_controllers load_kuavo_real.launch cali:=true"
            "cali:=true cali_arm:=%1 cali_leg:=%2").arg(cali_arm).arg(cali_leg);

    process->start(cmd, args);
    if (!process->waitForStarted(3000)) {
        QMessageBox::critical(this, "错误", "启动失败，请检查路径或ROS环境。");
    } else {
        QMessageBox::information(this, "完成", "关节标定程序打开完成！");
    }

    std::cout << "完成启动" << std::endl;
}