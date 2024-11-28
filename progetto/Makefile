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
CXXFLAGS = -std=c++17 -I$(INC_DIR) -g -O0

# Trova tutti i file .cpp in src/ e li trasforma in file .o
SRC_FILES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT)) \
            $(wildcard $(SRC_DIR)/tools/*.$(SRC_EXT))
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.$(OBJ_EXT))

# Dipendenze aggiuntive
DEPS = $(OBJ_FILES:.o=.d)

# Regola di default (compila il programma finale)
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) -std=c++17 -O0 -o $@ $^

# Compilazione dei file .cpp in .o
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(dir $@) # Crea la directory completa
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# Genera file di dipendenze .d
$(OBJ_DIR)/tools/%.d: $(SRC_DIR)/tools/%.$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -i 's|^\($*\)\.o[ :]*|$(OBJ_DIR)/tools/\1.o $(OBJ_DIR)/tools/\1.d : |g' $@

# Genera file di dipendenze per i file in src/
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -i 's|^\($*\)\.o[ :]*|$(OBJ_DIR)/\1.o $(OBJ_DIR)/\1.d : |g' $@

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