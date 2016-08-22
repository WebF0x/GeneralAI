CXX = g++
LD = g++

INC = -Iinclude
CFLAGS = -g -std=c++14
OBJ = obj
BIN = bin

AI_SRC = source/AI
WORLD_SRC = source/World

LIB_TEST = lib/UnitTest++/Linux/libUnitTest++.a
OUT_TEST = bin/Test/Test

OUT_DARWINTICTACTOE = bin/DarwinTicTacToe/DarwinTicTacToe

OUT_TICTACTOE = bin/TicTacToe/TicTacToe

# Path to object files
OBJ_TEST = $(OBJ)/test/CerealTest.o \
		   $(OBJ)/$(AI_SRC)/RandomAI/RandomAI.o \
		   $(OBJ)/test/CaseBasedAITest.o \
		   $(OBJ)/test/DarwinAITest.o \
		   $(OBJ)/test/GeneralAITest.o \
		   $(OBJ)/test/HumanAITest.o \
		   $(OBJ)/test/NeuralNetAITest.o \
		   $(OBJ)/test/RandomAITest.o \
		   $(OBJ)/test/SanityTest.o \
		   $(OBJ)/test/UtilityTest.o \
		   $(OBJ)/test/main.o \
		   $(OBJ)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o \
		   $(OBJ)/$(AI_SRC)/HumanAI/HumanAI.o \
		   $(OBJ)/$(AI_SRC)/GeneralAI/GeneralAI.o \
		   $(OBJ)/$(AI_SRC)/DarwinAI/DarwinAI.o \
		   $(OBJ)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o \
		   $(OBJ)/source/Utility/Utility.o

OBJ_DARWINTICTACTOE = $(OBJ)/$(AI_SRC)/RandomAI/RandomAI.o \
					  $(OBJ)/$(WORLD_SRC)/DarwinTicTacToe/TicTacToe.o \
					  $(OBJ)/$(WORLD_SRC)/DarwinTicTacToe/TicTacToeHuman.o \
					  $(OBJ)/$(WORLD_SRC)/DarwinTicTacToe/main.o \
					  $(OBJ)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o \
					  $(OBJ)/$(AI_SRC)/HumanAI/HumanAI.o \
					  $(OBJ)/$(AI_SRC)/GeneralAI/GeneralAI.o \
					  $(OBJ)/$(AI_SRC)/DarwinAI/DarwinAI.o

OBJ_TICTACTOE = $(OBJ)/$(WORLD_SRC)/TicTacToe/TicTacToeHuman.o \
				$(OBJ)/$(WORLD_SRC)/TicTacToe/main.o \
				$(OBJ)/$(AI_SRC)/HumanAI/HumanAI.o \
				$(OBJ)/$(AI_SRC)/GeneralAI/GeneralAI.o \
				$(OBJ)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o

all: test darwintictactoe tictactoe

clean:
	rm -rf $(OBJ) $(BIN)

# If the object directory doesn't exist, create it
before_test: 
	test -d bin/Test || mkdir -p bin/Test
	test -d $(OBJ)/test || mkdir -p $(OBJ)/test
	test -d $(OBJ)/$(AI_SRC)/RandomAI || mkdir -p $(OBJ)/$(AI_SRC)/RandomAI
	test -d $(OBJ)/$(AI_SRC)/NeuralNetAI || mkdir -p $(OBJ)/$(AI_SRC)/NeuralNetAI
	test -d $(OBJ)/$(AI_SRC)/HumanAI || mkdir -p $(OBJ)/$(AI_SRC)/HumanAI
	test -d $(OBJ)/$(AI_SRC)/GeneralAI || mkdir -p $(OBJ)/$(AI_SRC)/GeneralAI
	test -d $(OBJ)/$(AI_SRC)/DarwinAI || mkdir -p $(OBJ)/$(AI_SRC)/DarwinAI
	test -d $(OBJ)/$(AI_SRC)/CaseBasedAI || mkdir -p $(OBJ)/$(AI_SRC)/CaseBasedAI
	test -d $(OBJ)/source/Utility || mkdir -p $(OBJ)/source/Utility/

after_test: 
	./bin/Test/Test

test: before_test out_test after_test

out_test: before_test $(OBJ_TEST)
	$(LD) -o $(OUT_TEST) $(OBJ_TEST) $(LIB_TEST)

# Tests
$(OBJ)/test/CerealTest.o: test/CerealTest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/CerealTest.cpp -o $(OBJ)/test/CerealTest.o

$(OBJ)/test/CaseBasedAITest.o: test/CaseBasedAITest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/CaseBasedAITest.cpp -o $(OBJ)/test/CaseBasedAITest.o

$(OBJ)/test/DarwinAITest.o: test/DarwinAITest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/DarwinAITest.cpp -o $(OBJ)/test/DarwinAITest.o

$(OBJ)/test/GeneralAITest.o: test/GeneralAITest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/GeneralAITest.cpp -o $(OBJ)/test/GeneralAITest.o

$(OBJ)/test/HumanAITest.o: test/HumanAITest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/HumanAITest.cpp -o $(OBJ)/test/HumanAITest.o

$(OBJ)/test/NeuralNetAITest.o: test/NeuralNetAITest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/NeuralNetAITest.cpp -o $(OBJ)/test/NeuralNetAITest.o

$(OBJ)/test/RandomAITest.o: test/RandomAITest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/RandomAITest.cpp -o $(OBJ)/test/RandomAITest.o

$(OBJ)/test/SanityTest.o: test/SanityTest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/SanityTest.cpp -o $(OBJ)/test/SanityTest.o

$(OBJ)/test/UtilityTest.o: test/UtilityTest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/UtilityTest.cpp -o $(OBJ)/test/UtilityTest.o

$(OBJ)/test/main.o: test/main.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/main.cpp -o $(OBJ)/test/main.o

# AI's
$(OBJ)/$(AI_SRC)/RandomAI/RandomAI.o: $(AI_SRC)/RandomAI/RandomAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(AI_SRC)/RandomAI/RandomAI.cpp -o $(OBJ)/$(AI_SRC)/RandomAI/RandomAI.o

$(OBJ)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o: $(AI_SRC)/NeuralNetAI/NeuralNetAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(AI_SRC)/NeuralNetAI/NeuralNetAI.cpp -o $(OBJ)/$(AI_SRC)/NeuralNetAI/NeuralNetAI.o

$(OBJ)/$(AI_SRC)/HumanAI/HumanAI.o: $(AI_SRC)/HumanAI/HumanAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(AI_SRC)/HumanAI/HumanAI.cpp -o $(OBJ)/$(AI_SRC)/HumanAI/HumanAI.o

$(OBJ)/$(AI_SRC)/GeneralAI/GeneralAI.o: $(AI_SRC)/GeneralAI/GeneralAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(AI_SRC)/GeneralAI/GeneralAI.cpp -o $(OBJ)/$(AI_SRC)/GeneralAI/GeneralAI.o

$(OBJ)/$(AI_SRC)/DarwinAI/DarwinAI.o: $(AI_SRC)/DarwinAI/DarwinAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(AI_SRC)/DarwinAI/DarwinAI.cpp -o $(OBJ)/$(AI_SRC)/DarwinAI/DarwinAI.o

$(OBJ)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o: $(AI_SRC)/CaseBasedAI/CaseBasedAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(AI_SRC)/CaseBasedAI/CaseBasedAI.cpp -o $(OBJ)/$(AI_SRC)/CaseBasedAI/CaseBasedAI.o

# Utility
$(OBJ)/source/Utility/Utility.o: source/Utility/Utility.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/Utility/Utility.cpp -o $(OBJ)/source/Utility/Utility.o

before_darwintictactoe: 
	test -d bin/DarwinTicTacToe || mkdir -p bin/DarwinTicTacToe
	test -d $(OBJ)/$(AI_SRC)/RandomAI || mkdir -p $(OBJ)/$(AI_SRC)/RandomAI
	test -d $(OBJ)/$(WORLD_SRC)/DarwinTicTacToe || mkdir -p $(OBJ)/$(WORLD_SRC)/DarwinTicTacToe
	test -d $(OBJ)/$(AI_SRC)/NeuralNetAI || mkdir -p $(OBJ)/$(AI_SRC)/NeuralNetAI
	test -d $(OBJ)/$(AI_SRC)/HumanAI || mkdir -p $(OBJ)/$(AI_SRC)/HumanAI
	test -d $(OBJ)/$(AI_SRC)/GeneralAI || mkdir -p $(OBJ)/$(AI_SRC)/GeneralAI
	test -d $(OBJ)/$(AI_SRC)/DarwinAI || mkdir -p $(OBJ)/$(AI_SRC)/DarwinAI

after_darwintictactoe: 

darwintictactoe: before_darwintictactoe out_darwintictactoe after_darwintictactoe

out_darwintictactoe: before_darwintictactoe $(OBJ_DARWINTICTACTOE)
	$(LD) -o $(OUT_DARWINTICTACTOE) $(OBJ_DARWINTICTACTOE)

before_tictactoe: 
	test -d bin/TicTacToe || mkdir -p bin/TicTacToe
	test -d $(OBJ)/$(WORLD_SRC)/TicTacToe || mkdir -p $(OBJ)/$(WORLD_SRC)/TicTacToe
	test -d $(OBJ)/$(AI_SRC)/HumanAI || mkdir -p $(OBJ)/$(AI_SRC)/HumanAI
	test -d $(OBJ)/$(AI_SRC)/GeneralAI || mkdir -p $(OBJ)/$(AI_SRC)/GeneralAI
	test -d $(OBJ)/$(AI_SRC)/CaseBasedAI || mkdir -p $(OBJ)/$(AI_SRC)/CaseBasedAI

after_tictactoe: 

tictactoe: before_tictactoe out_tictactoe after_tictactoe

out_tictactoe: before_tictactoe $(OBJ_TICTACTOE)
	$(LD) -o $(OUT_TICTACTOE) $(OBJ_TICTACTOE)

$(OBJ)/$(WORLD_SRC)/TicTacToe/TicTacToeHuman.o: $(WORLD_SRC)/TicTacToe/TicTacToeHuman.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(WORLD_SRC)/TicTacToe/TicTacToeHuman.cpp -o $(OBJ)/$(WORLD_SRC)/TicTacToe/TicTacToeHuman.o

$(OBJ)/$(WORLD_SRC)/TicTacToe/main.o: $(WORLD_SRC)/TicTacToe/main.cpp
	$(CXX) $(CFLAGS) $(INC) -c $(WORLD_SRC)/TicTacToe/main.cpp -o $(OBJ)/$(WORLD_SRC)/TicTacToe/main.o

.PHONY: before_test after_test before_darwintictactoe after_darwintictactoe before_tictactoe after_tictactoe
