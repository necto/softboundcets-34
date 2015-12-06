// A drop-in substitute for the sys/mman.h header. Supports only a single
// mode usage of the mmap function.

#include <string.h>
#include <sys/types.h>
#include <assert.h>

// 1 Gb is not enough for SoftBoundCETS on 64 bit machine;
// 2 Gb appears to be just fine.
// 4 Gb causes a memory violation access in the SB runtime library;
#define PREALLOCATED_SIZE  2*1024*1024*1024UL

// Copies of the supported flags from sys/mman.h
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20
#define MAP_NORESERVE 0x04000

// Copies of the supported access modes from sys/mman.h
#define PROT_READ 0x1
#define PROT_WRITE 0x2

// This looks like the general prototype of the POSIX mmap function but it
// supports only a single combination of arguments, see mmap-stub.c. It
// allocates parts of a static global array, and may allocate for up to
// PREALLOCATED_SIZE bytes in total.
void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
