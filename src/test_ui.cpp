#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

class GreetingApp : public QWidget {
public:
    GreetingApp(QWidget *parent = nullptr) : QWidget(parent) {
        // 创建按钮
        QPushButton *greetButton = new QPushButton("打招呼", this);
        
        // 设置按钮点击信号与槽连接
        connect(greetButton, &QPushButton::clicked, this, &GreetingApp::printGreeting);
        
        // 设置布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(greetButton);
        
        // 设置窗口标题和大小
        setWindowTitle("roslaunch");
        resize(300, 200);
    }

private slots:
    void printGreeting() {
        QString command = "bash";
        QStringList args;
        args << "-c" << "cd /home/cc/kuavo-ros-opensource && source ./devel/setup.bash && roslaunch humanoid_controllers load_kuavo_real.launch";
        // qDebug() << "你好";
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    GreetingApp window;
    window.show();
    
    return app.exec();
}