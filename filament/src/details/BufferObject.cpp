/*
 * Copyright (C) 2021 The Android Open Source Project
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

#include "details/BufferObject.h"

#include "details/Engine.h"

#include "FilamentAPI-impl.h"

namespace filament {

struct BufferObject::BuilderDetails {
    BindingType mBindingType = BindingType::VERTEX;
    BufferUsage mBufferUsage = BufferUsage::STATIC;
    CreateCallback mCreateCallback = nullptr;
    void* mCreateCallbackUserData = nullptr;
    DestroyCallback mDestroyCallback = nullptr;
    void* mDestroyCallbackUserData = nullptr;
    uint32_t mByteCount = 0;
};

using BuilderType = BufferObject;
BuilderType::Builder::Builder() noexcept = default;
BuilderType::Builder::~Builder() noexcept = default;
BuilderType::Builder::Builder(BuilderType::Builder const& rhs) noexcept = default;
BuilderType::Builder::Builder(BuilderType::Builder&& rhs) noexcept = default;
BuilderType::Builder& BuilderType::Builder::operator=(BuilderType::Builder const& rhs) noexcept = default;
BuilderType::Builder& BuilderType::Builder::operator=(BuilderType::Builder&& rhs) noexcept = default;

BufferObject::Builder& BufferObject::Builder::size(uint32_t byteCount) noexcept {
    mImpl->mByteCount = byteCount;
    return *this;
}

BufferObject::Builder& BufferObject::Builder::bindingType(BindingType bindingType) noexcept {
    mImpl->mBindingType = bindingType;
    return *this;
}

BufferObject::Builder& BufferObject::Builder::bufferUsage(BufferUsage bufferUsage) noexcept {
    mImpl->mBufferUsage = bufferUsage;
    return *this;
}

BufferObject::Builder& BufferObject::Builder::createCallback(CreateCallback callback, void* user) noexcept {
    mImpl->mCreateCallback = callback;
    mImpl->mCreateCallbackUserData = user;
    return *this;
}

BufferObject::Builder& BufferObject::Builder::destroyCallback(DestroyCallback callback, void* user) noexcept {
    mImpl->mDestroyCallback = callback;
    mImpl->mDestroyCallbackUserData = user;
    return *this;
}

BufferObject* BufferObject::Builder::build(Engine& engine) {
    return downcast(engine).createBufferObject(*this);
}

// ------------------------------------------------------------------------------------------------

FBufferObject::FBufferObject(FEngine& engine, const BufferObject::Builder& builder)
        : mByteCount(builder->mByteCount), mBindingType(builder->mBindingType),
            mBufferUsage(builder->mBufferUsage), mDestroyCallback(builder->mDestroyCallback),
            mDestroyCallbackUserData(builder->mDestroyCallbackUserData) {
    FEngine::DriverApi& driver = engine.getDriverApi();
    mHandle = driver.createBufferObject(mByteCount, mBindingType, mBufferUsage);
    if (builder->mCreateCallback) {
        driver.getBufferObjectHwResource(mHandle, builder->mCreateCallback, builder->mCreateCallbackUserData);
    }
}

void FBufferObject::terminate(FEngine& engine) {
    FEngine::DriverApi& driver = engine.getDriverApi();
    if (mDestroyCallback) {
        driver.getBufferObjectHwResource(mHandle, mDestroyCallback, mDestroyCallbackUserData);
    }
    driver.destroyBufferObject(mHandle);
}

void FBufferObject::setBuffer(FEngine& engine, BufferDescriptor&& buffer, uint32_t byteOffset) {
    engine.getDriverApi().updateBufferObject(mHandle, std::move(buffer), byteOffset);
}

void FBufferObject::getBuffer(FEngine& engine, BufferDescriptor&& buffer, uint32_t byteOffset) {
    engine.getDriverApi().getBufferData(mHandle, std::move(buffer), byteOffset);
}

} // namespace filament
