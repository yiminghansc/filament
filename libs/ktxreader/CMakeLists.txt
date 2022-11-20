cmake_minimum_required(VERSION 3.19)
project(ktxreader)

set(TARGET ktxreader)
set(PUBLIC_HDR_DIR include)

# ==================================================================================================
# Sources and headers
# ==================================================================================================
set(PUBLIC_HDRS
        include/ktxreader/Ktx1Reader.h
        include/ktxreader/Ktx2Reader.h
)

set(SRCS
        src/Ktx1Reader.cpp
        src/Ktx2Reader.cpp
)

# ==================================================================================================
# Include and target definitions
# ==================================================================================================
include_directories(${PUBLIC_HDR_DIR})

add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})

if(HUNTER_ENABLED)
  target_link_libraries(${TARGET} PUBLIC utils image filament basis_universal::basisu_transcoder)
else()
  target_link_libraries(${TARGET} PUBLIC utils image filament basis_transcoder)
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
install(DIRECTORY ${PUBLIC_HDR_DIR}/${TARGET} DESTINATION include)

# ==================================================================================================
# Tests
# ==================================================================================================

function(add_testfile filename)
    set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/tests/${filename}")
    set(target_path "${PROJECT_BINARY_DIR}/${filename}")
    set(TESTFILES ${TESTFILES} ${target_path} PARENT_SCOPE)
    add_custom_command(
        OUTPUT ${target_path}
        COMMAND ${CMAKE_COMMAND} -E copy ${source_path} ${target_path}
        MAIN_DEPENDENCY ${source_path})
endfunction()

add_testfile(color_grid_uastc_zstd.ktx2)
add_testfile(lightroom_ibl.ktx)

if (NOT ANDROID AND NOT WEBGL AND NOT IOS)
    add_executable(test_ktxreader tests/test_ktxreader.cpp ${TESTFILES})
    if(HUNTER_ENABLED)
      target_link_libraries(test_ktxreader PRIVATE ${TARGET} GTest::gtest GTest::gtest_main Threads::Threads)
    else()
      target_link_libraries(test_ktxreader PRIVATE ${TARGET} gtest)
    endif()
    set_target_properties(test_ktxreader PROPERTIES FOLDER Tests)
endif()
