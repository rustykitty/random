#include <stdint.h>

typedef union UUID {
    /* if __uint128_t is supported */
#ifdef __SIZEOF_INT128__
    __uint128_t int128;   
#endif
    uint64_t uint64_a[2];
    struct __attribute__((packed)) {
        uint64_t least64;
        uint64_t most64;
    };
    uint32_t uint32_a[2];
};
