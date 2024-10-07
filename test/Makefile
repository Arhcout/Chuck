include ../Makefile.in
PREFIX=../

SRC=$(shell find . -name "*.c")
TESTS=$(SRC:%=%.test)
TESTING_SCRIPT=./test.sh

LIBS=-lcbase $(shell, sdl2-config --libs) $(PREFIX)libchuck.a
LDFLAGS=$(BASE_LDFLAGS)
CFLAGS=$(BASE_CFLAGS) -I$(PREFIX)game -I$(PREFIX)ext/CBase/src $(shell, sdl2-config --cflags)

.DEFAULT: tests

tests: $(TESTS)
	$(TESTING_SCRIPT) $^

%.c.test: %.c
	@echo "== BUILDING TEST $@ =="
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TESTS)
