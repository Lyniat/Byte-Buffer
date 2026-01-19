#include <cstring> //needed by gcc

namespace lyniat::memory
{
    inline uint8_t endianSwap(uint8_t _in)
    {
        return _in;
    }

    inline int8_t endianSwap(int8_t _in)
    {
        return _in;
    }

    inline uint16_t endianSwap(uint16_t _in)
    {
        return (_in>>8) | (_in<<8);
    }

    inline int16_t endianSwap(int16_t _in)
    {
        return (int16_t)endianSwap( (uint16_t)_in);
    }

    inline uint32_t endianSwap(uint32_t _in)
    {
        return (  _in            >>24) | (  _in            <<24)
             | ( (_in&0x00ff0000)>> 8) | ( (_in&0x0000ff00)<< 8)
             ;
    }

    inline int32_t endianSwap(int32_t _in)
    {
        return (int32_t)endianSwap( (uint32_t)_in);
    }

    inline uint64_t endianSwap(uint64_t _in)
    {
        return   (_in                               >>56) | (  _in                               <<56)
             | ( (_in&UINT64_C(0x00ff000000000000) )>>40) | ( (_in&UINT64_C(0x000000000000ff00) )<<40)
             | ( (_in&UINT64_C(0x0000ff0000000000) )>>24) | ( (_in&UINT64_C(0x0000000000ff0000) )<<24)
             | ( (_in&UINT64_C(0x000000ff00000000) )>> 8) | ( (_in&UINT64_C(0x00000000ff000000) )<< 8)
             ;
    }

    inline int64_t endianSwap(int64_t _in)
    {
        return (int64_t)endianSwap( (uint64_t)_in);
    }

    inline float endianSwap(float _in)
    {
        uint32_t u;
        std::memcpy(&u, &_in, sizeof(u));
        u = (u >> 24) |
            ((u >> 8 ) & 0x0000FF00UL) |
            ((u << 8 ) & 0x00FF0000UL) |
            (u << 24);

        float v;
        std::memcpy(&v, &u, sizeof(_in));
        return v;
    }

    inline double endianSwap(double _in)
    {
        uint64_t u;
        std::memcpy(&u, &_in, sizeof(u));
        u = (u >> 56) |
            ((u >> 40) & 0x000000000000FF00ULL) |
            ((u >> 24) & 0x0000000000FF0000ULL) |
            ((u >> 8 ) & 0x00000000FF000000ULL) |
            ((u << 8 ) & 0x000000FF00000000ULL) |
            ((u << 24) & 0x0000FF0000000000ULL) |
            ((u << 40) & 0x00FF000000000000ULL) |
            (u << 56);

        double v;
        std::memcpy(&v, &u, sizeof(_in));
        return v;
    }

    template <typename Ty>
    inline Ty toLittleEndian(Ty _in)
    {
#if BB_CPU_ENDIAN_BIG
        return endianSwap(_in);
#else
        return _in;
#endif // BB_CPU_ENDIAN_BIG
    }

    template <typename Ty>
    inline Ty toBigEndian(Ty _in)
    {
#if BB_CPU_ENDIAN_LITTLE
        return endianSwap(_in);
#else
        return _in;
#endif // BB_CPU_ENDIAN_LITTLE
    }

    template <typename Ty>
    inline Ty toHostEndian(Ty _in, bool _fromLittleEndian)
    {
#if BB_CPU_ENDIAN_LITTLE
        return _fromLittleEndian ? _in : endianSwap(_in);
#else
        return _fromLittleEndian ? endianSwap(_in) : _in;
#endif // BB_CPU_ENDIAN_LITTLE
    }

}