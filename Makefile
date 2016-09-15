CFLAGS=-Wall -Werror -pedantic -static
OBJ=dictionary.o strutil.o

debug: CFLAGS += -g -O0
debug: libnucommon.a

libnucommon.a: libnucommon.a($(OBJ))

.c.a:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $*.o
	$(AR) r $@ $*.o
	$(RM) $*.o