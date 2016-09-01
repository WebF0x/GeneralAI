CXX = g++ # C++ Compiler
LD = g++ # Linker

INCLUDE = -Iinclude
CFLAGS = -g -std=c++14
OBJ_DIR = obj
BIN_DIR = bin

LIBRARIES_TESTS = lib/UnitTest++/Linux/libUnitTest++.a
LIBRARIES_ADDER =
EXECUTABLE_TESTS = $(BIN_DIR)/test/test
EXECUTABLE_ADDER = $(BIN_DIR)/adder/adder

SOURCES_TESTS = test/CerealTest.cpp \
	test/CaseBasedAITest.cpp \
	test/DarwinAITest.cpp \
	test/GeneralAITest.cpp \
	test/HumanAITest.cpp \
	test/NeuralNetAITest.cpp \
	test/RandomAITest.cpp \
	test/SanityTest.cpp \
	test/UtilityTest.cpp \
	test/main.cpp \
	source/AI/RandomAI/RandomAI.cpp \
	source/AI/NeuralNetAI/NeuralNetAI.cpp \
	source/AI/HumanAI/HumanAI.cpp \
	source/AI/GeneralAI/GeneralAI.cpp \
	source/AI/DarwinAI/DarwinAI.cpp \
	source/AI/CaseBasedAI/CaseBasedAI.cpp \
	source/Utility/Utility.cpp

SOURCES_ADDER = source/AI/NeuralNetAI/NeuralNetAI.cpp \
	source/AI/GeneralAI/GeneralAI.cpp \
	source/AI/DarwinAI/DarwinAI.cpp \
	source/Utility/Utility.cpp \
	source/World/Adder/main.cpp

OBJECTS_TESTS := $(SOURCES_TESTS:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS_ADDER := $(SOURCES_ADDER:%.cpp=$(OBJ_DIR)/%.o)

all: tests adder

tests: $(EXECUTABLE_TESTS)

$(EXECUTABLE_TESTS): $(OBJECTS_TESTS)
	@echo Linking: $@
	@mkdir -p $(@D)
	@$(LD) -o $@ $(OBJECTS_TESTS) $(LIBRARIES_TESTS)

adder: $(EXECUTABLE_ADDER)

$(EXECUTABLE_ADDER): $(OBJECTS_ADDER)
	@echo Linking: $@
	@mkdir -p $(@D)
	@$(LD) -o $@ $(OBJECTS_ADDER) $(LIBRARIES_ADDER)

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling: $@
	@mkdir -p $(@D)
	@ $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

DEPENDENCIES_TESTS := $(OBJECTS_TESTS:.o=.d)
-include $(DEPENDENCIES_TESTS)

DEPENDENCIES_ADDER := $(OBJECTS_ADDER:.o=.d)
-include $(DEPENDENCIES_ADDER)

clean:
	@echo Cleaning
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean tests all
