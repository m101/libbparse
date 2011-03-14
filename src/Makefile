CC	=	gcc
CFLAGS	=	-g -O2 -Wall -W
LDFLAGS =

define compile_rule
	libtool --mode=compile $(CC) $(CFLAGS) $(CPPFLAGS) -c $<
endef
define link_rule
	libtool --mode=link $(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
endef

LIBS = libbparse.la
libbparse_OBJS = escape.lo file_binary.lo file_elf.lo file_elf_view.lo file_pe.lo file_pe_view.lo filemap.lo raw_data.lo

%.lo: %.c
	$(call compile_rule)

libbparse.la: $(libbparse_OBJS)
	$(call link_rule)

.PHONY: clean mrproper

clean:
	rm -f $(libbparse_OBJS)
	rm -f *.o
	rm -f libbparse.la

mrproper: clean
