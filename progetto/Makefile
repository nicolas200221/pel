# Nome del programma finale
TARGET = pel

# Cartelle
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Estensioni dei file
SRC_EXT = cpp
OBJ_EXT = o

# Flag per il compilatore
CXX = g++
CXXFLAGS = -std=c++17 -I$(INC_DIR) -g

# Trova tutti i file .cpp in src/ e li trasforma in file .o
SRC_FILES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.$(OBJ_EXT))

# Dipendenze aggiuntive
DEPS = $(OBJ_FILES:.o=.d)

# Regola di default (compila il programma finale)
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "Compilando il target finale $(TARGET)"
	$(CXX) -o $@ $^

# Compilazione dei file .cpp in .o
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@echo "Compilando $< in $@"
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) -o $@ $<
	@echo "Compilato $@"

# Genera file di dipendenze .d
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.$(SRC_EXT)
	@echo "Generando dipendenze per $<"
	@mkdir -p $(OBJ_DIR)
	$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -i 's|\($*\)\.o[ :]*|$(OBJ_DIR)/\1.o $(OBJ_DIR)/\1.d : |g' $@
	@echo "Dipendenze per $< generate in $@"

# Includi i file di dipendenze
-include $(DEPS)

# Pulizia dei file generati
clean:
	@echo "Pulizia dei file generati..."
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
	@if [ -f $(TARGET).exe ]; then rm $(TARGET).exe; fi
	@echo "Pulizia completata."

# Se vuoi ricompilare tutto da zero
rebuild: clean all

.PHONY: all clean rebuild
