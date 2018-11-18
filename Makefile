SRC_DIR = ./src
TEST_SRC_DIR = ./testbench_src
OBJ_DIR = ./obj
BIN_DIR = ./bin
PARSE_DIR = ./parser
TST_DIR = ./tests

SIM_NAME = mips_simulator
SIM_OUT = $(BIN_DIR)/$(SIM_NAME)

TEST_NAME = mips_testbench
BINGEN_NAME = mips_bingen
TEST_OUT = $(BIN_DIR)/$(TEST_NAME)

TST_FILES = $(TEST_SRC_DIR)/tests/*.meta
TST_DATA = $(TEST_SRC_DIR)/tests/*.txt
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -O3 -mavx

simulator: $(SIM_OUT)

parser:
	make -C $(PARSE_DIR)

testbench: parser
	mkdir -p $(BIN_DIR)
	mkdir -p $(TST_DIR)
	cp $(TEST_SRC_DIR)/$(TEST_NAME) $(BIN_DIR)/$(TEST_NAME)
	cp -r $(TST_FILES) $(TST_DIR)
	cp -r $(TST_DATA) $(TST_DIR)
	$(TEST_SRC_DIR)/$(BINGEN_NAME) $(TST_DIR)

run_tests: simulator testbench
	clear
	$(TEST_OUT) $(SIM_OUT) | column -t -s, | grep -E --color=auto 'Fail|$$'

$(SIM_OUT): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean parser testbench
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(TST_DIR)
	make -C $(PARSE_DIR) clean