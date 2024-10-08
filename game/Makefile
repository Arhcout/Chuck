include ../Makefile.in
PREFIX=../

SRC=$(shell find . -name "*.c" -not -name "main.c")
OBJ=$(SRC:%=%.o)
ENTRY=main.c.o

LIBS=-lhashmap -lcbase $(shell, sdl2-config --libs)
LDFLAGS=$(BASE_LDFLAGS)
CFLAGS=$(BASE_CFLAGS) $(shell, sdl2-config --cflags)

.DEFAULT: $(GAME)

$(GAME): $(ENTRY) $(GAME_LIB)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(GAME_LIB): $(OBJ)
	$(AR) r $@ $^

%.c.o: %.c
	@echo "== COMPILING $@ =="
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(ENTRY)
