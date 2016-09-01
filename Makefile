# Build settings
CXX = g++ # C++ Compiler
LD = g++ # Linker
INCLUDE = -Iinclude
CFLAGS = -g -std=c++14
OBJ_DIR = obj
BIN_DIR = bin

# Libraries
LIBRARIES_TESTS = lib/UnitTest++/Linux/libUnitTest++.a
LIBRARIES_ADDER =

# Executable path
EXECUTABLE_TESTS = $(BIN_DIR)/test/test
EXECUTABLE_ADDER = $(BIN_DIR)/adder/adder

# Source files
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

# Objects
OBJECTS_TESTS := $(SOURCES_TESTS:%.cpp=$(OBJ_DIR)/%.o)
OBJECTS_ADDER := $(SOURCES_ADDER:%.cpp=$(OBJ_DIR)/%.o)

# Build targets
all: tests adder
tests: $(EXECUTABLE_TESTS)
adder: $(EXECUTABLE_ADDER)

# Link executable
$(EXECUTABLE_TESTS): $(OBJECTS_TESTS)
	@echo Linking: $@
	@mkdir -p $(@D)
	@$(LD) -o $@ $^ $(LIBRARIES_TESTS)

$(EXECUTABLE_ADDER): $(OBJECTS_ADDER)
	@echo Linking: $@
	@mkdir -p $(@D)
	@$(LD) -o $@ $^ $(LIBRARIES_ADDER)

# Compile only if a dependency was modified
DEPENDENCIES_TESTS := $(OBJECTS_TESTS:.o=.d)
DEPENDENCIES_ADDER := $(OBJECTS_ADDER:.o=.d)
-include $(DEPENDENCIES_TESTS)
-include $(DEPENDENCIES_ADDER)

# Rule to compile any object
$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling: $@
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

# Erase generated files
clean:
	@echo Cleaning
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Tell 'make' these rules do not have a corresponding file
# Without this, an unrelated file with the same name as the build rule could prevent from building
.PHONY: clean all tests adder
