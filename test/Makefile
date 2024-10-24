include ../Makefile.in
PREFIX=../

SRC=$(shell find . -name "*.c")
TESTS=$(SRC:%=%.test)
TESTING_SCRIPT=./test.sh

LIBS=-Wl,-rpath,$(CURDIR)/$(PREFIX)ext/lib -Wl,--enable-new-dtags -lSDL3 -lSDL3_image -lm $(PREFIX)libchuck.a -lhashmap -lcbase
CFLAGS=$(BASE_CFLAGS) -I$(PREFIX)game
LDFLAGS=$(BASE_LDFLAGS)

.PHONY: run_tests tests clean

.DEFAULT: run_tests
run_tests: $(TESTS)
	$(TESTING_SCRIPT) $^

tests: $(TESTS)

%.c.test: %.c
	@echo "== BUILDING TEST $@ =="
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f $(TESTS)
