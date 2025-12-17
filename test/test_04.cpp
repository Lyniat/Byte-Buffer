#include "memory_validation.cpp"

#include "bytebuffer/ByteBuffer.h"
#include <iostream>
#include <ostream>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;

int run_test() {
    auto bb = std::make_unique<ByteBuffer>();

    bb->Append(a);
    bb->Append(b);
    bb->Append(c);
    bb->Append(d);
    bb->Append(e);
    bb->Append(f);
    bb->Append(g);
    bb->Append(h);

    size_t size = sizeof(a) + sizeof(b) + sizeof(c) + sizeof(d) + sizeof(e) + sizeof(f) + sizeof(g) + sizeof(h);
    if (bb->Size() != size) {
        return 1;
    }

    bb->Compress();
    bb->Uncompress();

    if (bb->Size() != size) {
        return 1;
    }

    // NOLINTBEGIN(readability-braces-around-statements)
    if (!bb->Read(&_a)) return 1;
    if (!bb->Read(&_b)) return 1;
    if (!bb->Read(&_c)) return 1;
    if (!bb->Read(&_d)) return 1;
    if (!bb->Read(&_e)) return 1;
    if (!bb->Read(&_f)) return 1;
    if (!bb->Read(&_g)) return 1;
    if (!bb->Read(&_h)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    // NOLINTEND(readability-braces-around-statements)

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