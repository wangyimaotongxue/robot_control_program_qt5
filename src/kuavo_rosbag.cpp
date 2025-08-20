#include "MainWindow.hpp"
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <pwd.h>
#include <QTime> 
#include <QDebug>
#include <QMessageBox>

namespace fs = std::filesystem;

void MainWindow::panelRosbag() {

    textOutput->append(">>> [" + QTime::currentTime().toString() + "] 正在导出Rosbag...");

    const char* homeDir = getenv("HOME");
    // if (!homeDir) {
    //     struct passwd* pw = getpwuid(getuid());
    //     homeDir = pw ? pw->pw_dir : nullptr;
    // }
    // if (!homeDir) {
    //     QMessageBox::warning(this, "警告", "无法获取家目录！");
    //     return;
    // }
    if (!homeDir) {

        struct passwd* pw = getpwuid(getuid());
    if (pw) {
        homeDir = pw->pw_dir;
    } else {
        std::cerr << "提示信息：无法获取家目录！" << std::endl;
        // QMessageBox::warning(this, "警告", "无法获取家目录！");
        return;
    }
    }

    std::string rosDir = std::string(homeDir) + "/.ros";
    std::vector<fs::directory_entry> bagFiles;
    std::vector<fs::path> result;

    try {
        for (const auto& entry : fs::directory_iterator(rosDir)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension();
                if (ext == ".bag" || ext == ".bag.active") {
                    bagFiles.push_back(entry);
                }
            }
        }

        std::sort(bagFiles.begin(), bagFiles.end(),
                  [](const fs::directory_entry& a, const fs::directory_entry& b) {
                      return a.last_write_time() > b.last_write_time();
                  });

        int maxFiles = std::min(3, static_cast<int>(bagFiles.size()));
        for (int i = 0; i < maxFiles; ++i) {
            result.push_back(bagFiles[i].path());
        }

        if (result.empty()) {
            QMessageBox::information(this, "提示", "未找到任何 .bag 或 .bag.active 文件。");
            return;
        }

        std::string destDir = "/home/cc/Documents/lejurobot_rosbags/";
        if (!fs::exists(destDir)) {
            fs::create_directories(destDir);
        }

        for (const auto& file : result) {
            fs::copy(file, fs::path(destDir) / file.filename(),
                     fs::copy_options::overwrite_existing);
        }

        textOutput->append(">>> [" + QTime::currentTime().toString() + "] Rosbag 导出完成...");
        QMessageBox::information(this, "完成", "rosbag导出成功！");
    } catch (const fs::filesystem_error& e) {
        QMessageBox::critical(this, "错误", QString("文件处理失败: ") + QString::fromStdString(e.what()));
    }

    qDebug() << "Rosbag 导出完成";
    
}
