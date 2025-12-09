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
    auto size_before = bb->Size();
    bb->Compress();
    auto size_after = bb->Size();

    if (size_before == size_after) {
        ERR_ENDL("Compressed and uncompressed data have same length!")
        return 1;
    }

    bb->Uncompress();
    auto size_end = bb->Size();

    if (size_before != size_end) {
        ERR_ENDL("Compression input and output don't match length!")
        return 1;
    }

    auto result_1 = bb->to_string();

    if (result_1 != test_string_european) {
        ERR_ENDL("Compression failed!")
        return 1;
    }
    delete bb;

    auto leaks = check_allocated_memory();
    if (leaks != 0) {
        ERR(leaks)
        ERR_ENDL(" memory leaks detected!")
        return 1;
    }

    return 0;
}