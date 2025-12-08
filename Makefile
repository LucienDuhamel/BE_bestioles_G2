# Compilateur
CXX = g++

# Dossiers
SRC_DIR = src
INC_DIR = includes

# --- AJOUT : Détection de Gnuplot ---
# La commande 'shell which' renvoie le chemin si trouvé, sinon vide.
HAS_GNUPLOT := $(shell which gnuplot 2> /dev/null)

# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++17 -I $(INC_DIR) -fsanitize=address,undefined -g

# Fichiers sources et objets
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Nom de l'exécutable
TARGET = main

# Règle principale
# --- MODIFICATION : On ajoute 'check_deps' avant de construire $(TARGET) ---
all: check_deps $(TARGET)

# --- AJOUT : Règle de vérification ---
check_deps:
ifndef HAS_GNUPLOT
	@echo "========================================================================"
	@echo "⚠️  ATTENTION : Gnuplot n'est pas détecté."
	@echo "   La simulation se lancera sans graphiques."
	@echo "   Pour les activer : sudo apt install gnuplot-x11"
	@echo "========================================================================"
else
	@echo "✅ Gnuplot détecté. Graphiques activés."
endif

# Edition de liens
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) -lX11 -lpthread -fsanitize=address,undefined -g

# Compilation des .cpp vers .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
