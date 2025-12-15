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

#include "bytebuffer/memory.h"
#include "bytebuffer/buffer.h"
#include "komihash.h"

#define LZAV_MALLOC( s, T ) (T*) ossp_malloc( s )
#define LZAV_FREE( p ) ossp_free( p )
#include "lzav.h"

namespace lyniat::memory::buffer {

ByteBuffer::ByteBuffer() {
    ptr = nullptr;
    b_size = 0;
    b_length = 0;
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;
}

ByteBuffer::ByteBuffer(void* new_ptr, size_t size, bool copy) {
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
ByteBuffer::ByteBuffer(const ByteBuffer& b) {
    b_size = b.b_size;
    b_length = b.b_size;
    ptr = (std::byte*)ossp_malloc(b_size);
    memmove(ptr, b.ptr, b_size);
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;
}

ByteBuffer& ByteBuffer::operator=(const ByteBuffer& other) {
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

ByteBuffer::ByteBuffer(ByteBuffer&& other) noexcept
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

ByteBuffer& ByteBuffer::operator=(ByteBuffer&& other) noexcept {
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


ByteBuffer::ByteBuffer(size_t size) {
    ptr = (std::byte*)ossp_malloc(size);
    b_size = size;
    b_length = size;
    current_pos = 0;
    current_read_pos = 0;
    free_memory = true;
    read_only = false;
}

ByteBuffer::~ByteBuffer() {
    if (free_memory) {
        ossp_free(ptr);
    }
}

const std::byte* ByteBuffer::Data() const {
    return ptr;
}

std::byte* ByteBuffer::MutableData() {
    return ptr;
}

const std::byte* ByteBuffer::DataAt(size_t position) const {
    if (position >= b_size) {
        return nullptr;
    }
    return (std::byte*)((char*)ptr + position);
}

size_t ByteBuffer::Size() {
    return b_size;
}

bool ByteBuffer::ReadOnly() {
    return read_only;
}

size_t ByteBuffer::CurrentReadingPos() {
    return current_pos;
}

bool ByteBuffer::SetCurrentReadingPos(size_t pos) {
    if (pos <= b_size) {
        current_read_pos = pos;
        return true;
    }
    return false;
}

bool ByteBuffer::Compress() {
    auto max_len = lzav_compress_bound(b_size);
    auto c_data = ossp_malloc(max_len);;
    int comp_len = lzav_compress_default(ptr, c_data, b_size, max_len);
    if (comp_len < 0) {
        ossp_free(c_data);
        return false;
    }
    if (free_memory) {
        ossp_free(ptr);
    }
    auto final_len = comp_len + sizeof(uint32_t);
    auto final_ptr = (char*)ossp_malloc(final_len);
    memmove(final_ptr + (sizeof(uint32_t)), c_data, comp_len);
    ossp_free(c_data);
    ((uint32_t*)final_ptr)[0] = b_size;

    b_size = final_len;
    b_length = final_len;
    free_memory = true;
    ptr = (std::byte*)final_ptr;
    return true;
}

bool ByteBuffer::Uncompress() {
    auto decomp_len = (int)((uint32_t*)ptr)[0];
    void* decomp_buf = (char*)ossp_malloc(decomp_len);
    void* data_start = ((char*)ptr) + sizeof(uint32_t);
    int l = lzav_decompress(data_start, decomp_buf, b_size - sizeof(uint32_t), decomp_len);
    if (l < 0) {
        //problem?
        ossp_free(decomp_buf);
        return false;
    }
    if (free_memory) {
        ossp_free(ptr);
    }
    ptr = (std::byte*)decomp_buf;
    b_size = l;
    b_length = l;
    free_memory = true;
    return true;
}

uint64_t ByteBuffer::Hash() {
    return komihash(ptr, b_size, 0);
}

bool ByteBuffer::AppendData(const void* data, size_t size) {
    if (read_only) {
        return false;
    }
    if (b_size + size > b_length) {
        if (b_length == 0) {
            const size_t MiB = 1024 * 1024;
            b_length = MiB > size ? MiB : size;
            b_size = 0;
            ptr = (std::byte*)ossp_malloc(b_length);
            if (!ptr) {
                return false;
            }
        } else {
            auto new_length = b_length * 2 + size;
            auto r_pointer = realloc(ptr, new_length);
            b_length = new_length;
            //as backup
            if (r_pointer == nullptr) {
                auto new_ptr = ossp_malloc(new_length);
                memmove(new_ptr, ptr, b_size);
                ossp_free(ptr);
                ptr = (std::byte*)new_ptr;
            } else {
                ptr = (std::byte*)r_pointer;
            }
            return true;
        }
    }
    memmove((char*)ptr + b_size, data, size);
    b_size = b_size + size;
    current_pos += size;
    return true;
}

bool ByteBuffer::SetDataAt(size_t pos, void* data, size_t size) {
    if (read_only) {
        return false;
    }
    if (pos + size < b_size) {
        memmove((char*)ptr + pos, data, size);
        return true;
    }
    return false;
}

bool ByteBuffer::ReadData(void* data, size_t size) {
    if (current_read_pos + size <= b_size) {
        memmove(data, (char*)ptr + current_read_pos, size);
        current_read_pos += size;
        return true;
    }
    return false;
}

bool ByteBuffer::ReadDataAt(size_t pos, void* data, size_t size) {
    if (pos + size <= b_size) {
        memmove(data, (char*)ptr + pos, size);
        return true;
    }
    return false;
}

std::string ByteBuffer::to_string() {
    return {(char*)ptr, b_size};
}
}