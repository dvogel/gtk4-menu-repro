
CFLAGS+=-I. $(shell pkg-config --cflags gtk4)
LDFLAGS+=-L/usr/local/lib -Wl,--as-needed $(shell pkg-config --libs gtk4)

basic:
	$(MAKE) clean
	$(MAKE) gtk4-menu-repro
	./gtk4-menu-repro

custom:
	$(MAKE) clean
	CFLAGS=-DCUSTOM_WIDGETS $(MAKE) gtk4-menu-repro
	./gtk4-menu-repro

gtk4-menu-repro: gtk4-menu-repro.o
	gcc -g -o $@ $< $(LDFLAGS)

gtk4-menu-repro.o: main.c
	gcc -g -Wall $(CFLAGS) -c -o $@ $<

clean:
	rm -f gtk4-menu-repro gtk4-menu-repro.o

.PHONY: basic clean custom
