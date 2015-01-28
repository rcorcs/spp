CC=g++
CFLAGS=-std=c++11 -lpthread #-lsupc++

DEPS= spp.h fork.h map.h reduce.h array.h

ODIR=../obj
_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< -c $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ main
