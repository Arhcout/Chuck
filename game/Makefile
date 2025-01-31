include ../Makefile.in
PREFIX=../

SRC=$(shell find . -name "*.c" -not -name "main.c")
OBJ=$(SRC:%=%.o)
EXT_OBJ=
ENTRY=main.c.o

LIBS=$(BASE_LIBS)
LDFLAGS=$(BASE_LDFLAGS)
CFLAGS=$(BASE_CFLAGS)

.DEFAULT: $(GAME)

$(GAME): $(ENTRY) $(GAME_LIB)
	$(CC) $(LDFLAGS)  $^ $(EXT_OBJ) -o $@ $(LIBS) 

$(GAME_LIB): $(OBJ)
	$(AR) r $@ $^

%.c.o: %.c
	@echo "== COMPILING $@ =="
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(ENTRY)
