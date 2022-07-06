cmake_minimum_required(VERSION 3.19)
project(mipgen)

set(TARGET mipgen)

# ==================================================================================================
# Source files
# ==================================================================================================
set(SRCS src/main.cpp)

# ==================================================================================================
# Target definitions
# ==================================================================================================
add_executable(${TARGET} ${SRCS})

set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

if(HUNTER_ENABLED)
  target_link_libraries(${TARGET} PRIVATE math utils ZLIB::zlib image imageio)
  if (MSVC)
    target_link_libraries(${TARGET} PRIVATE getopt::getopt)
  endif()
else()
  target_link_libraries(${TARGET} PRIVATE math utils z image imageio getopt)
endif()

# =================================================================================================
# Licenses
# ==================================================================================================
set(MODULE_LICENSES getopt libpng tinyexr libz stb)
set(GENERATION_ROOT ${CMAKE_CURRENT_BINARY_DIR}/generated)
list_licenses(${GENERATION_ROOT}/licenses/licenses.inc ${MODULE_LICENSES})
target_include_directories(${TARGET} PRIVATE ${GENERATION_ROOT})

# ==================================================================================================
# Installation
# ==================================================================================================
install(TARGETS ${TARGET} EXPORT ${TARGETS_EXPORT_NAME} RUNTIME DESTINATION bin)
install(FILES "README.md" DESTINATION docs/ RENAME "${TARGET}.md")
