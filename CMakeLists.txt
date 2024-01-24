cmake_minimum_required(VERSION 3.8)
project(vrx_bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(vrx_bridge_component SHARED
  src/vrx_bridge_component.cpp
)
target_compile_definitions(vrx_bridge_component
  PRIVATE "VRX_BRIDGE_COMPONENT_BUILDING_DLL")
rclcpp_components_register_nodes(vrx_bridge_component
  "vrx_bridge::VRXBridgeComponent")

ament_auto_add_executable(vrx_bridge_node
  src/vrx_bridge_node.cpp
)
target_link_libraries(vrx_bridge_node
  vrx_bridge_component
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
