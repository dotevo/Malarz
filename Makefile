LIBS+=$(shell  sdl-config --libs )
CFLAGS=-Wall -Wno-deprecated 
CFLAGS+=$(shell sdl-config --cflags)

PROGS=malarz

EXT=cc

GCC=g++

CC=${GCC} ${INCLUDE} ${CFLAGS} 
LINK=${GCC}
GENDEP=${GCC} -MM ${INCLUDE} ${CFLAGS} 2> /dev/null

OBJS:=$(patsubst %.${EXT},%.o, $(wildcard *.${EXT}))
DEPS:=$(patsubst %.${EXT},.%.d, $(wildcard *.${EXT}))

.PHONY: all
all: ${PROGS}
	@ echo Build complete

.%.d: %.${EXT}
	@ echo DEP $<
	@ ${GENDEP} $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

${PROGS}: ${DEPS} ${OBJS}
	@ echo LINK $@
	${LINK} ${OBJS} ${LIBS}  -lSDL_image -lSDL_ttf -o  $@
	@ strip $@

${OBJS}: %.o: %.${EXT}
	@ echo CC $<
	@ ${CC} -c $<

REALDEPS:=$(wildcard .*.d)
ifneq ($(strip $(REALDEPS)),)
include ${REALDEPS}
endif

.PHONY: clean
clean:
	@ echo CLEAN ${PROGS}
	@ rm -f ${PROGS}

	@ echo CLEAN ${OBJS}
	@ rm -f ${OBJS}

	@ echo CLEAN ${DEPS}
	@ rm -f ${DEPS}


