#You may wish to add -DNO_UNISTD and -DNO_SYSTEM to CFLAGS if
#your system lacks the /usr/include/unistd.h header file
#or the system() function, respectively. Non-unix systems
#will also definitely have different linker syntax.

CFLAGS=
CC=gcc
AR=ar
LIBS=-L./ -lcgic

all: libcgic.a cgictest capture

libcgic.a: cgic.o cgic.h
	rm -f libcgic.a
	$(AR) rc libcgic.a cgic.o

cgictest: cgictest.o libcgic.a
	gcc cgictest.o -o cgictest ${LIBS}

capture: capture.o libcgic.a
	gcc capture.o -o capture ${LIBS}

clean:
	rm -f *.o *.a cgictest capture

