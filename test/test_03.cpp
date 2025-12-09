#include "memory_validation.cpp"

#include "bytebuffer/buffer.h"
#include <iostream>
#include <ostream>
#include <string>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;

#define ERR_ENDL(msg) std::cerr << msg << std::endl;
#define ERR(msg) std::cerr << msg;

int main() {
    set_test_memory_allocator();

    ByteBuffer* bb;

    bb = new ByteBuffer();
    bb->Append(test_string_european);

    auto bb2 = new ByteBuffer(*bb);
    delete bb;

    auto result_1 = bb2->to_string();
    if (result_1 != test_string_european) {
        ERR_ENDL("European test string failed!")
        return 1;
    }
    delete bb2;

    auto leaks = check_allocated_memory();
    if (leaks != 0) {
        ERR(leaks)
        ERR_ENDL(" memory leaks detected!")
        return 1;
    }

    return 0;
}