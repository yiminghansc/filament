cmake_minimum_required(VERSION 3.19)
project(camutils)

set(TARGET camutils)
set(PUBLIC_HDR_DIR include)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
set(PUBLIC_HDRS
        include/camutils/Bookmark.h
        include/camutils/compiler.h
        include/camutils/Manipulator.h
)

set(SRCS
        src/Bookmark.cpp
        src/FreeFlightManipulator.h
        src/Manipulator.cpp
        src/MapManipulator.h
        src/OrbitManipulator.h
)

# ==================================================================================================
# Include and target definitions
# ==================================================================================================
include_directories(${PUBLIC_HDR_DIR})

add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})

target_link_libraries(${TARGET} PUBLIC math)

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
install(DIRECTORY ${PUBLIC_HDR_DIR}/camutils DESTINATION include)

# ==================================================================================================
# Tests
# ==================================================================================================
if (NOT ANDROID AND NOT WEBGL AND NOT IOS)
    add_executable(test_${TARGET} tests/test_camutils.cpp)
    if(HUNTER_ENABLED)
      target_link_libraries(test_${TARGET} PRIVATE camutils GTest::gtest GTest::gtest_main Threads::Threads)
    else()
      target_link_libraries(test_${TARGET} PRIVATE camutils gtest)
    endif()
    set_target_properties(test_${TARGET} PROPERTIES FOLDER Tests)
endif()
