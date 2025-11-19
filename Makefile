# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I .

# Détection automatique des fichiers
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = main

# Règle principale
all: $(TARGET)

# Link final
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) -lX11 -lpthread

# Compilation générique de tous les .cpp
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage Windows
clean:

	rm -rf *.o main


