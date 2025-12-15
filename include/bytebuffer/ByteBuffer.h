/*
* MIT License
*
* Copyright (c) 2025 Laurin "lyniat" Muth
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
*         of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
*         to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*         copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
*         copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*         AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#include <cstddef>
#include <string>
#include "ReadBuffer.h"

namespace lyniat::memory::buffer {
using namespace lyniat::memory;

class ByteBuffer : public ReadBuffer {
public:
    using ReadBuffer::ReadBuffer;

    bool Append(const std::string& data) {
        if (AppendData(data.c_str(), data.size())) {
            const uint8_t nt = '\0';
            return AppendData(&nt, sizeof(nt));
        }
        return false;
    }

    template<typename T>
    bool Append(T data) {
        return AppendData(&data, sizeof(T));
    }

    template<typename T>
    bool Append(T* data, size_t size) {
        return AppendData(data, size);
    }

    template<typename T>
    bool Append(const T* data, size_t size) {
        return AppendData(data, size);
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    void AppendWithEndian(T data, Endianness endian) {
        T converted;
        switch (endian) {
            case Host:
                #if BB_CPU_ENDIAN_BIG
                converted = bx::toHostEndian(data, false);
                #else
                converted = toHostEndian(data, true);
                #endif
                break;
            case Little: converted = toLittleEndian(data);
                break;
            case Big: converted = toBigEndian(data);
                break;
        }
        AppendData(&converted, sizeof(T));
    }

    template<typename T>
    bool SetAt(size_t pos, T data) {
        return SetDataAt(pos, &data, sizeof(T));
    }

    template<typename T>
    bool SetAt(size_t pos, T* data, size_t size) {
        return SetDataAt(pos, data, size);
    }

    template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    bool SetAtWithEndian(size_t pos, T data, Endianness endian) {
        T converted;
        switch (endian) {
            case Host:
                #if BB_CPU_ENDIAN_BIG
                converted = bx::toHostEndian(data, false);
                #else
                converted = toHostEndian(data, true);
                #endif
                break;
            case Little: converted = toLittleEndian(data);
                break;
            case Big: converted = toBigEndian(data);
                break;
        }
        return SetDataAt(pos, &converted, sizeof(T));
    }

    const std::byte* Data() const;

    const std::byte* DataAt(size_t position) const;

    bool SetCurrentReadingPos(size_t pos);

    bool Compress();

    bool Uncompress();

private:
    bool AppendData(const void* data, size_t size);
    bool SetDataAt(size_t pos, void* data, size_t size);
};

}