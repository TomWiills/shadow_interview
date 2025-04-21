CXX := g++
#get whatever py version the machine is running
# Get the Python version (major.minor)
PYTHON_VERSION := $(shell python3 -c "import sys; print(f'{sys.version_info[0]}.{sys.version_info[1]}')")
CXXFLAGS := -std=c++17 -Wall -Iinclude -I/usr/include/python$(PYTHON_VERSION) -I$(shell python3 -c "import numpy; print(numpy.get_include())")
PYTHON_LIB := -L/usr/lib/python$(PYTHON_VERSION)/config-$(shell python3-config --configdir) -lpython$(PYTHON_VERSION)

SRC_DIR := source
OUT_DIR := output
OBJ_DIR := $(OUT_DIR)/obj
BIN_DIR := $(OUT_DIR)/bin
BIN := $(BIN_DIR)/solution
SOURCES := $(SRC_DIR)/*.cpp
OBJECTS := $(OBJ_DIR)/solution.o

TEST_DIR := tests
TEST_BIN := $(BIN_DIR)/test_solution
TEST_SOURCES := $(TEST_DIR)/test_solution.cpp
TEST_OBJECTS := $(OBJ_DIR)/test_solution.o
GTEST_DIR := $(TEST_DIR)/third_party/googletest
GTEST_LIB_DIR := $(GTEST_DIR)/build/lib

all: clean $(BIN) run

$(BIN): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(BIN) $(PYTHON_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf output

run: $(BIN)
	./$(BIN)

# Test compilations
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/googletest/include -c $< -o $@

$(OBJ_DIR)/solution_test.o: $(SRC_DIR)/solution.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -DUNIT_TESTING -c $< -o $@

# Build GoogleTest from the submodule
$(GTEST_LIB_DIR)/libgtest.a:
	@if [ ! -f $(GTEST_DIR)/CMakeLists.txt ]; then \
		echo "ERROR: Gtest submodule missing, please run: git submodule update --init --recursive"; \
		exit 1; \
	fi
	@mkdir -p $(GTEST_DIR)/build
	cd $(GTEST_DIR)/build && cmake ..
	cd $(GTEST_DIR)/build && make

test: clean $(GTEST_LIB_DIR)/libgtest.a $(TEST_OBJECTS) $(OBJ_DIR)/solution_test.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(TEST_OBJECTS) $(OBJ_DIR)/solution_test.o -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -pthread $(PYTHON_LIB) -o $(TEST_BIN)
	./$(TEST_BIN)

.PHONY: all clean run test