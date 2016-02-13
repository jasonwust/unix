FLAG=  -m elf_i386  -dynamic-linker /lib/ld-linux.so.2 -lc -L/lib -o
objs := cconvert.d
main:$(objs)
	ld $(FLAG) $@ $^
%.d:%.s
	as --32 -g -o $@ $^
clean:
	rm -rf *.d main
.PHONY: clean
