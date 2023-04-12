#include <string>
#include <iostream>
#include "src/bt_bumpgo/include/bt_bumpgo/Forward.hpp"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace bt_bumpgo
{
using namespace std::chrono_literals;

Forward::Forward(const std::string & xml_tag_name, const BT::NodeConfiguration & conf) : BT::ActionNodeBase(xml_tag_name, conf)
{
    config().blackboard->get("node", node_);

    vel_pub_ = node_->create_publisher<geometry_msgs::msg::Twist>("/output_vel", 100);
}
BT::NodeStatus
Forward::tick()
{
    geometry_msgs::msg::Twist vel_msgs;
    vel_msgs.linear.x = 0.3;
    vel_pub_->publish(vel_msgs);

    return BT::NodeStatus::RUNNING;
}
}

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
    factory.registerNodeType<bt_bumpgo::Forward>("Forward");
}