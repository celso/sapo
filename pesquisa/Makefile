SHELL =		/bin/sh

RANLIB =		ranlib
CC =		cc
CFLAGS =        -Wno-pointer-sign -Wno-int-conversion -Wno-invalid-source-encoding -Wno-array-bounds -Wno-format -Wno-invalid-pp-token -Wno-implicit-int -Wno-parentheses -Wno-implicit-function-declaration -Wno-return-type -O3 -I../cgic/
CLFLAGS =       -lm -lcdb
P      =	
OUTP   =	pesquisa

OBJS = pesquisa.o
LIBS = ../cgic/libcgic.a ../library/ctools_nosql.a

all: 	pesquisa

pesquisa: $(P) $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) $(CLFLAGS) -o $(OUTP)
	@echo "$(OUTP) compiled."

clean:
	rm -f $(OUTP)
	rm -f *.a *.o core errs *~ \#* TAGS *.E a.out
	@echo "All clean. Type make all to rebuild."

install: rinstall

rinstall:	all
	@echo "Installi remote copy."
#	scp pesquisa celso@zebedeu:
	@echo "pesquisa remotely installed."


# DO NOT DELETE THIS LINE -- make depend depends on it.
pesquisa.o:
