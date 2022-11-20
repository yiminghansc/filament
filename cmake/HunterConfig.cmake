hunter_config(civetweb VERSION 1.11-p0
              CMAKE_ARGS CIVETWEB_ENABLE_WEBSOCKETS=ON)

hunter_config(SPIRV-Headers 
              URL https://github.com/KhronosGroup/SPIRV-Headers/archive/refs/tags/sdk-1.3.231.1.zip
              SHA1 c70697e501823485f9a232649b02ab55545eed11
              CMAKE_ARGS 
                SPIRV_HEADERS_SKIP_EXAMPLES=ON)


hunter_config(SPIRV-Tools 
              URL https://github.com/zbai-sc/SPIRV-Tools/archive/refs/tags/v2022.3-p0.tar.gz
              SHA1 9fc2998b77582623e2272ed7d03340b55317bc00
              CMAKE_ARGS
                SPIRV_TOOLS_BUILD_STATIC=OFF
                SPIRV_SKIP_EXECUTABLES=ON
                SPIRV_SKIP_TESTS=ON
                SPIRV_WERROR=OFF)

hunter_config(spirv-cross
              URL https://github.com/KhronosGroup/SPIRV-Cross/archive/refs/tags/sdk-1.3.231.1.zip
              SHA1 47cdca60a201178f6783ae8745ec3ec3a6148135
              CMAKE_ARGS
                SPIRV_CROSS_CLI=OFF
                SPIRV_CROSS_ENABLE_TESTS=OFF)

hunter_config(glslang 
              URL https://github.com/KhronosGroup/glslang/archive/refs/tags/11.12.0.tar.gz
              SHA1 8a5da853addebe077cc3217555a667ac66040bb4
              CMAKE_ARGS 
                BUILD_TESTING=OFF
                BUILD_EXTERNAL=OFF
                ENABLE_CTEST=OFF
                ENABLE_AMD_EXTENSIONS=ON
                ENABLE_NV_EXTENSIONS=ON
                ENABLE_OPT=OFF
                ENABLE_GLSLANG_BINARIES=OFF)

hunter_config(VulkanMemoryAllocator VERSION 2.3.0-p0)

hunter_config(cgltf
              URL https://github.com/cpp-pm/cgltf/archive/refs/tags/v1.13-p0.tar.gz
              SHA1 bcff0c818201c5652acf03675f3714d5132e75f8
              CMAKE_ARGS
                BUILD_AS_LIBRARY=OFF)

hunter_config(basis_universal VERSION 1.16.3-p0)

hunter_config(meshoptimizer VERSION 0.16-86740c2-p0
              CMAKE_ARGS
                MESHOPT_BUILD_DEMO=OFF
                MESHOPT_BUILD_GLTFPACK=OFF
                MESHOPT_BUILD_SHARED_LIBS=OFF)
