
# A path to the Klee user include directory. should be in the form
# $(KLEE_ROOT_DIR)/include/
KLEE_INCLUDE=../../klee/klee/include/

# Automated symbolic-execution testing
test-with-klee: full-test-klee.bc
	klee --libc=uclibc --posix-runtime full-test-klee.bc

# Manual testing
test: test.bin
	./test.bin

test.bin: test.c
	clang -fsoftboundcets test.c -o test.bin -L../softboundcets-lib -lm -lrt

full-test-klee.bc: test-klee.bc ../softboundcets-lib/softboundcets_klee_rt.bc
	llvm-link  test-klee.bc ../softboundcets-lib/softboundcets_klee_rt.bc -o full-test-klee.bc

test-klee.bc: test-klee.c
	clang -fsoftboundcets test-klee.c -S -o test-klee.bc -I$(KLEE_INCLUDE) -emit-llvm -target x86_64-pc-linux-gnu

