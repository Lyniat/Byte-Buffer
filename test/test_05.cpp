#include "memory_validation.cpp"

#include "bytebuffer/ByteBuffer.h"
#include <iostream>
#include <ostream>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;
using lyniat::memory::Endianness;

int run_test() {
    auto bb = std::make_unique<ByteBuffer>();
    bb->AppendWithEndian(a, Endianness::Host);
    bb->AppendWithEndian(b, Endianness::Host);
    bb->AppendWithEndian(c, Endianness::Host);
    bb->AppendWithEndian(d, Endianness::Host);
    bb->AppendWithEndian(e, Endianness::Host);
    bb->AppendWithEndian(f, Endianness::Host);
    bb->AppendWithEndian(g, Endianness::Host);
    bb->AppendWithEndian(h, Endianness::Host);
    bb->AppendWithEndian(i, Endianness::Host);
    bb->AppendWithEndian(j, Endianness::Host);
    bb->AppendWithEndian(k, Endianness::Host);
    bb->AppendWithEndian(l, Endianness::Host);

    bb->AppendWithEndian(a, Endianness::Little);
    bb->AppendWithEndian(b, Endianness::Little);
    bb->AppendWithEndian(c, Endianness::Little);
    bb->AppendWithEndian(d, Endianness::Little);
    bb->AppendWithEndian(e, Endianness::Little);
    bb->AppendWithEndian(f, Endianness::Little);
    bb->AppendWithEndian(g, Endianness::Little);
    bb->AppendWithEndian(h, Endianness::Little);
    bb->AppendWithEndian(i, Endianness::Little);
    bb->AppendWithEndian(j, Endianness::Little);
    bb->AppendWithEndian(k, Endianness::Little);
    bb->AppendWithEndian(l, Endianness::Little);

    bb->AppendWithEndian(a, Endianness::Big);
    bb->AppendWithEndian(b, Endianness::Big);
    bb->AppendWithEndian(c, Endianness::Big);
    bb->AppendWithEndian(d, Endianness::Big);
    bb->AppendWithEndian(e, Endianness::Big);
    bb->AppendWithEndian(f, Endianness::Big);
    bb->AppendWithEndian(g, Endianness::Big);
    bb->AppendWithEndian(h, Endianness::Big);
    bb->AppendWithEndian(i, Endianness::Big);
    bb->AppendWithEndian(j, Endianness::Big);
    bb->AppendWithEndian(k, Endianness::Big);
    bb->AppendWithEndian(l, Endianness::Big);

    // NOLINTBEGIN(readability-braces-around-statements)
    if (!bb->Read(&_a)) return 1;
    if (!bb->Read(&_b)) return 1;
    if (!bb->Read(&_c)) return 1;
    if (!bb->Read(&_d)) return 1;
    if (!bb->Read(&_e)) return 1;
    if (!bb->Read(&_f)) return 1;
    if (!bb->Read(&_g)) return 1;
    if (!bb->Read(&_h)) return 1;
    if (!bb->Read(&_i)) return 1;
    if (!bb->Read(&_j)) return 1;
    if (!bb->Read(&_k)) return 1;
    if (!bb->Read(&_l)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    if (i != _i) return 1;
    if (j != _j) return 1;
    if (k != _k) return 1;
    if (l != _l) return 1;

    if (!bb->ReadWithEndian(&_a, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_b, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_c, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_d, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_e, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_f, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_g, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_h, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_i, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_j, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_k, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_l, Endianness::Little)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    if (i != _i) return 1;
    if (j != _j) return 1;
    if (k != _k) return 1;
    if (l != _l) return 1;

    if (!bb->ReadWithEndian(&_a, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_b, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_c, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_d, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_e, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_f, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_g, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_h, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_i, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_j, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_k, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_l, Endianness::Big)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    if (i != _i) return 1;
    if (j != _j) return 1;
    if (k != _k) return 1;
    if (l != _l) return 1;
    // NOLINTEND(readability-braces-around-statements)

    bb = std::make_unique<ByteBuffer>();
    bb->AppendWithEndian(a, Endianness::Host);
    bb->AppendWithEndian(b, Endianness::Host);
    bb->AppendWithEndian(c, Endianness::Host);
    bb->AppendWithEndian(d, Endianness::Host);
    bb->AppendWithEndian(e, Endianness::Host);
    bb->AppendWithEndian(f, Endianness::Host);
    bb->AppendWithEndian(g, Endianness::Host);
    bb->AppendWithEndian(h, Endianness::Host);
    bb->AppendWithEndian(i, Endianness::Host);
    bb->AppendWithEndian(j, Endianness::Host);
    bb->AppendWithEndian(k, Endianness::Host);
    bb->AppendWithEndian(l, Endianness::Host);

    // NOLINTBEGIN(readability-braces-around-statements)
#if BB_CPU_ENDIAN_LITTLE
    if (!bb->ReadWithEndian(&_a, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_b, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_c, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_d, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_e, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_f, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_g, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_h, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_i, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_j, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_k, Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_l, Endianness::Little)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    if (i != _i) return 1;
    if (j != _j) return 1;
    if (k != _k) return 1;
    if (l != _l) return 1;

#else
    if (!bb->ReadWithEndian(&_a, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_b, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_c, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_d, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_e, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_f, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_g, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_h, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_i, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_j, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_k, Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_l, Endianness::Big)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    if (h != _i) return 1;
    if (h != _j) return 1;
    if (h != _k) return 1;
    if (h != _l) return 1;
#endif
    // NOLINTEND(readability-braces-around-statements)

    bb = std::make_unique<ByteBuffer>();
#if BB_CPU_ENDIAN_LITTLE
    bb->AppendWithEndian(a, Endianness::Little);
    bb->AppendWithEndian(b, Endianness::Little);
    bb->AppendWithEndian(c, Endianness::Little);
    bb->AppendWithEndian(d, Endianness::Little);
    bb->AppendWithEndian(e, Endianness::Little);
    bb->AppendWithEndian(f, Endianness::Little);
    bb->AppendWithEndian(g, Endianness::Little);
    bb->AppendWithEndian(h, Endianness::Little);
    bb->AppendWithEndian(i, Endianness::Little);
    bb->AppendWithEndian(j, Endianness::Little);
    bb->AppendWithEndian(k, Endianness::Little);
    bb->AppendWithEndian(l, Endianness::Little);

    bb->AppendWithEndian(a, Endianness::Big);
    bb->AppendWithEndian(b, Endianness::Big);
    bb->AppendWithEndian(c, Endianness::Big);
    bb->AppendWithEndian(d, Endianness::Big);
    bb->AppendWithEndian(e, Endianness::Big);
    bb->AppendWithEndian(f, Endianness::Big);
    bb->AppendWithEndian(g, Endianness::Big);
    bb->AppendWithEndian(h, Endianness::Big);
    bb->AppendWithEndian(i, Endianness::Big);
    bb->AppendWithEndian(j, Endianness::Big);
    bb->AppendWithEndian(k, Endianness::Big);
    bb->AppendWithEndian(l, Endianness::Big);
#else
    bb->AppendWithEndian(a, Endianness::Big);
    bb->AppendWithEndian(b, Endianness::Big);
    bb->AppendWithEndian(c, Endianness::Big);
    bb->AppendWithEndian(d, Endianness::Big);
    bb->AppendWithEndian(e, Endianness::Big);
    bb->AppendWithEndian(f, Endianness::Big);
    bb->AppendWithEndian(g, Endianness::Big);
    bb->AppendWithEndian(h, Endianness::Big);
    bb->AppendWithEndian(i, Endianness::Big);
    bb->AppendWithEndian(j, Endianness::Big);
    bb->AppendWithEndian(k, Endianness::Big);
    bb->AppendWithEndian(l, Endianness::Big);

    bb->AppendWithEndian(a, Endianness::Little);
    bb->AppendWithEndian(b, Endianness::Little);
    bb->AppendWithEndian(c, Endianness::Little);
    bb->AppendWithEndian(d, Endianness::Little);
    bb->AppendWithEndian(e, Endianness::Little);
    bb->AppendWithEndian(f, Endianness::Little);
    bb->AppendWithEndian(g, Endianness::Little);
    bb->AppendWithEndian(h, Endianness::Little);
    bb->AppendWithEndian(i, Endianness::Little);
    bb->AppendWithEndian(j, Endianness::Little);
    bb->AppendWithEndian(k, Endianness::Little);
    bb->AppendWithEndian(l, Endianness::Little);
#endif

    // NOLINTBEGIN(readability-braces-around-statements)
    if (!bb->Read(&_a)) return 1;
    if (!bb->Read(&_b)) return 1;
    if (!bb->Read(&_c)) return 1;
    if (!bb->Read(&_d)) return 1;
    if (!bb->Read(&_e)) return 1;
    if (!bb->Read(&_f)) return 1;
    if (!bb->Read(&_g)) return 1;
    if (!bb->Read(&_h)) return 1;
    if (!bb->Read(&_i)) return 1;
    if (!bb->Read(&_j)) return 1;
    if (!bb->Read(&_k)) return 1;
    if (!bb->Read(&_l)) return 1;

    if (a != _a) return 1;
    if (b != _b) return 1;
    if (c != _c) return 1;
    if (d != _d) return 1;
    if (e != _e) return 1;
    if (f != _f) return 1;
    if (g != _g) return 1;
    if (h != _h) return 1;
    if (i != _i) return 1;
    if (j != _j) return 1;
    if (k != _k) return 1;
    if (l != _l) return 1;

    if (!bb->Read(&_a)) return 1;
    if (!bb->Read(&_b)) return 1;
    if (!bb->Read(&_c)) return 1;
    if (!bb->Read(&_d)) return 1;
    if (!bb->Read(&_e)) return 1;
    if (!bb->Read(&_f)) return 1;
    if (!bb->Read(&_g)) return 1;
    if (!bb->Read(&_h)) return 1;
    if (!bb->Read(&_i)) return 1;
    if (!bb->Read(&_j)) return 1;
    if (!bb->Read(&_k)) return 1;
    if (!bb->Read(&_l)) return 1;

    // a and b are only 1 byte; they will always be equal
    if (a != _a) return 1;
    if (b != _b) return 1;

    if (c == _c) return 1;
    if (d == _d) return 1;

    // a and b are only 1 byte; they will always be equal
    if (e != _e) return 1;
    if (f != _f) return 1;

    if (g == _g) return 1;
    if (h == _h) return 1;
    if (i == _i) return 1;
    if (j == _j) return 1;
    if (k == _k) return 1;
    if (l == _l) return 1;
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