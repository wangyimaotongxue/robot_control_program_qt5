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
void MainWindow::panelVRControl() {
    
    bool ok;
    QString ipAddress = QInputDialog::getText(this, 
                                            "输入IP地址",
                                            "请输入有效的VR设备的IP地址:",
                                            QLineEdit::Normal,
                                            "192.168.31.01",  // 默认值
                                            &ok);
    
    if (!ok || ipAddress.isEmpty()) {
        return; // 用户取消输入
    }
    
    // 简单的IP地址格式验证
    QRegExp ipRegex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
    if (!ipRegex.exactMatch(ipAddress)) {
        QMessageBox::warning(this, "错误", "请输入有效的IP地址格式");
        return;
    }
    
    QString cmd = "bash";
    QStringList args;
    args << "-c"
        << QString("cd /home/cc/kuavo-ros-opensource/ && source ./devel/setup.bash && roslaunch noitom_hi5_hand_udp_python launch_quest3_ik.launch ip_address:=%1").arg(ipAddress);

    process->start(cmd, args);
    if (!process->waitForStarted(3000)) {
        QMessageBox::critical(this, "错误", "启动失败，请检查您的VR设备是否存在于同一局域网内。");
    } else {
        QMessageBox::information(this, "完成", QString("VR设备启动完成 (IP: %1)").arg(ipAddress));
    }

    std::cout << "完成启动" << std::endl;
}