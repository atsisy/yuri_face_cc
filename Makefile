CXX = g++
DST = ./dst
SRC = ./src
BIN = ./bin
INCLUDE = ./include
OBJS = $(DST)/dot.o $(DST)/geometry.o $(DST)/load_yfml.o $(DST)/object.o $(DST)/transform.o \
	$(DST)/yuriface2face.o $(DST)/face.o $(DST)/left_eye.o $(DST)/main.o \
	$(DST)/right_eye.o $(DST)/utility.o $(DST)/face_base.o $(DST)/left_eyebrows.o \
	$(DST)/mouth.o $(DST)/right_eyebrows.o $(DST)/yuriface.o
CFLAGS = `pkg-config --cflags opencv`
LDFLAGS = `pkg-config --libs opencv`

yfc: $(OBJS)
	$(CXX) -o $(BIN)/yfc $(OBJS) $(LDFLAGS)


$(DST)/%.o: $(SRC)/%.cpp
	mkdir -p $(DST)
	mkdir -p $(BIN)
	$(CXX) $(CFLAGS) -Ofast -march=native -std=c++14 -c -o $(DST)/$*.o $(SRC)/$*.cpp $(LDFLAGS) -I$(INCLUDE)

clean:
	rm -f $(DST)/*.o $(BIN)/*
