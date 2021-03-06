all: softboundcets_rt softboundmpx_rt softboundcets_klee_rt.bc

MPX_FLAGS=-Wall -pedantic -O3 -D__SOFTBOUNDMPX_SPATIAL 
CFLAGS=-Wall -pedantic  -D__SOFTBOUNDCETS_SPATIAL_TEMPORAL -O3 -fno-strict-aliasing
KLEE_CFLAGS=$(CFLAGS) -D__FOR_KLEE -target x86_64-pc-linux-gnu
ARFLAGS=-rcs

# If LLVM_GOLD is set, also build a library for use with LTO
#
# Note that the name of the library is hardcoded in the compiler. Thus, we call
# it the same, but put it in the lto/ subdirectory. To use it, pass
# -L/path/to/softboundcets-lib/lto to the compiler, and use -flto during
# compilation and linking
ifneq ($(LLVM_GOLD),)
all: softboundcets_rt_lto softboundmpx_rt_lto
endif

softboundmpx_rt: softboundmpx.h softboundmpx-checks.c softboundmpx.c softboundmpx-wrappers.c
	clang $(MPX_FLAGS) -c softboundmpx-checks.c -o softboundmpx-checks.o
	clang $(MPX_FLAGS) -c softboundmpx.c -o softboundmpx.o
	clang $(MPX_FLAGS) -c softboundmpx-wrappers.c -o softboundmpx-wrappers.o
	ar $(ARFLAGS) libsoftboundmpx_rt.a softboundmpx.o softboundmpx-checks.o softboundmpx-wrappers.o

softboundcets_rt: softboundcets.h softboundcets-checks.c softboundcets.c softboundcets-wrappers.c 
	clang $(CFLAGS) -c softboundcets-checks.c -o softboundcets-checks.o
	clang $(CFLAGS) -c softboundcets.c -o softboundcets.o
	clang $(CFLAGS) -c softboundcets-wrappers.c -o softboundcets-wrappers.o
	ar $(ARFLAGS) libsoftboundcets_rt.a softboundcets.o softboundcets-checks.o softboundcets-wrappers.o

softboundcets_klee_rt.bc: softboundcets.h softboundcets-checks.c softboundcets.c softboundcets-wrappers.c mmap-stub.h mmap-stub.c
	clang $(KLEE_CFLAGS) -c -g -emit-llvm softboundcets-checks.c -o softboundcets-checks.bc
	clang $(KLEE_CFLAGS) -c -g -emit-llvm softboundcets.c -o softboundcets.bc
	clang $(KLEE_CFLAGS) -c -g -emit-llvm softboundcets-wrappers.c -o softboundcets-wrappers.bc
	clang $(KLEE_CFLAGS) -c -g -emit-llvm mmap-stub.c -o mmap-stub.bc
	llvm-link softboundcets-checks.bc softboundcets.bc softboundcets-wrappers.bc mmap-stub.bc -o softboundcets_klee_rt.bc

softboundcets_rt_lto: softboundcets.h softboundcets-checks.c softboundcets.c softboundcets-wrappers.c 
	mkdir lto
	clang $(CFLAGS) -flto -c softboundcets-checks.c -o lto/softboundcets-checks.lto.o
	clang $(CFLAGS) -flto -c softboundcets.c -o lto/softboundcets.lto.o
	clang $(CFLAGS) -flto -c softboundcets-wrappers.c -o lto/softboundcets-wrappers.lto.o
	ar --plugin=$(LLVM_GOLD) $(ARFLAGS) lto/libsoftboundcets_rt.a lto/softboundcets.lto.o lto/softboundcets-checks.lto.o lto/softboundcets-wrappers.lto.o


softboundmpx_rt_lto: softboundmpx.h softboundmpx-checks.c softboundmpx.c softboundmpx-wrappers.c
	clang $(MPX_FLAGS) -flto -c softboundmpx-checks.c -o lto/softboundmpx-checks.lto.o
	clang $(MPX_FLAGS) -flto -c softboundmpx.c -o lto/softboundmpx.lto.o
	clang $(MPX_FLAGS) -flto -c softboundmpx-wrappers.c -o lto/softboundmpx-wrappers.lto.o
	ar --plugin=$(LLVM_GOLD) $(ARFLAGS) lto/libsoftboundmpx_rt.a lto/softboundmpx.lto.o lto/softboundmpx-checks.lto.o lto/softboundmpx-wrappers.lto.o


clean:
	rm -rf *.o *.bc *.a *~ lto/

