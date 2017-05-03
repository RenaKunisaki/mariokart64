#ifndef _N64_PATCH_H_
#define _N64_PATCH_H_

enum PatchType {
    PATCH_TYPE_BYTES = 0,
    PATCH_TYPE_JUMP,
    PATCH_TYPE_JAL,
    PATCH_TYPE_PTR
};

typedef struct {
    void* offset;
    const uint32_t patchType; //PATCH_TYPE_BYTES: write following data
    const uint8_t data[];
} PatchBytes;

typedef struct {
    void* offset;
    const uint32_t patchType;
    const uint32_t data[];
} PatchWords;

typedef struct {
    void* offset;
    const uint32_t patchType; //PATCH_TYPE_PTR: write from pointer (XXX size?)
    const void *data;
} PatchPtr;

#define _CONCAT(x, y) x ## y
#define CONCAT(x, y) _CONCAT(x, y)

#define PATCH_BYTES(offs, ...) \
__attribute__((section ("PATCH") )) __attribute__ ((__used__)) \
PatchBytes CONCAT(_patch_, __COUNTER__) = {offs, PATCH_TYPE_BYTES, __VA_ARGS__}

#define PATCH_WORDS(offs, ...) \
__attribute__((section ("PATCH") )) __attribute__ ((__used__)) \
PatchWords CONCAT(_patch_, __COUNTER__) = {offs, PATCH_TYPE_BYTES, __VA_ARGS__}

#define PATCH_PTR(offs, p) \
__attribute__((section ("PATCH") )) __attribute__ ((__used__)) \
PatchPtr CONCAT(_patch_, __COUNTER__) = {offs, PATCH_TYPE_PTR, (const void*)(p)}

/* We could just use PATCH_WORDS here and compute the J/JAL right in the macro.
 * But, gcc refuses to cooperate, and just spits out zero any time I try to
 * perform any non-trivial bit operations on a casted pointer.
 */
#define PATCH_JUMP(offs, p) \
__attribute__((section ("PATCH") )) __attribute__ ((__used__)) \
PatchWords CONCAT(_patch_, __COUNTER__) = {offs, PATCH_TYPE_JUMP, (uint32_t)(p)}

#define PATCH_JAL(offs, p) \
__attribute__((section ("PATCH") )) __attribute__ ((__used__)) \
PatchWords CONCAT(_patch_, __COUNTER__) = {offs, PATCH_TYPE_JAL, (uint32_t)(p)}

#define PATCH_NOP(offs) PATCH_WORDS(offs, {0})

#endif //_N64_PATCH_H_
