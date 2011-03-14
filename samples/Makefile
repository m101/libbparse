LIBBPARSE_PATH = ../src

TOOLS	=	read_elf read_pe dump
COMMON	=	$(LIBBPARSE_PATH)/escape.o $(LIBBPARSE_PATH)/file_binary.o
COMMON +=   $(LIBBPARSE_PATH)/file_elf.o $(LIBBPARSE_PATH)/file_elf_view.o
COMMON +=   $(LIBBPARSE_PATH)/file_pe.o $(LIBBPARSE_PATH)/file_pe_view.o
COMMON += 	$(LIBBPARSE_PATH)/filemap.o
DEPS	=	Makefile $(LIBBPARSE_PATH)/file_generic.h $(LIBBPARSE_PATH)/type_windows.h

CC	=	gcc
CFLAGS	=	-g -O2 -Wall -W -I$(LIBBPARSE_PATH)
LDFLAGS =	

OBJS	= $(COMMON) $(addsuffix .o, $(TOOLS))

all: $(TOOLS)

$(TOOLS): %: %.o $(COMMON) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< $(COMMON) $(LDFLAGS)

$(OBJS): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TOOLS)
	rm -f $(LIBBPARSE_PATH)/*.o
