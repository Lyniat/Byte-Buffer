#include "memory_validation.cpp"

#include "bytebuffer/ByteBuffer.h"
#include <iostream>
#include <ostream>
#include <string>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;
using lyniat::memory::buffer::ReadBuffer;

int run_test() {
    set_test_memory_allocator();

    auto bb = std::make_unique<ByteBuffer>();
    bb->AppendString(test_string_european);

    std::unique_ptr<ReadBuffer> rb = std::move(bb);

    auto result_1 = rb->to_string();
    if (result_1 != test_string_european) {
        ERR_ENDL("European test string failed!")
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