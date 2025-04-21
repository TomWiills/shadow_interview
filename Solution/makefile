CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude -I/usr/include/python3.8

PYTHON_LIB := -L/usr/lib/python3.8/config-$(shell python3-config --configdir) -lpython3.8

SRC_DIR := source
OBJ_DIR := obj
BIN := solution

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: clean $(BIN) run

$(BIN): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BIN) $(PYTHON_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

run: $(BIN)
	./$(BIN)

.PHONY: all clean run
