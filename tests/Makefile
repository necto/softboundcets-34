
KLEE_INCLUDE=../../klee/klee/include/

test-with-klee: full-test-klee.bc
	klee --libc=uclibc --posix-runtime full-test-klee.bc

full-test-klee.bc: test-klee.bc ../softboundcets-lib/softboundcets_klee_rt.bc
	llvm-link  test-klee.bc ../softboundcets-lib/softboundcets_klee_rt.bc -o full-test-klee.bc

test-klee.bc: test-klee.c
	clang -fsoftboundcets test-klee.c -S -o test-klee.bc -I$(KLEE_INCLUDE) -emit-llvm -target x86_64-pc-linux-gnu

