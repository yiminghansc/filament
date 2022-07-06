hunter_config(civetweb VERSION 1.11-p0
             CMAKE_ARGS CIVETWEB_ENABLE_WEBSOCKETS=ON)

hunter_config(SPIRV-Headers VERSION 1.5.1.corrected)

hunter_config(SPIRV-Tools VERSION 2020.1-p0)

hunter_config(spirv-cross
              URL https://github.com/elisemorysc/SPIRV-Cross/archive/refs/tags/2021.6.21.zip
              SHA1 c443b739c27574cf5cc2c3a68798d6dc453d4110)

hunter_config(glslang VERSION 8.13.3743-9eef54b2-p0
              CMAKE_ARGS ENABLE_HLSL=OFF ENABLE_GLSLANG_BINARIES=OFF ENABLE_OPT=OFF BUILD_TESTING=OFF)

hunter_config(VulkanMemoryAllocator VERSION 2.3.0-p0)

hunter_config(cgltf
              URL https://github.com/zbai-sc/cgltf/archive/refs/heads/hunter-1.12.zip
              SHA1 b925b8cd49004c712991607c3e9db47366672c7e)

hunter_config(basis_universal VERSION 1.16.3-p0)
