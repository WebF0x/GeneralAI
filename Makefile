CXX = g++ # C++ Compiler
LD = g++ # Linker

INCLUDE = -Iinclude
CFLAGS = -g -std=c++14
OBJ_DIR = obj
BIN_DIR = bin

AI_SRC = source/AI
WORLD_SRC = source/World

LIBRARIES = lib/UnitTest++/Linux/libUnitTest++.a
EXECUTABLE = $(BIN_DIR)/test/test

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

all: runtests

runtests: $(EXECUTABLE)
	@echo Running tests
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking
	@mkdir -p $(@D)
	@$(LD) -o $(EXECUTABLE) $(OBJECTS) $(LIBRARIES)

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling: $@
	@mkdir -p $(@D)
	@ $(CXX) $(CFLAGS) $(INCLUDE) -c -MMD -o $@ $<

DEPENDENCIES := $(OBJECTS:.o=.d)
-include $(DEPENDENCIES)

clean:
	@echo Cleaning
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean runtests all
