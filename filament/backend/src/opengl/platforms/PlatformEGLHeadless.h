/*
 * Copyright (C) 2022 The Android Open Source Project
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

#ifndef TNT_FILAMENT_DRIVER_OPENGL_PLATFORM_EGL_HEADLESS_H
#define TNT_FILAMENT_DRIVER_OPENGL_PLATFORM_EGL_HEADLESS_H

#include "PlatformEGL.h"

namespace filament::backend {

class PlatformEGLHeadless final : public PlatformEGL {
public:

    PlatformEGLHeadless() noexcept;

    backend::Driver* createDriver(void* sharedContext) noexcept final;

    void createExternalImageTexture(void* texture) noexcept final {}
    void destroyExternalImage(void* texture) noexcept final {}

    int getOSVersion() const noexcept final { return 0; }

    void setPresentationTime(int64_t presentationTimeInNanosecond) noexcept final {}

    Stream* createStream(void* nativeStream) noexcept final { return nullptr; }
    void destroyStream(Stream* stream) noexcept final {}
    void attach(Stream* stream, intptr_t tname) noexcept final {}
    void detach(Stream* stream) noexcept final {}
    void updateTexImage(Stream* stream, int64_t* timestamp) noexcept final {}
};

} // namespace filament

#endif // TNT_FILAMENT_DRIVER_OPENGL_PLATFORM_EGL_HEADLESS_H
