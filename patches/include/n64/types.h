#ifndef _N64_TYPES_H_
#define _N64_TYPES_H_
#include <stdint.h>

#define BIT(n) (1 << (n))

//these aren't totally necessary, but lots of N64 devs, as well as
//Nintendo's SDK, uses these, so when in Rome...
/*
typedef  int8_t  s8;
typedef uint8_t  u8;
typedef  int16_t s16;
typedef uint16_t u16;
typedef  int32_t s32;
typedef uint32_t u32;
typedef  int64_t s64;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;

typedef volatile  int8_t  vs8;
typedef volatile uint8_t  vu8;
typedef volatile  int16_t vs16;
typedef volatile uint16_t vu16;
typedef volatile  int32_t vs32;
typedef volatile uint32_t vu32;
typedef volatile  int64_t vs64;
typedef volatile uint64_t vu64;
typedef volatile float    vf32;
typedef volatile double   vf64;
*/

typedef u32 rspPtr;
typedef struct { float x, y, z; } vec3f;
typedef struct { s16   x, y, z; } vec3i;

#endif //_N64_TYPES_H_
