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
#include <cstdint>
#include <string>

namespace lyniat::memory::buffer {
class ByteBuffer {
public:
    ByteBuffer();

    explicit ByteBuffer(size_t size);

    ByteBuffer(void* new_ptr, size_t size, bool copy = false);

    // Rule of Five Implementation
    ByteBuffer(const ByteBuffer& other);
    ByteBuffer& operator=(const ByteBuffer& other);
    ByteBuffer(ByteBuffer&& other) noexcept;
    ByteBuffer& operator=(ByteBuffer&& other) noexcept;


    ~ByteBuffer();

    bool Append(const std::string& data) {
        return AppendData(data.c_str(), data.size());
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

    template<typename T>
    bool SetAt(size_t pos, T data) {
        return SetDataAt(pos, &data, sizeof(T));
    }

    template<typename T>
    bool SetAt(size_t pos, T* data, size_t size) {
        return SetDataAt(pos, data, size);
    }

    template<typename T>
    bool Read(T* data) {
        return ReadData(data, sizeof(T));
    }

    template<typename T>
    bool Read(T* data, size_t size) {
        return ReadData(data, size);
    }

    const std::byte* Data() const;

    std::byte* MutableData();

    const std::byte* DataAt(size_t position) const;

    size_t Size();

    bool ReadOnly();

    size_t CurrentPos();

    bool Compress();

    bool Uncompress();

    uint64_t Hash();

    std::string to_string();

private:
    std::byte* ptr;
    size_t b_size;
    size_t b_length;
    bool AppendData(const void* data, size_t size);
    bool SetDataAt(size_t pos, void* data, size_t size);
    bool ReadData(void* data, size_t size);
    size_t current_pos;
    bool free_memory;
    bool read_only;

    // read feature
    size_t current_read_pos;
};

}