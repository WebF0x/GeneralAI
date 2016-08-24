CXX = g++ # C++ Compiler
LD = g++ # Linker

INCLUDE = -Iinclude
CFLAGS = -g -std=c++14
OBJ_DIR = obj
BIN_DIR = bin

AI_SRC = source/AI
WORLD_SRC = source/World

LIBRARIES = lib/UnitTest++/Linux/libUnitTest++.a
EXECUTABLE = $(BIN_DIR)/Test/Test

# Path to object files
OBJECTS = $(OBJ_DIR)/test/CerealTest.o \
	$(OBJ_DIR)/test/CaseBasedAITest.o \
	$(OBJ_DIR)/test/DarwinAITest.o \
	$(OBJ_DIR)/test/GeneralAITest.o \
	$(OBJ_DIR)/test/HumanAITest.o \
	$(OBJ_DIR)/test/NeuralNetAITest.o \
	$(OBJ_DIR)/test/RandomAITest.o \
	$(OBJ_DIR)/test/SanityTest.o \
	$(OBJ_DIR)/test/UtilityTest.o \
	$(OBJ_DIR)/test/main.o \
	$(OBJ_DIR)/$(AI_SRC)/RandomAI/RandomAI.o \
	$(OBJ_DIR)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o \
	$(OBJ_DIR)/$(AI_SRC)/HumanAI/HumanAI.o \
	$(OBJ_DIR)/$(AI_SRC)/GeneralAI/GeneralAI.o \
	$(OBJ_DIR)/$(AI_SRC)/DarwinAI/DarwinAI.o \
	$(OBJ_DIR)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o \
	$(OBJ_DIR)/source/Utility/Utility.o

DEPENDENCIES := $(OBJECTS:.o=.d)

all: test

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
	./$(EXECUTABLE)

test: before_test out_test after_test

out_test: before_test $(OBJECTS)
	$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LIBRARIES)

$(OBJ_DIR)/test/%.o: test/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/AI/RandomAI/%.o: source/AI/RandomAI/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/AI/NeuralNetAI/%.o: source/AI/NeuralNetAI/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/AI/HumanAI/%.o: source/AI/HumanAI/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/AI/GeneralAI/%.o: source/AI/GeneralAI/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/AI/DarwinAI/%.o: source/AI/DarwinAI/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/AI/CaseBasedAI/%.o: source/AI/CaseBasedAI/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

$(OBJ_DIR)/source/Utility/%.o: source/Utility/%.cpp
	 $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

-include $(DEPENDENCIES)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: before_test after_test
