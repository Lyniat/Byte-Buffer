#include "memory_validation.cpp"

#include "bytebuffer/buffer.h"
#include <iostream>
#include <ostream>
#include "content.h"

using lyniat::memory::buffer::ByteBuffer;

#define ERR_ENDL(msg) std::cerr << msg << std::endl;
#define ERR(msg) std::cerr << msg;

int main() {
    set_test_memory_allocator();

    ByteBuffer* bb;

    bb = new ByteBuffer();
    bb->AppendWithEndian(a, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Host);

    bb->AppendWithEndian(a, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Little);

    bb->AppendWithEndian(a, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Big);

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

    if (!bb->ReadWithEndian(&_a, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_b, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_c, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_d, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_e, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_f, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_g, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_h, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_i, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_j, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_k, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_l, ByteBuffer::Endianness::Little)) return 1;

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

    if (!bb->ReadWithEndian(&_a, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_b, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_c, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_d, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_e, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_f, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_g, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_h, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_i, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_j, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_k, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_l, ByteBuffer::Endianness::Big)) return 1;

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

    delete bb;

    bb = new ByteBuffer();
    bb->AppendWithEndian(a, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Host);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Host);

    // NOLINTBEGIN(readability-braces-around-statements)
#if BB_CPU_ENDIAN_LITTLE
    if (!bb->ReadWithEndian(&_a, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_b, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_c, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_d, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_e, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_f, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_g, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_h, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_i, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_j, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_k, ByteBuffer::Endianness::Little)) return 1;
    if (!bb->ReadWithEndian(&_l, ByteBuffer::Endianness::Little)) return 1;

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
    if (!bb->ReadWithEndian(&_a, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_b, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_c, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_d, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_e, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_f, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_g, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_h, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_i, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_j, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_k, ByteBuffer::Endianness::Big)) return 1;
    if (!bb->ReadWithEndian(&_l, ByteBuffer::Endianness::Big)) return 1;

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

    delete bb;

    bb = new ByteBuffer();
#if BB_CPU_ENDIAN_LITTLE
    bb->AppendWithEndian(a, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Little);

    bb->AppendWithEndian(a, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Big);
#else
    bb->AppendWithEndian(a, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Big);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Big);

    bb->AppendWithEndian(a, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(b, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(c, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(d, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(e, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(f, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(g, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(h, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(i, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(j, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(k, ByteBuffer::Endianness::Little);
    bb->AppendWithEndian(l, ByteBuffer::Endianness::Little);
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

    delete bb;

    auto leaks = check_allocated_memory();
    if (leaks != 0) {
        ERR(leaks)
        ERR_ENDL(" memory leaks detected!")
        return 1;
    }

    return 0;
}