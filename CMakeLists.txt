cmake_minimum_required(VERSION 3.11)
project(remote LANGUAGES CXX)

## Settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if(APPLE)
  #set(CMAKE_INSTALL_NAME_DIR @rpath)
  #set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
  #set(CMAKE_INSTALL_RPATH "@loader_path/../Frameworks;@executable_path;")
endif()

## Metadata
set(CPACK_PACKAGE_NAME "ossia remote")
set(CPACK_PACKAGE_VENDOR "ossia")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ossia remote, a remote for OSCQuery devices")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "remote")

## Dependenices
find_package(Qt5 5.10 COMPONENTS Core Widgets Qml)

set(OSSIA_NO_INSTALL ON CACHE INTERNAL "" FORCE)
set(OSSIA_DISABLE_QT_PLUGIN ON CACHE INTERNAL "" FORCE)
set(OSSIA_STATIC ON CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_MIDI OFF CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_MINUIT OFF CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_OSC OFF CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_HTTP OFF CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_SERIAL OFF CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_WEBSOCKETS OFF CACHE "" INTERNAL)
set(OSSIA_PROTOCOL_AUDIO OFF CACHE "" INTERNAL)

set(OSSIA_EDITOR OFF CACHE "" INTERNAL)
set(OSSIA_DATAFLOW OFF CACHE "" INTERNAL)

set(OSSIA_QT ON CACHE "" INTERNAL)
set(OSSIA_QML_DEVICE OFF CACHE "" INTERNAL)
set(OSSIA_QML_SCORE OFF CACHE "" INTERNAL)

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

"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/graph.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/creativecontrolsplugin.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/angleslider.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/scope.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/cpputils.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/xytarget.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/polygon.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/toucharea.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/painted_polygon.hpp"

"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/graph.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/creativecontrolsplugin.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/angleslider.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/scope.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/cpputils.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/xytarget.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/polygon.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/toucharea.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src/painted_polygon.cpp"

)

qt5_add_resources(QRCS "${CMAKE_CURRENT_SOURCE_DIR}/remote/qml.qrc"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/com_github_jcelerier_qml-creative-controls.qrc")
add_executable(remote WIN32
  ${SRCS} ${QRCS}
)

set_target_properties(remote
  PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1

    OUTPUT_NAME "ossia-remote"

    MACOSX_BUNDLE FALSE
    MACOSX_BUNDLE_INFO_STRING "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}"
    MACOSX_BUNDLE_GUI_IDENTIFIER "org.ossia.remote"
    MACOSX_BUNDLE_LONG_VERSION_STRING "${CPACK_PACKAGE_VERSION}"
    MACOSX_BUNDLE_BUNDLE_NAME "ossia remote"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${CPACK_PACKAGE_VERSION}"
    MACOSX_BUNDLE_BUNDLE_VERSION "${CPACK_PACKAGE_VERSION}"
    MACOSX_BUNDLE_COPYRIGHT "https://ossia.io"
#    MACOSX_BUNDLE_ICON_FILE "score.icns"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist.in"
    )

target_compile_features(remote
  PRIVATE
    cxx_std_17
)

target_link_libraries(remote
  PRIVATE
    ossia
    Qt5::Core Qt5::Widgets Qt5::Qml
    Servus_iface
)

target_include_directories(remote
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/remote"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-device"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-state"
    "${CMAKE_CURRENT_SOURCE_DIR}/score/base/plugins/score-lib-device"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qml-creative-controls/src"
    )

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/score_lib_base_export.h")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_lib_base_export.h" "#pragma once\n#define SCORE_LIB_BASE_EXPORT")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_lib_state_export.h" "#pragma once\n#define SCORE_LIB_STATE_EXPORT")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_lib_device_export.h" "#pragma once\n#define SCORE_LIB_DEVICE_EXPORT")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/score_compiler_detection.hpp" "#pragma once")
endif()

install(
  TARGETS remote
  BUNDLE DESTINATION .
  RUNTIME DESTINATION bin)

if(APPLE)
    set(MACDEPLOYQT_EXE "${_qt5_root_dir}/../../bin/macdeployqt")
    install(CODE "
      execute_process(COMMAND ${MACDEPLOYQT_EXE} \"\${CMAKE_INSTALL_PREFIX}/remote.app\" -qmldir=${CMAKE_CURRENT_SOURCE_DIR}/remote/qml)
    ")
    set(CPACK_GENERATOR "DragNDrop")
endif()

include(CPack)
