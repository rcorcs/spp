CC=g++
CFLAGS=-std=c++11 -lpthread #-lsupc++

IDIR = ../

_DEPS = spp.h fork.h map.h reduce.h pipeline.h array.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ../../obj/test
_OBJ = fork.o map.o reduce.o pipeline.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: fork map reduce pipeline

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

map: $(ODIR)/map.o $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

reduce: $(ODIR)/reduce.o
	$(CC) -o $@ $^ $(CFLAGS)

fork: $(ODIR)/fork.o
	$(CC) -o $@ $^ $(CFLAGS)

pipeline: $(ODIR)/pipeline.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ fork map reduce pipeline
