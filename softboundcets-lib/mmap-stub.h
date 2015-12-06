#include <string.h>
#include <sys/types.h>
#include <assert.h>

#define PREALLOCATED_SIZE  1024*1024*1024UL

#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20
#define MAP_NORESERVE 0x04000

#define PROT_READ 0x1
#define PROT_WRITE 0x2

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
