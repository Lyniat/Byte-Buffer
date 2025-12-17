#include "memory_validation.cpp"

#include "bytebuffer/ByteBuffer.h"
#include <iostream>
#include <ostream>
#include <string>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;
using lyniat::memory::buffer::ReadBuffer;

int run_test() {
    auto bb = std::make_unique<ByteBuffer>();
    bb->AppendCString(test_string_haiku);
    bb->AppendCString(test_string_european);
    bb->AppendCString(test_string_haiku);

    // copy data
    std::unique_ptr<ReadBuffer> br = std::make_unique<ReadBuffer>(*bb);

    std::string result;

    br->ReadCStringAt(0, &result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 1 test string failed!")
    }

    br->ReadCStringAt(test_string_haiku.size() + 1, &result);
    if (result != test_string_european) {
        ERR_ENDL("European test string failed!")
    }

    br->ReadCStringAt(test_string_haiku.size() + 1 + test_string_european.size() + 1, &result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 2 test string failed!")
    }

    br->ReadCString(&result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 1 test string failed!")
    }

    br->ReadCString(&result);
    if (result != test_string_european) {
        ERR_ENDL("European test string failed!")
    }

    br->ReadCString(&result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 2 test string failed!")
    }

    bb = std::make_unique<ByteBuffer>();
    bb->AppendCString(test_string_haiku);
    bb->AppendCString(test_string_european);
    bb->AppendCString(test_string_haiku);

    std::unique_ptr<ReadBuffer> rb = std::move(bb);

    rb->ReadCString(&result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 1 test string failed!")
    }

    rb->ReadString(&result, test_string_european_start.size());
    if (result != test_string_european_start) {
        ERR_ENDL("European test string failed!")
    }

    rb->ReadCString(&result);
    if (result != test_string_european_end) {
        ERR_ENDL("European test string failed!")

    }

    bb = std::make_unique<ByteBuffer>();
    bb->AppendString(test_string_haiku);
    bb->AppendCString(test_string_european);
    bb->AppendCString(test_string_haiku);

    br = std::move(bb);

    br->ReadCString(&result);
    if (result != test_string_haiku + test_string_european) {
        ERR_ENDL("Combined test string failed!")
    }

    br->ReadCString(&result);
    if (result != test_string_haiku) {
        ERR_ENDL("Haiku 2 test string failed!")
    }

    return 0;
}

int main() {
    set_test_memory_allocator();

    auto result = run_test();

    if (result != 0) {
        return result;
    }

    auto leaks = check_allocated_memory();
    if (leaks != 0) {
        ERR(leaks)
        ERR_ENDL(" memory leaks detected!")
    }

    return 0;
}