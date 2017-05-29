CXX = /home/takai/bin/gcc710/bin/g++
INCLUDE = ./include
DST = ./dst
SRC = .
BIN = ./bin
OBJS = $(DST)/point.o $(DST)/main.o $(DST)/init.o $(DST)/koma.o $(DST)/wcm.o $(DST)/masu.o \
 $(DST)/banmen.o $(DST)/tegoma.o $(DST)/naru.o $(DST)/files.o $(DST)/ai.o $(DST)/eval.o

all: $(OBJS)
	mkdir -p bin
	$(CXX) -o $(BIN)/coyuri  $(OBJS) $(LDFLAGS)

$(DST)/%.o:	$(SRC)/%.cpp
	mkdir -p dst
	$(CXX) $(CFLAGS) -Ofast -march=native -std=c++14 -c -o $(DST)/$*.o $(SRC)/$*.cpp $(LDFLAGS)

clean:
	rm -f $(DST)/* $(BIN)/*
