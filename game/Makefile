include ../Makefile.in
PREFIX=../

SRC=$(shell find . -name "*.c" -not -name "main.c")
OBJ=$(SRC:%=%.o)
ENTRY=main.c.o

LIBS=-Wl,-rpath,$(PREFIX)ext/lib -Wl,--enable-new-dtags -lSDL3 -lSDL3_image -lm -lhashmap -lcbase 
LDFLAGS=$(BASE_LDFLAGS)
CFLAGS=$(BASE_CFLAGS)

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
