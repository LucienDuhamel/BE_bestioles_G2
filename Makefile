# Compilateur
CXX = g++
INCLUDES = -Iincludes
CXXFLAGS = -Wall -Wextra -std=c++17 $(INCLUDES)

# Trouve automatiquement tous les fichiers .cpp
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Nom de l’exécutable
EXEC = lauch_simulation

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle générique : comment transformer un .cpp en .o
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)

.PHONY: all clean

