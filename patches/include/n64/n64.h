#ifndef _N64_H_
#define _N64_H_

#include <ultra64.h>
#include "ultra64/PR/os.h"
#include "ultra64/PR/os_inter.h"
#include "ultra64/PR/os_internal.h"
#include "types.h"
#include "lib/libc/libc.h"
#include "pi.h"
#include "lib/rawio/rawio.h"
#include "mio0.h"
#include "patch.h"
#include "lib/64drive/64drive.h"

//tell gcc not to reorder operations across barriers
#define MEMORY_BARRIER() asm volatile ("" : : : "memory")

#endif //_N64_H_
