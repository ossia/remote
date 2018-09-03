cmake_minimum_required(VERSION 3.11)
project(score_remote LANGUAGES CXX)

find_package(Qt5 5.10 COMPONENTS Core Widgets Qml)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(OSSIA_PROTOCOL_MIDI 0 CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_MINUIT 0 CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_OSC 0 CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_HTTP 0 CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_SERIAL 0 CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_WS 0 CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_AUDIO 0 CACHE "" INTERNAL)

set(OSSIA_EDITOR 0 CACHE "" INTERNAL)
set(OSSIA_DATAFLOW 0 CACHE "" INTERNAL)

set(OSSIA_QT 1 CACHE "" INTERNAL)
set(OSSIA_QML_DEVICE 0 CACHE "" INTERNAL)
set(OSSIA_QML_SCORE 0 CACHE "" INTERNAL)

add_subdirectory(score/API)

set(SRCS
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/CentralItemModel.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/NodeModel.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/WidgetListModel.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/WidgetAddressSetup.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/GUIItem.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/RemoteApplication.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/RemoteContext.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/WidgetKind.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/ZeroconfListener.hpp"

"${CMAKE_CURRENT_SOURCE_DIR}/remote/main.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/CentralItemModel.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/NodeModel.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/WidgetListModel.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/Models/GUIItem.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/RemoteApplication.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/remote/ZeroconfListener.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/score/base/lib/score/serialization/StringConstants.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-device/Device/Address/AddressSettings.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-device/Device/Node/DeviceNode.cpp"

"${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state/State/Domain.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state/State/Value.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state/State/ValueConversion.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state/State/Address.cpp"
)

qt5_add_resources(QRCS "${CMAKE_CURRENT_SOURCE_DIR}/remote/qml.qrc")
add_executable(score_remote_ui WIN32
  ${SRCS} ${QRCS}
)

target_compile_features(score_remote_ui
  PRIVATE
    cxx_std_17
)

target_link_libraries(score_remote_ui
  PRIVATE
    ossia
    Qt5::Core Qt5::Widgets Qt5::Qml
    Servus_iface
)

target_include_directories(score_remote_ui
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/remote"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-device"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-device"
    )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_lib_base_export.h" "#pragma once\n#define SCORE_LIB_BASE_EXPORT")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_lib_state_export.h" "#pragma once\n#define SCORE_LIB_STATE_EXPORT")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_lib_device_export.h" "#pragma once\n#define SCORE_LIB_DEVICE_EXPORT")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_compiler_detection.hpp" "#pragma once")

if(DEPLOYMENT_BUILD)
  set_target_properties(score_remote_ui PROPERTIES MACOSX_BUNDLE TRUE)
endif()

install(
  TARGETS score_remote_ui
  BUNDLE DESTINATION .
  RUNTIME DESTINATION bin)
