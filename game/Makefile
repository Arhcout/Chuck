include ../Makefile.in
PREFIX=../

SRC=$(shell find . -name "*.c" -not -name "main.c" -not -name "LuaCM*")
OBJ=$(SRC:%=%.o)
ENTRY=main.c.o

LIBS=$(BASE_LIBS)
LDFLAGS=$(BASE_LDFLAGS)
CFLAGS=$(BASE_CFLAGS)

.DEFAULT: $(GAME)

$(GAME): $(ENTRY) $(GAME_LIB)
	$(MAKE) -C $(LCM_DIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(GAME_LIB): $(OBJ)
	$(AR) r $@ $^

%.c.o: %.c
	@echo "== COMPILING $@ =="
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	$(MAKE) -C $(LCM_DIR) clean
	rm -f $(OBJ) $(ENTRY)
