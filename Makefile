CXX = /home/takai/bin/gcc710/bin/g++
INCLUDE = ./include
DST = ./dst
SRC = .
BIN = ./bin
OBJS = $(DST)/point.o $(DST)/main.o $(DST)/koma.o $(DST)/wcm.o $(DST)/mochi_goma.o  \
 $(DST)/banmen.o $(DST)/tegoma.o $(DST)/naru.o $(DST)/ai.o $(DST)/eval.o

all: $(OBJS)
	mkdir -p bin
	$(CXX) -o $(BIN)/coyuri  $(OBJS) $(LDFLAGS)

$(DST)/%.o:	$(SRC)/%.cpp
	mkdir -p dst
	$(CXX) $(CFLAGS) -Ofast -march=native -std=c++11 -c -o $(DST)/$*.o $(SRC)/$*.cpp $(LDFLAGS)

clean:
	rm -f $(DST)/* $(BIN)/*
