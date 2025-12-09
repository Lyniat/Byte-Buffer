#include "memory_validation.cpp"

#include <../include/bytebuffer/buffer.h>
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

    uint8_t a = 123;
    int8_t b = -4;
    uint16_t c = 7654;
    int16_t d = -6543;
    bool e = false;
    bool f = true;
    float g = 3.14f;
    double h = 1.2345;

    uint8_t _a;
    int8_t _b;
    uint16_t _c;
    int16_t _d;
    bool _e;
    bool _f;
    float _g;
    double _h;

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

    delete bb;

    auto leaks = check_allocated_memory();
    if (leaks != 0) {
        ERR(leaks)
        ERR_ENDL(" memory leaks detected!")
        return 1;
    }

    return 0;
}