// Copyright (c) 2022 OUXT Polaris
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vrx_bridge/vrx_bridge_component.hpp>

namespace vrx_bridge
{
VRXBridgeComponent::VRXBridgeComponent(const rclcpp::NodeOptions & options)
: Node("vrx_bridge", options)
{
  gps_sub_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
    "/wamv/sensors/gps/gps/fix", 1,
    std::bind(&VRXBridgeComponent::GPStopic_callback, this, std::placeholders::_1));

  imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
    "/wamv/sensors/imu/imu/data", 1,
    std::bind(&VRXBridgeComponent::Imutopic_callback, this, std::placeholders::_1));

  // goal_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
  //   "/vrx/stationkeeping/goal", 1,
  //   std::bind(&VRXBridgeComponent::Goaltopic_callback, this, std::placeholders::_1));

  gps_pub_ =
    this->create_publisher<geographic_msgs::msg::GeoPoseStamped>("/localization/geopose", 1);
  imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("/imu", 1);
  goal_pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("/move_base_simple/goal", 1);
}

void VRXBridgeComponent::GPStopic_callback(const sensor_msgs::msg::NavSatFix::SharedPtr msg)
{
  geographic_msgs::msg::GeoPoseStamped gps;
  gps.header = msg->header;
  gps.pose.position.latitude = msg->latitude;
  gps.pose.position.longitude = msg->longitude;
  gps.pose.position.altitude = msg->altitude;

  gps_pub_->publish(gps);
}

void VRXBridgeComponent::Imutopic_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
  sensor_msgs::msg::Imu imu;
  imu.header = msg->header;
  imu.angular_velocity = msg->angular_velocity;
  imu.linear_acceleration = msg->linear_acceleration;
  imu_pub_->publish(imu);
}

// void VRXBridgeComponent::Goaltopic_callback(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
// {
//   geometry_msgs::msg::PoseStamped goal;
//   goal.header = msg->header;
//   goal.pose = msg->pose;
//   goal_pub_->publish(goal);
// }

}  // namespace vrx_bridge

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(vrx_bridge::VRXBridgeComponent)
