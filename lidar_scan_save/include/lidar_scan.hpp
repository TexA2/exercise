#include <iostream>
#include "rclcpp/rclcpp.hpp"

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/pcl_config.h> 


#include <sensor_msgs/msg/point_cloud2.hpp>

class PointCloudSaver : public rclcpp::Node
{
public:
    PointCloudSaver() : Node("CloudSaverSub")
    {

    cloud_sub = this->create_subscription<sensor_msgs::msg::PointCloud2>(
    "/lidar_top/points", rclcpp::QoS{1} , std::bind(&PointCloudSaver::callbackCloud, this, std::placeholders::_1));

    }

private:

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr  cloud_sub;
    void callbackCloud(const sensor_msgs::msg::PointCloud2::ConstSharedPtr cloud_msg_ptr);

};


void PointCloudSaver::callbackCloud(const sensor_msgs::msg::PointCloud2::ConstSharedPtr cloud_msg_ptr)
{
    //принимаем облако и сохраняем ее сканы отдельно друг от друга

    //доработать сделать путь!
   // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

     pcl::PointCloud<pcl::PointXYZI> cloud;

     pcl::fromROSMsg(*cloud_msg_ptr, cloud);

    static int count_cloud = 0;

    std::string filename = "pointcloud_" + std::to_string(count_cloud) + ".pcd";

    ++count_cloud;

    // Сохраняем в бинарном формате PCD
    if (pcl::io::savePCDFileBinary(filename, cloud) == 0)
    {
      RCLCPP_INFO(this->get_logger(), "Saved pointcloud to %s", filename.c_str());
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to save pointcloud to %s", filename.c_str());
    }
}
