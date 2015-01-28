CC=g++
CFLAGS=-std=c++11 -lpthread #-lsupc++

IDIR = ../

_DEPS= spp.h fork.h map.h reduce.h array.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR=../../obj/test
_OBJ = map.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: map

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

map: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ map
