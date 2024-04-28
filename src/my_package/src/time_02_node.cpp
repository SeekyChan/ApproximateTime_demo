#include "ros/ros.h"
#include "std_msgs/Header.h"
#include <sensor_msgs/PointCloud2.h>
#include <ctime>

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "timestamp_publisher");

    // 创建节点句柄
    ros::NodeHandle n;


    ros::Publisher pub = n.advertise<sensor_msgs::PointCloud2>("timestamp_02_topic", 10);

    // 设置发布频率，这里设定为每秒1次
    ros::Rate loop_rate(1);

    int count = 0;
    while (ros::ok())
    {
        // 获取当前系统时间戳

        sensor_msgs::PointCloud2 cloud_msg;

        // 设置消息的元数据
        cloud_msg.header.frame_id = "time_02_node"; 
        cloud_msg.header.stamp = ros::Time::now(); // 设置时间戳
        cloud_msg.header.seq = count;


        // 发布消息
        pub.publish(cloud_msg);

        // 输出当前时间戳
        //ROS_INFO("time_02_node publishing timestamp: %f", cloud_msg.header.stamp.toSec());

        // 递增count值
        count++;

        // 延时以达到指定的发布频率
        loop_rate.sleep();
    }

    return 0;
}
