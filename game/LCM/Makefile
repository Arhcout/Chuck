include ../../Makefile.in
PREFIX=../../

SRC=$(shell find . -name "*.c")
OBJ=$(SRC:%=%.o)

CFLAGS=$(BASE_CFLAGS) -I$(PREFIX)game -fPIC 
LDFLAGS=$(BASE_LDFLAGS) -shared

.DEFAULT: $(LCM_LIB)

$(LCM_LIB):  $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.c.o: %.c
	@echo "== COMPILING $@ =="
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(LCM_LIB)
