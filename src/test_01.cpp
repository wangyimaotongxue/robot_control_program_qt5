#include <unistd.h>  // for execl
#include <iostream>
#include <cstdlib>   // for exit

int main() {
    std::cout << "Starting ZMP_walking script..." << std::endl;

    // 调用 execl 执行 /bin/bash 运行脚本
    execl("/bin/bash", 
          "bash", "-c", // 注意：这里应该是 argv[0]，通常用 "bash" 或脚本名
          "cd /home/cc/kuavo-ros-opensource/ && source ./devel/setup.bash && roslaunch humanoid_controllers load_kuavo_real.launch", 
          (char*)NULL);

    // 如果 execl 执行失败，会继续执行到这里
    std::cerr << "Failed to execute script!" << std::endl;
    return 1;
}