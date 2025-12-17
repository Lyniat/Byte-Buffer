#include <filesystem>

#include "memory_validation.cpp"

#include "bytebuffer/ByteBuffer.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include "content.h"

using lyniat::memory::buffer::ReadBuffer;
using lyniat::memory::buffer::ByteBuffer;

int run_test() {
    auto test_path = std::filesystem::current_path().append(test_file_name);

    auto bb = std::make_unique<ByteBuffer>();

    std::cout << check_allocated_memory() << std::endl;

    bb->AppendString(test_string_european_start);
    bb->Append(a);
    bb->Append(b);
    bb->Append(c);
    bb->Append(d);
    bb->Append(e);
    bb->Append(f);
    bb->Append(g);
    bb->Append(h);
    bb->Append(i);
    bb->Append(j);
    bb->Append(k);
    bb->Append(l);
    bb->AppendCString(test_string_haiku);
    bb->AppendCString(test_string_european_end);

    auto hash = bb->Hash();

    if (!bb->WriteToDisk(test_path)) {
        ERR_ENDL("WriteToDisk failed!")
    }

    std::cout << check_allocated_memory() << std::endl;

    auto rb = std::make_unique<ByteBuffer>(test_file_name);

    if (rb->Size() == 0) {
        ERR_ENDL("ReadBuffer size is zero!")
    }

    std::string start_str;
    if (!rb->ReadString(&start_str, test_string_european_start.size())) {
        ERR_ENDL("ReadString failed!")
    }

    if (start_str != test_string_european_start) {
        ERR_ENDL("European string failed!")
    }

    auto test_hash = rb->Hash();

    if (hash != test_hash) {
        ERR_ENDL("Hash test failed!")
    }

    std::cout << check_allocated_memory() << std::endl;

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