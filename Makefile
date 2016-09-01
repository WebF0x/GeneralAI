CXX = g++ # C++ Compiler
LD = g++ # Linker

INCLUDE = -Iinclude
CFLAGS = -g -std=c++14
OBJ_DIR = obj
BIN_DIR = bin

LIBRARIES = lib/UnitTest++/Linux/libUnitTest++.a
LIBRARIES_ADDER =
EXECUTABLE = $(BIN_DIR)/test/test
EXECUTABLE_ADDER = $(BIN_DIR)/adder/adder

SOURCES = test/CerealTest.cpp \
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

OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS_ADDER := $(SOURCES_ADDER:%.cpp=$(OBJ_DIR)/%.o)

all: tests adder

tests: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking: $@
	@mkdir -p $(@D)
	@$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LIBRARIES)

adder: $(EXECUTABLE_ADDER)

$(EXECUTABLE_ADDER): $(OBJECTS_ADDER)
	@echo Linking: $@
	@mkdir -p $(@D)
	@$(LD) -o $(EXECUTABLE_ADDER) $(OBJECTS_ADDER) $(LIBRARIES_ADDER)

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling: $@
	@mkdir -p $(@D)
	@ $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

DEPENDENCIES := $(OBJECTS:.o=.d)
-include $(DEPENDENCIES)

clean:
	@echo Cleaning
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean tests all
