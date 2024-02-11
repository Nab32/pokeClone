CXX := g++ # Or clang++ if you prefer
CXXFLAGS := -std=c++11 -Iinclude
LDFLAGS := -Llib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)
EXEC := pokemon

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f src/*.o $(EXEC)
