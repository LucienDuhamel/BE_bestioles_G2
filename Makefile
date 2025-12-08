# Compilateur
CXX = g++

# Dossiers
SRC_DIR = src
INC_DIR = includes

# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++17 -I $(INC_DIR) -fsanitize=address,undefined -g

# Fichiers sources et objets
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Nom de l'exécutable
TARGET = main

# Règle principale
all: $(TARGET)

# Edition de liens
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) -lX11 -lpthread -fsanitize=address,undefined -g

# Compilation des .cpp vers .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

