#include <lidar_scan.hpp>


int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PointCloudSaver>());
    rclcpp::shutdown();
    return 0;
}