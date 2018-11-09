SRC_DIR = ./src
TEST_SRC_DIR = ./testbench_src
OBJ_DIR = ./obj
BIN_DIR = ./bin

SIM_NAME = mips_simulator
SIM_OUT = $(BIN_DIR)/$(SIM_NAME)

TEST_NAME = mips_testbench
TEST_OUT = $(BIN_DIR)/$(TEST_NAME)

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -O3 -mavx

simulator: $(SIM_OUT)

testbench:
	mkdir -p $(BIN_DIR)
	cp -R $(TEST_SRC_DIR)/. $(BIN_DIR)/

run_tests: simulator testbench
	clear
	$(TEST_OUT) $(SIM_OUT) | column -t -s, | grep -E --color=auto 'Fail|$$'

$(SIM_OUT): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -r -f $(OBJ_DIR)
	rm -r -f $(BIN_DIR)