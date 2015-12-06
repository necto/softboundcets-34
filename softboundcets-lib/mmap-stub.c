#include <stdio.h>
#include "mmap-stub.h"

char bigarray[PREALLOCATED_SIZE];
size_t allocated = 0;

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
    assert(addr == 0);
    assert(prot == (PROT_READ | PROT_WRITE));
    assert(flags == (MAP_PRIVATE|MAP_ANONYMOUS|MAP_NORESERVE));
    assert(offset == 0);
    assert(fd == -1);
    
    assert(allocated + length < PREALLOCATED_SIZE);
    size_t start = allocated; 
    allocated += length;
    printf("allocated 0x%lx bytes between %p and %p\n", length, bigarray+start, bigarray+allocated);
    return &bigarray[start];
}
