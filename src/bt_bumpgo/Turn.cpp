#include <string>
#include <iostream>
#include "src/bt_bumpgo/include/bt_bumpgo/Turn.hpp"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace bt_bumpgo
{
using namespace std::chrono_literals;

Turn::Turn(const std::string & xml_tag_name, const BT::NodeConfiguration & conf) : BT::ActionNodeBase(xml_tag_name, conf)
{
    config().blackboard->get("node", node_);

    vel_pub_ = node_->create_publisher<geometry_msgs::msg::Twist>("/output_vel", 100);
}

void
Turn::halt()
{
}

BT::NodeStatus
Turn::tick()
{   
    if(status() == BT::NodeStatus::IDLE)
    {
        start_time_ = node_->now();
    }

    geometry_msgs::msg::Twist vel_msgs;
    vel_msgs.linear.z = 0.5;
    vel_pub_->publish(vel_msgs);

    auto elasped = node_->now() - start_time_;

    if(elasped < 3s)
    {
        return BT::NodeStatus::RUNNING;
    }
    else
    {
        return BT::NodeStatus::SUCCESS;
    }
}

}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
    factory.registerNodeType<bt_bumpgo::Turn>("Turn");
}