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

#ifndef VRX_BRIDGE_COMPONENT_HPP_
#define VRX_BRIDGE_COMPONENT_HPP_

#if __cplusplus
extern "C" {
#endif

// The below macros are taken from https://gcc.gnu.org/wiki/Visibility and from
// demos/composition/include/composition/visibility_control.h at https://github.com/ros2/demos
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define VRX_BRIDGE_COMPONENT_EXPORT \
  __attribute__((dllexport))
#define VRX_BRIDGE_COMPONENT_IMPORT \
  __attribute__((dllimport))
#else
#define VRX_BRIDGE_COMPONENT_EXPORT \
  __declspec(dllexport)
#define VRX_BRIDGE_COMPONENT_IMPORT \
  __declspec(dllimport)
#endif
#ifdef VRX_BRIDGE_COMPONENT_BUILDING_DLL
#define VRX_BRIDGE_COMPONENT_PUBLIC \
  VRX_BRIDGE_COMPONENT_EXPORT
#else
#define VRX_BRIDGE_COMPONENT_PUBLIC \
  VRX_BRIDGE_COMPONENT_IMPORT
#endif
#define VRX_BRIDGE_COMPONENT_PUBLIC_TYPE \
  VRX_BRIDGE_COMPONENT_PUBLIC
#define VRX_BRIDGE_COMPONENT_LOCAL
#else
#define VRX_BRIDGE_COMPONENT_EXPORT \
  __attribute__((visibility("default")))
#define VRX_BRIDGE_COMPONENT_IMPORT
#if __GNUC__ >= 4
#define VRX_BRIDGE_COMPONENT_PUBLIC \
  __attribute__((visibility("default")))
#define VRX_BRIDGE_COMPONENT_LOCAL \
  __attribute__((visibility("hidden")))
#else
#define VRX_BRIDGE_COMPONENT_PUBLIC
#define VRX_BRIDGE_COMPONENT_LOCAL
#endif
#define VRX_BRIDGE_COMPONENT_PUBLIC_TYPE
#endif
#if __cplusplus
}  // extern "C"
#endif

#include <geographic_msgs/msg/geo_pose_stamped.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <rclcpp/rclcpp.hpp>


namespace vrx_bridge
{
class VRXBridgeComponent : public rclcpp::Node
{
public:
  VRX_BRIDGE_COMPONENT_PUBLIC
  VRXBridgeComponent(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;

  rclcpp::Publisher<geographic_msgs::msg::GeoPoseStamped>::SharedPtr gps_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;

  void GPStopic_callback(const sensor_msgs::msg::NavSatFix::SharedPtr msg);
  void Imutopic_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
};
}  // namespace vrx_bridge

#endif  // VRX_BRIDGE_COMPONENT_HPP_
