BIN = nuklear_sfml
CXXFLAGS = -std=c++14 -O2

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

LIBS = -lsfml-system -lsfml-graphics -lsfml-window -lGL

$(BIN):
	@mkdir -p bin
	rm -f bin/$(BIN) $(OBJS)
	$(CXX) $(SRC) $(CXXFLAGS) -o bin/$(BIN) $(LIBS)
