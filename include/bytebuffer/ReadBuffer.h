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

#include <filesystem>
#include <limits>

// Might be useful in future when porting to more platforms
static_assert(std::numeric_limits<float>::is_iec559 && sizeof(float) == 4,
              "Requires IEEE 754 binary32 (float)");
static_assert(std::numeric_limits<double>::is_iec559 && sizeof(double) == 8,
              "Requires IEEE 754 binary64 (double)");

// https://github.com/bkaradzic/bx/blob/master/include/bx/inline/endian.inl
// Endianness
#define BB_CPU_ENDIAN_BIG    0
#define BB_CPU_ENDIAN_LITTLE 0

// CPU
#define BB_CPU_ARM   0
#define BB_CPU_X86   0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__)     \
|| defined(__aarch64__) \
|| defined(_M_ARM)
#	undef  BB_CPU_ARM
#	define BB_CPU_ARM 1
#	undef  BB_CPU_ENDIAN_LITTLE
#	define BB_CPU_ENDIAN_LITTLE 1
#else
#	undef  BB_CPU_X86
#	define BB_CPU_X86 1
#	undef  BB_CPU_ENDIAN_LITTLE
#	define BB_CPU_ENDIAN_LITTLE 1
#endif

#include <cstddef>
#include <string>
#include "endian.inl"

namespace lyniat::memory::buffer {
using namespace lyniat::memory;

class ReadBuffer {
public:
    enum Endianness {
        Host,
        Little,
        Big,
    };

    ReadBuffer();

    explicit ReadBuffer(size_t size);

    ReadBuffer(void* new_ptr, size_t size, bool copy = false);

    explicit ReadBuffer(const std::filesystem::path& path);

    // Rule of Five Implementation
    ReadBuffer(const ReadBuffer& other);
    ReadBuffer& operator=(const ReadBuffer& other);
    ReadBuffer(ReadBuffer&& other) noexcept;
    ReadBuffer& operator=(ReadBuffer&& other) noexcept;


    virtual ~ReadBuffer();

    template<typename T>
    bool Read(T* data) {
        static_assert(
        std::is_arithmetic_v<T> ||
        (std::is_trivial_v<T> && std::is_standard_layout_v<T>),
        "T must be numeric or a POD-like struct");
        return ReadData(data, sizeof(T));
    }

    template<typename T>
    bool Read(T* data, size_t size) {
        static_assert(
        std::is_arithmetic_v<T> ||
        (std::is_trivial_v<T> && std::is_standard_layout_v<T>),
        "T must be numeric or a POD-like struct");
        return ReadData(data, size);
    }

    template<typename T>
    bool ReadWithEndian(T* data, Endianness endian) {
        static_assert(std::is_arithmetic_v<T>, "T must be numeric");
        T read;
        auto result = Read(&read, sizeof(T));
        if (!result) {
            return false;
        }
        switch (endian) {
            case Host:
                #if BB_CPU_ENDIAN_BIG
                *data = bx::toHostEndian(read, false);
                #else
                *data = toHostEndian(read, true);
                #endif
                break;
            case Little: *data = toLittleEndian(read);
                break;
            case Big: *data = toBigEndian(read);
                break;
        }
        return true;
    }

    bool ReadString(std::string* str, size_t size);
    bool ReadCString(std::string* str);

    bool ReadCStringAt(size_t pos, std::string* str);
    bool ReadStringAt(size_t pos, std::string* str, size_t size);

    template<typename T>
    bool ReadAt(size_t pos, T* data) {
        static_assert(
        std::is_arithmetic_v<T> ||
        (std::is_trivial_v<T> && std::is_standard_layout_v<T>),
        "T must be numeric or a POD-like struct");
        return ReadDataAt(pos, data, sizeof(T));
    }

    template<typename T>
    bool ReadAt(size_t pos, T* data, size_t size) {
        static_assert(
        std::is_arithmetic_v<T> ||
        (std::is_trivial_v<T> && std::is_standard_layout_v<T>),
        "T must be numeric or a POD-like struct");
        return ReadDataAt(pos, data, size);
    }

    template<typename T>
    bool ReadWithEndianAt(size_t pos, T* data, Endianness endian) {
        static_assert(std::is_arithmetic_v<T>, "T must be numeric");
        T read;
        auto result = ReadDataAt(pos, &read, sizeof(T));
        if (!result) {
            return false;
        }
        switch (endian) {
            case Host:
                #if BB_CPU_ENDIAN_BIG
                *data = bx::toHostEndian(read, false);
                #else
                *data = toHostEndian(read, true);
                #endif
                break;
            case Little: *data = toLittleEndian(read);
                break;
            case Big: *data = toBigEndian(read);
                break;
        }
        return true;
    }

    size_t Size();

    bool ReadOnly();

    size_t CurrentReadingPos();

    uint64_t Hash();

    bool WriteToDisk(const std::filesystem::path& path);

    std::string to_string();

protected:
    std::byte* ptr;
    size_t b_size;
    size_t b_length;
    bool ReadData(void* data, size_t size);
    bool ReadDataAt(size_t pos, void* data, size_t size);
    size_t current_pos;
    bool free_memory;
    bool read_only;

    // read feature
    size_t current_read_pos;
};

}