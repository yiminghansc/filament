/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLTFIO_JITCOLORSHADER_H
#define GLTFIO_JITCOLORSHADER_H

#include <gltfio/MaterialProvider.h>

#include <filamat/MaterialBuilder.h>
#include <filament/Material.h>
#include <filament/MaterialInstance.h>

#include <string>

namespace filament::gltfio {

class UTILS_PUBLIC JitColorShaderProvider {
public:
    virtual ~JitColorShaderProvider() {}

    // Jit materials are cached based on MaterialKey.
    // Here the input key can be modified to account for variations in custom
    // color handling
    virtual void processMaterialKey(MaterialKey* key, UvMap* uvmap,
            const char* label, const cgltf_material* srcMaterial) {}

    // 'processBaseColor' function provides a way to inject custom color shader
    virtual std::string getShaderString(const MaterialKey& config, const UvMap& uvmap,
            const char* label, const cgltf_material* srcMaterial) {
        std::string shader = R"SHADER(
                void processBaseColor(inout MaterialInputs material) {
                }
            )SHADER";
        return shader;
    }

    // Here custom parameters for color handling can be added
    virtual void processMaterial(filamat::MaterialBuilder& builder,
            const MaterialKey& config, const UvMap& uvmap,
            const char* label, const cgltf_material* srcMaterial) {}

    // Set required color handling parameters
    virtual void processMaterialInstance(MaterialInstance* instance,
            const MaterialKey& config, const UvMap& uvmap,
            const char* label, const cgltf_material* srcMaterial) {}
};

} // namespace filament::gltfio

#endif // GLTFIO_JITCOLORSHADER_H
