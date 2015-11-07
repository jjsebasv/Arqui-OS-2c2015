#ifndef _LIBASM_H
#define _LIBASM_H

#include <stdint.h>

extern void execSysCall( uint64_t code, uint64_t arg1, uint64_t arg2, uint64_t arg3 );

#endif
