#include "memory_validation.cpp"

#include "bytebuffer/ByteBuffer.h"
#include <iostream>
#include <ostream>
#include <string>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;
using lyniat::memory::buffer::ReadBuffer;

#define ERR_ENDL(msg) std::cerr << msg << std::endl;
#define ERR(msg) std::cerr << msg;

int main() {
    set_test_memory_allocator();

    ByteBuffer* bb;

    bb = new ByteBuffer();
    bb->Append(test_string_haiku);
    bb->Append(test_string_european);
    bb->Append(test_string_haiku);

    auto br = new ReadBuffer(*bb);

    delete bb;

    std::string result;

    br->ReadAt(0, &result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 1 test string failed!")
        return 1;
    }

    br->ReadAt(test_string_haiku.size() + 1, &result);
    if (result != test_string_european) {
        ERR_ENDL("European test string failed!")
        return 1;
    }

    br->ReadAt(test_string_haiku.size() + 1 + test_string_european.size() + 1, &result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 2 test string failed!")
        return 1;
    }

    br->Read(&result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 1 test string failed!")
        return 1;
    }

    br->Read(&result);
    if (result != test_string_european) {
        ERR_ENDL("European test string failed!")
        return 1;
    }

    br->Read(&result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 2 test string failed!")
        return 1;
    }

    delete br;

    auto leaks = check_allocated_memory();
    if (leaks != 0) {
        ERR(leaks)
        ERR_ENDL(" memory leaks detected!")
        return 1;
    }

    return 0;
}