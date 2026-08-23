cmake_minimum_required(VERSION 3.8)
project(argus_core)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/NeuralFrame.msg"
)

install(DIRECTORY include/ DESTINATION include)

ament_export_include_directories(include)
ament_export_dependencies(rosidl_default_runtime)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)

  # argus_wire.h is the vendored ABI contract. Its formatting is shared with
  # bare-metal copies uncrustify never sees, so reformatting here would force
  # a re-vendor for cosmetic reasons and put the copies out off sync.
  set(AMENT_LINT_AUTO_FILE_EXCLUDE include/argus_core/argus_wire.h)

  ament_lint_auto_find_test_dependencies()

  # Compile argus_wire.h as C11, the way the bare-metal PS consumes it.
  # Build failure here is the intent; the static_asserts are the test.
  add_library(argus_wire_c_check OBJECT test/wire_c_check.c)
  set_target_properties(argus_wire_c_check PROPERTIES
    C_STANDARD 11 C_STANDARD_REQUIRED ON)
  target_include_directories(argus_wire_c_check PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_wire_contract test/test_wire_contract.cpp)
  target_include_directories(test_wire_contract PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
  rosidl_get_typesupport_target(cpp_typesupport_target
    ${PROJECT_NAME} rosidl_typesupport_cpp)
  target_link_libraries(test_wire_contract "${cpp_typesupport_target}")
endif()
ament_package()
