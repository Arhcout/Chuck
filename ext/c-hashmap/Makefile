include ../../Makefile.in
PREFIX=../../

SRC=$(shell find . -name "*.c")
OBJ=$(SRC:%=%.o)

CFLAGS=$(BASE_CFLAGS)

LIB=$(PREFIX)ext/libhashmap.a

.DEFAULT: lib

.PHONY: lib clean

lib: $(LIB)

$(LIB): $(OBJ)
	$(AR) r $@ $^

%.c.o: %.c
	@echo "== COMPILING $@ =="
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(LIB)
