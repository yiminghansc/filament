cmake_minimum_required(VERSION 3.19)
project(viewer)

set(TARGET viewer)
set(PUBLIC_HDR_DIR include)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
set(PUBLIC_HDRS
        include/viewer/AutomationEngine.h
        include/viewer/AutomationSpec.h
        include/viewer/RemoteServer.h
        include/viewer/Settings.h
        include/viewer/ViewerGui.h
)

set(SRCS
        src/jsonParseUtils.h
        src/AutomationEngine.cpp
        src/AutomationSpec.cpp
        src/RemoteServer.cpp
        src/Settings.cpp
        src/Settings_generated.cpp
        src/Settings_generated.h
        src/ViewerGui.cpp
)

# ==================================================================================================
# Include and target definitions
# ==================================================================================================
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})
if(HUNTER_ENABLED)
  target_link_libraries(${TARGET} PUBLIC imgui::imgui filament gltfio_core filagui jsmn::jsmn civetweb::civetweb-cpp)
else()
  target_link_libraries(${TARGET} PUBLIC imgui filament gltfio_core filagui jsmn civetweb)
endif()
if(HUNTER_ENABLED)
  target_include_directories(${TARGET} PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_HDR_DIR}>  
    $<INSTALL_INTERFACE:${PUBLIC_HDR_DIR}>)
else()
  target_include_directories(${TARGET} PUBLIC ${PUBLIC_HDR_DIR})
endif()
set_target_properties(${TARGET} PROPERTIES FOLDER Libs)

# ==================================================================================================
# Compiler flags
# ==================================================================================================
if (MSVC)
    target_compile_options(${TARGET} PRIVATE $<$<CONFIG:Release>:/fp:fast>)
else()
    target_compile_options(${TARGET} PRIVATE $<$<CONFIG:Release>:-ffast-math>)
    target_compile_options(${TARGET} PRIVATE -Wno-deprecated-register)
endif()

# ==================================================================================================
# Installation
# ==================================================================================================
if(HUNTER_ENABLED)
  install(TARGETS ${TARGET} EXPORT ${TARGETS_EXPORT_NAME} ARCHIVE DESTINATION lib/${DIST_DIR})
else()
  install(TARGETS ${TARGET} ARCHIVE DESTINATION lib/${DIST_DIR})
endif()
install(DIRECTORY ${PUBLIC_HDR_DIR}/viewer DESTINATION include)

# ==================================================================================================
# Tests
# ==================================================================================================
if (NOT ANDROID AND NOT WEBGL AND NOT IOS)
    add_executable(test_settings tests/test_settings.cpp)
    if(HUNTER_ENABLED)
      target_link_libraries(test_settings PRIVATE ${TARGET} GTest::gtest GTest::gtest_main)
    else()
      target_link_libraries(test_settings PRIVATE ${TARGET} gtest)
    endif()
    set_target_properties(test_settings PROPERTIES FOLDER Tests)
endif()
