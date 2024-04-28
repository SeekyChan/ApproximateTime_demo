#include "ros/ros.h"
#include "std_msgs/Header.h"
#include <sensor_msgs/PointCloud2.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


void callback(const sensor_msgs::PointCloud2::ConstPtr& msg1, const sensor_msgs::PointCloud2::ConstPtr& msg2) {


    // 打印消息的时间戳
    ROS_INFO("Received timestamps: topic1: %f, topic2: %f", msg1->header.stamp.toSec(), msg2->header.stamp.toSec());

    // 计算时间戳的差值（绝对值）
    double timestamp_diff = fabs(msg1->header.stamp.toSec() - msg2->header.stamp.toSec());

    ROS_INFO("Timestamp difference: %f seconds ,node_1 seq : %d , node_1 seq : %d", timestamp_diff,msg1->header.seq,msg2->header.seq);
}

int main(int argc, char **argv) {
    // 初始化 ROS 节点
    ros::init(argc, argv, "timestamp_sync_node");

    // 创建节点句柄
    ros::NodeHandle nh;


    //订阅两个话题
    message_filters::Subscriber<sensor_msgs::PointCloud2> sub1(nh, "timestamp_01_topic", 5);
    message_filters::Subscriber<sensor_msgs::PointCloud2> sub2(nh, "timestamp_02_topic", 5);
 
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2,sensor_msgs::PointCloud2> syncPolicy; //近似同步策略
    message_filters::Synchronizer<syncPolicy> sync(syncPolicy(10), sub1, sub2);// 同步
    
    sync.registerCallback(boost::bind(&callback, _1, _2));


    // 循环等待回调
    ros::spin();

    return 0;
}
