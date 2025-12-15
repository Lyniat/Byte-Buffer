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

#include "bytebuffer/ReadBuffer.h"
#include "bytebuffer/memory.h"
#include "komihash.h"

#include <iostream>
#include <ostream>

namespace lyniat::memory::buffer {

ReadBuffer::ReadBuffer() {
    ptr = nullptr;
    b_size = 0;
    b_length = 0;
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;
}

ReadBuffer::ReadBuffer(void* new_ptr, size_t size, bool copy) {
    ptr = nullptr;
    b_size = 0;
    b_length = 0;
    current_pos = 0;
    current_read_pos = 0;
    read_only = true;
    if (copy) {
        ptr = (std::byte*)ossp_malloc(size);
        memmove(ptr, new_ptr, size);
        b_size = size;
        b_length = size;
        free_memory = true;
    } else {
        ptr = (std::byte*)new_ptr;
        b_size = size;
        b_length = size;
        free_memory = false;
    }
}

// copy constructor
ReadBuffer::ReadBuffer(const ReadBuffer& b) {
    b_size = b.b_size;
    b_length = b.b_size;
    ptr = (std::byte*)ossp_malloc(b_size);
    memmove(ptr, b.ptr, b_size);
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;
}

ReadBuffer& ReadBuffer::operator=(const ReadBuffer& other) {
    if (this == &other) {
        return *this;
    }
    // cleanup old data
    if (free_memory && ptr) {
        ossp_free(ptr);
    }

    // copy new data
    b_size = other.b_size;
    b_length = other.b_length;
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;

    if (other.ptr && other.b_size > 0) {
        ptr = (std::byte*)ossp_malloc(b_size);
        if (ptr) {
            memmove(ptr, other.ptr, b_size);
        }
    } else {
        ptr = nullptr;
    }

    return *this;
}

ReadBuffer::ReadBuffer(ReadBuffer&& other) noexcept
    : ptr(other.ptr)
      , b_size(other.b_size)
      , b_length(other.b_length)
      , current_pos(other.current_pos)
      , free_memory(other.free_memory)
      , read_only(other.read_only)
      , current_read_pos(other.current_read_pos) {
    other.ptr = nullptr;
    other.b_size = 0;
    other.b_length = 0;
    other.free_memory = false;
    // positions are not relevant for empty buffer
}

ReadBuffer& ReadBuffer::operator=(ReadBuffer&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (free_memory && ptr) {
        ossp_free(ptr);
    }

    ptr = other.ptr;
    b_size = other.b_size;
    b_length = other.b_length;
    current_pos = other.current_pos;
    current_read_pos = other.current_read_pos;
    free_memory = other.free_memory;
    read_only = other.read_only;

    other.ptr = nullptr;
    other.b_size = 0;
    other.b_length = 0;
    other.free_memory = false;

    return *this;
}


ReadBuffer::ReadBuffer(size_t size) {
    ptr = (std::byte*)ossp_malloc(size);
    b_size = size;
    b_length = size;
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;
}

ReadBuffer::~ReadBuffer() {
    if (free_memory) {
        ossp_free(ptr);
    }
}

size_t ReadBuffer::Size() {
    return b_size;
}

bool ReadBuffer::ReadOnly() {
    return read_only;
}

size_t ReadBuffer::CurrentReadingPos() {
    return current_pos;
}

uint64_t ReadBuffer::Hash() {
    return komihash(ptr, b_size, 0);
}

bool ReadBuffer::Read(std::string* str) {
    return Read(str, SIZE_MAX);
}

bool ReadBuffer::Read(std::string* str, size_t size){
    if (current_read_pos < b_size) {
        auto diff = b_size - current_read_pos;
        auto read_ptr = (char*)ptr + current_read_pos;
        auto len =  std::min(strnlen(read_ptr, diff), size);
        auto read_str = std::string(read_ptr, len);
        current_read_pos += read_str.size() + 1;
        *str = read_str;
        return true;
    }
    return false;
}

bool ReadBuffer::ReadAt(size_t pos, std::string* str){
    return ReadAt(pos, str, SIZE_MAX);
}

bool ReadBuffer::ReadAt(size_t pos, std::string* str, size_t size){
    if (pos < b_size) {
        auto diff = b_size - pos;
        auto read_ptr = (char*)ptr + pos;
        auto len = std::min(strnlen(read_ptr, diff), size);
        *str = std::string(read_ptr, len);
        return true;
    }
    return false;
}

bool ReadBuffer::ReadData(void* data, size_t size) {
    if (current_read_pos + size <= b_size) {
        memmove(data, (char*)ptr + current_read_pos, size);
        current_read_pos += size;
        return true;
    }
    return false;
}

bool ReadBuffer::ReadDataAt(size_t pos, void* data, size_t size) {
    if (pos + size <= b_size) {
        memmove(data, (char*)ptr + pos, size);
        return true;
    }
    return false;
}

std::string ReadBuffer::to_string() {
    auto len = strnlen((char*)ptr, b_size);
    return std::string((char*)ptr, len);
}
}