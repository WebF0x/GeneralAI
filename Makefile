CXX = g++ # C++ Compiler
LD = g++ # Linker

INCLUDE = -Iinclude
CFLAGS = -g -std=c++14
OBJ_DIR = obj
BIN_DIR = bin

AI_SRC = source/AI
WORLD_SRC = source/World

LIB_TEST = lib/UnitTest++/Linux/libUnitTest++.a
OUT_TEST = $(BIN_DIR)/Test/Test

# Path to object files
OBJ_DIR_TEST = $(OBJ_DIR)/test/CerealTest.o \
	$(OBJ_DIR)/$(AI_SRC)/RandomAI/RandomAI.o \
	$(OBJ_DIR)/test/CaseBasedAITest.o \
	$(OBJ_DIR)/test/DarwinAITest.o \
	$(OBJ_DIR)/test/GeneralAITest.o \
	$(OBJ_DIR)/test/HumanAITest.o \
	$(OBJ_DIR)/test/NeuralNetAITest.o \
	$(OBJ_DIR)/test/RandomAITest.o \
	$(OBJ_DIR)/test/SanityTest.o \
	$(OBJ_DIR)/test/UtilityTest.o \
	$(OBJ_DIR)/test/main.o \
	$(OBJ_DIR)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o \
	$(OBJ_DIR)/$(AI_SRC)/HumanAI/HumanAI.o \
	$(OBJ_DIR)/$(AI_SRC)/GeneralAI/GeneralAI.o \
	$(OBJ_DIR)/$(AI_SRC)/DarwinAI/DarwinAI.o \
	$(OBJ_DIR)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o \
	$(OBJ_DIR)/source/Utility/Utility.o

all: test

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# If the object directory doesn't exist, create it
before_test: 
	@mkdir -p $(BIN_DIR)/Test
	@mkdir -p $(OBJ_DIR)/test
	@mkdir -p $(OBJ_DIR)/$(AI_SRC)/RandomAI
	@mkdir -p $(OBJ_DIR)/$(AI_SRC)/NeuralNetAI
	@mkdir -p $(OBJ_DIR)/$(AI_SRC)/HumanAI
	@mkdir -p $(OBJ_DIR)/$(AI_SRC)/GeneralAI
	@mkdir -p $(OBJ_DIR)/$(AI_SRC)/DarwinAI
	@mkdir -p $(OBJ_DIR)/$(AI_SRC)/CaseBasedAI
	@mkdir -p $(OBJ_DIR)/source/Utility/

after_test: 
	./$(BIN_DIR)/Test/Test

test: before_test out_test after_test

out_test: before_test $(OBJ_DIR_TEST)
	$(LD) -o $(OUT_TEST) $(OBJ_DIR_TEST) $(LIB_TEST)

# Tests
$(OBJ_DIR)/test/CerealTest.o: test/CerealTest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/CerealTest.cpp -o $(OBJ_DIR)/test/CerealTest.o

$(OBJ_DIR)/test/CaseBasedAITest.o: test/CaseBasedAITest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/CaseBasedAITest.cpp -o $(OBJ_DIR)/test/CaseBasedAITest.o

$(OBJ_DIR)/test/DarwinAITest.o: test/DarwinAITest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/DarwinAITest.cpp -o $(OBJ_DIR)/test/DarwinAITest.o

$(OBJ_DIR)/test/GeneralAITest.o: test/GeneralAITest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/GeneralAITest.cpp -o $(OBJ_DIR)/test/GeneralAITest.o

$(OBJ_DIR)/test/HumanAITest.o: test/HumanAITest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/HumanAITest.cpp -o $(OBJ_DIR)/test/HumanAITest.o

$(OBJ_DIR)/test/NeuralNetAITest.o: test/NeuralNetAITest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/NeuralNetAITest.cpp -o $(OBJ_DIR)/test/NeuralNetAITest.o

$(OBJ_DIR)/test/RandomAITest.o: test/RandomAITest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/RandomAITest.cpp -o $(OBJ_DIR)/test/RandomAITest.o

$(OBJ_DIR)/test/SanityTest.o: test/SanityTest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/SanityTest.cpp -o $(OBJ_DIR)/test/SanityTest.o

$(OBJ_DIR)/test/UtilityTest.o: test/UtilityTest.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/UtilityTest.cpp -o $(OBJ_DIR)/test/UtilityTest.o

$(OBJ_DIR)/test/main.o: test/main.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c test/main.cpp -o $(OBJ_DIR)/test/main.o

# AI's
$(OBJ_DIR)/$(AI_SRC)/RandomAI/RandomAI.o: $(AI_SRC)/RandomAI/RandomAI.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(AI_SRC)/RandomAI/RandomAI.cpp -o $(OBJ_DIR)/$(AI_SRC)/RandomAI/RandomAI.o

$(OBJ_DIR)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o: $(AI_SRC)/NeuralNetAI/NeuralNetAI.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(AI_SRC)/NeuralNetAI/NeuralNetAI.cpp -o $(OBJ_DIR)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o

$(OBJ_DIR)/$(AI_SRC)/HumanAI/HumanAI.o: $(AI_SRC)/HumanAI/HumanAI.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(AI_SRC)/HumanAI/HumanAI.cpp -o $(OBJ_DIR)/$(AI_SRC)/HumanAI/HumanAI.o

$(OBJ_DIR)/$(AI_SRC)/GeneralAI/GeneralAI.o: $(AI_SRC)/GeneralAI/GeneralAI.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(AI_SRC)/GeneralAI/GeneralAI.cpp -o $(OBJ_DIR)/$(AI_SRC)/GeneralAI/GeneralAI.o

$(OBJ_DIR)/$(AI_SRC)/DarwinAI/DarwinAI.o: $(AI_SRC)/DarwinAI/DarwinAI.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(AI_SRC)/DarwinAI/DarwinAI.cpp -o $(OBJ_DIR)/$(AI_SRC)/DarwinAI/DarwinAI.o

$(OBJ_DIR)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o: $(AI_SRC)/CaseBasedAI/CaseBasedAI.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $(AI_SRC)/CaseBasedAI/CaseBasedAI.cpp -o $(OBJ_DIR)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o

# Utility
$(OBJ_DIR)/source/Utility/Utility.o: source/Utility/Utility.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c source/Utility/Utility.cpp -o $(OBJ_DIR)/source/Utility/Utility.o

.PHONY: before_test after_test
