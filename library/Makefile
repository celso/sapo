# Possible defines: SUP_MSQL    - To include msql support
#                   SUP_FTPWEB  - To include ftpweb.c functions
DEFINES= -D SUP_MSQL
CFLAGS = -Wno-pointer-sign -Wno-int-conversion -Wno-invalid-source-encoding -Wno-array-bounds -Wno-format -Wno-invalid-pp-token -Wno-implicit-int -Wno-parentheses -Wno-implicit-function-declaration -Wno-return-type -O3 -I../include -I/usr/include $(DEFINES)
SHELL =		/bin/sh
RANLIB =		ranlib
CC =		cc

LIB_OBJS = args.o sgml.o crypt.o text.o lists.o ftpweb.o file.o url.o templates.o queries.o logs.o bandas.o time.o soundex.o http.o sapo.o miolo.o cookies.o dbwrapper.o noticias.o

LIB_OBJS_NOSQL = args.o sgml.o crypt.o text.o lists.o ftpweb.o file.o url.o templates.o queries.o logs.o bandas.o time.o soundex.o http.o sapo.o cookies.o noticias.o

all: ctools.a ctools_nosql.a

ctools.a: $(LIB_OBJS)
	rm -f ctools.a
	ar cr ctools.a $(LIB_OBJS)
	$(RANLIB) ctools.a
	@echo "Library created."

ctools_nosql.a: $(LIB_OBJS_NOSQL)
	rm -f ctools_nosql.a
	ar cr ctools_nosql.a $(LIB_OBJS_NOSQL)
	$(RANLIB) ctools_nosql.a
	@echo "Library created."

clean:
	rm -f *.a *.o core errs *~ \#* TAGS *.E a.out
	@echo "All clean. Type make all to rebuild."

# DO NOT DELETE THIS LINE -- make depend depends on it.
args.o:		args.h \
		macros.h \
		protos.h
sgml.o:		sgml.h \
		macros.h \
		protos.h
crypt.o:	protos.h
text.o:		text.h \
		macros.h \
		protos.h
lists.o:	lists.h \
		macros.h \
		protos.h
text.o:		text.h \
		macros.h \
		protos.h
fptweb.o:	ftpweb.h \
		macros.h \
		protos.h
file.o:		file.h \
		macros.h \
		protos.h
url.o:		url.h \
		macros.h \
		protos.h
soundex.o:	soundex.h \
		macros.h \
		protos.h
http.o:		http.h \
		macros.h \
		protos.h
http.o:	macros.h \
		protos.h
dbwrapper.o:		dbwrapper.h
templates.o:		lists.h \
		macros.h \
		templates.h \
		protos.h
