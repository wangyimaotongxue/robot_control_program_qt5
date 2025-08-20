#include "MainWindow.hpp"
// #include "kuavo_rosbag.hpp"
#include <iostream>
#include <QFont>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QTextEdit>
#include <QProcess> 
#include <QInputDialog>

// 启动进程
void MainWindow::panelStartRobot() {
    QStringList items;
    items << "无 (不使用手柄)" << "BT2 手柄" << "BT2 Pro 手柄" << "H12 手柄";
    
    bool ok;
    QString item = QInputDialog::getItem(this, "选择手柄类型", 
                                       "请选择要使用的手柄类型:", 
                                       items, 0, false, &ok);
    
    if (!ok) {
        return; // 用户取消
    }
    
    QString joystickParam;
    if (item == "BT2 手柄") joystickParam = "bt2";
    else if (item == "BT2 Pro 手柄") joystickParam = "bt2pro";
    else if (item == "H12 手柄") joystickParam = "h12";
    

    // QString cmd = "bash";
    // QStringList args;
    // args << "-c"
    //     << "cd /home/cc/kuavo-ros-opensource/ && source ./devel/setup.bash && roslaunch humanoid_controllers load_kuavo_mujoco_sim.launch";

    // process->start(cmd, args);
    // if (!process->waitForStarted(3000)) {
    //     QMessageBox::critical(this, "错误", "启动失败，请检查路径或ROS环境。");
    // } else {
    //     QMessageBox::information(this, "完成", "机器人程序已启动！");
    // }
    terminal->sendText("clear\n");

    // 切换路径并启动 ROS
    terminal->sendText("cd /home/cc/kuavo-ros-opensource\n");
    terminal->sendText("source ./devel/setup.bash\n");
    terminal->sendText(QString("roslaunch humanoid_controllers load_kuavo_mujoco_sim.launch joystick:=%1\n").arg(joystickParam));

    std::cout << "完成启动" << std::endl;
    
}