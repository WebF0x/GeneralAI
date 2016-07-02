#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#

CXX = g++
LD = g++

INC = -Iinclude
CFLAGS = -g -std=c++14
OBJ = obj
BIN = bin

LIB_TEST = lib/UnitTest++/Linux/libUnitTest++.a
OUT_TEST = bin/Test/Test

OUT_DARWINTICTACTOE = bin/DarwinTicTacToe/DarwinTicTacToe

OUT_TICTACTOE = bin/TicTacToe/TicTacToe

# Path to object files
OBJ_TEST = $(OBJ)/test/CerealTest.o \
		   $(OBJ)/source/StrongAI/AI/RandomAI/RandomAI.o \
		   $(OBJ)/test/CaseBasedAITest.o \
		   $(OBJ)/test/DarwinAITest.o \
		   $(OBJ)/test/GeneralAITest.o \
		   $(OBJ)/test/HumanAITest.o \
		   $(OBJ)/test/NeuralNetAITest.o \
		   $(OBJ)/test/RandomAITest.o \
		   $(OBJ)/test/SanityTest.o \
		   $(OBJ)/test/UtilityTest.o \
		   $(OBJ)/test/main.o \
		   $(OBJ)/source/StrongAI/AI/NeuralNetAI/NeuralNetAI.o \
		   $(OBJ)/source/StrongAI/AI/HumanAI/HumanAI.o \
		   $(OBJ)/source/StrongAI/AI/GeneralAI/GeneralAI.o \
		   $(OBJ)/source/StrongAI/AI/DarwinAI/DarwinAI.o \
		   $(OBJ)/source/StrongAI/AI/CaseBasedAI/CaseBasedAI.o \
		   $(OBJ)/source/Utility/Utility.o

OBJ_DARWINTICTACTOE = $(OBJ)/source/StrongAI/AI/RandomAI/RandomAI.o \
					  $(OBJ)/source/StrongAI/World/DarwinTicTacToe/TicTacToe.o \
					  $(OBJ)/source/StrongAI/World/DarwinTicTacToe/TicTacToeHuman.o \
					  $(OBJ)/source/StrongAI/World/DarwinTicTacToe/main.o \
					  $(OBJ)/source/StrongAI/AI/NeuralNetAI/NeuralNetAI.o \
					  $(OBJ)/source/StrongAI/AI/HumanAI/HumanAI.o \
					  $(OBJ)/source/StrongAI/AI/GeneralAI/GeneralAI.o \
					  $(OBJ)/source/StrongAI/AI/DarwinAI/DarwinAI.o

OBJ_TICTACTOE = $(OBJ)/source/StrongAI/World/TicTacToe/TicTacToeHuman.o \
				$(OBJ)/source/StrongAI/World/TicTacToe/main.o \
				$(OBJ)/source/StrongAI/AI/HumanAI/HumanAI.o \
				$(OBJ)/source/StrongAI/AI/GeneralAI/GeneralAI.o \
				$(OBJ)/source/StrongAI/AI/CaseBasedAI/CaseBasedAI.o

all: test darwintictactoe tictactoe

clean:
	rm -rf $(OBJ) $(BIN)

# If the object directory doesn't exist, create it
before_test: 
	test -d bin/Test || mkdir -p bin/Test
	test -d $(OBJ)/test || mkdir -p $(OBJ)/test
	test -d $(OBJ)/source/StrongAI/AI/RandomAI || mkdir -p $(OBJ)/source/StrongAI/AI/RandomAI
	test -d $(OBJ)/source/StrongAI/AI/NeuralNetAI || mkdir -p $(OBJ)/source/StrongAI/AI/NeuralNetAI
	test -d $(OBJ)/source/StrongAI/AI/HumanAI || mkdir -p $(OBJ)/source/StrongAI/AI/HumanAI
	test -d $(OBJ)/source/StrongAI/AI/GeneralAI || mkdir -p $(OBJ)/source/StrongAI/AI/GeneralAI
	test -d $(OBJ)/source/StrongAI/AI/DarwinAI || mkdir -p $(OBJ)/source/StrongAI/AI/DarwinAI
	test -d $(OBJ)/source/StrongAI/AI/CaseBasedAI || mkdir -p $(OBJ)/source/StrongAI/AI/CaseBasedAI
	test -d $(OBJ)/source/Utility || mkdir -p $(OBJ)/source/Utility/

after_test: 
	./bin/Test/Test

test: before_test out_test after_test

out_test: before_test $(OBJ_TEST)
	$(LD) -o $(OUT_TEST) $(OBJ_TEST) $(LIB_TEST)

$(OBJ)/test/CerealTest.o: test/CerealTest.cpp
	$(CXX) $(CFLAGS) $(INC) -c test/CerealTest.cpp -o $(OBJ)/test/CerealTest.o

$(OBJ)/source/StrongAI/AI/RandomAI/RandomAI.o: source/StrongAI/AI/RandomAI/RandomAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/AI/RandomAI/RandomAI.cpp -o $(OBJ)/source/StrongAI/AI/RandomAI/RandomAI.o

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

$(OBJ)/source/StrongAI/AI/NeuralNetAI/NeuralNetAI.o: source/StrongAI/AI/NeuralNetAI/NeuralNetAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/AI/NeuralNetAI/NeuralNetAI.cpp -o $(OBJ)/source/StrongAI/AI/NeuralNetAI/NeuralNetAI.o

$(OBJ)/source/StrongAI/AI/HumanAI/HumanAI.o: source/StrongAI/AI/HumanAI/HumanAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/AI/HumanAI/HumanAI.cpp -o $(OBJ)/source/StrongAI/AI/HumanAI/HumanAI.o

$(OBJ)/source/StrongAI/AI/GeneralAI/GeneralAI.o: source/StrongAI/AI/GeneralAI/GeneralAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/AI/GeneralAI/GeneralAI.cpp -o $(OBJ)/source/StrongAI/AI/GeneralAI/GeneralAI.o

$(OBJ)/source/StrongAI/AI/DarwinAI/DarwinAI.o: source/StrongAI/AI/DarwinAI/DarwinAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/AI/DarwinAI/DarwinAI.cpp -o $(OBJ)/source/StrongAI/AI/DarwinAI/DarwinAI.o

$(OBJ)/source/StrongAI/AI/CaseBasedAI/CaseBasedAI.o: source/StrongAI/AI/CaseBasedAI/CaseBasedAI.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/AI/CaseBasedAI/CaseBasedAI.cpp -o $(OBJ)/source/StrongAI/AI/CaseBasedAI/CaseBasedAI.o

$(OBJ)/source/Utility/Utility.o: source/Utility/Utility.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/Utility/Utility.cpp -o $(OBJ)/source/Utility/Utility.o

before_darwintictactoe: 
	test -d bin/DarwinTicTacToe || mkdir -p bin/DarwinTicTacToe
	test -d $(OBJ)/source/StrongAI/AI/RandomAI || mkdir -p $(OBJ)/source/StrongAI/AI/RandomAI
	test -d $(OBJ)/source/StrongAI/World/DarwinTicTacToe || mkdir -p $(OBJ)/source/StrongAI/World/DarwinTicTacToe
	test -d $(OBJ)/source/StrongAI/AI/NeuralNetAI || mkdir -p $(OBJ)/source/StrongAI/AI/NeuralNetAI
	test -d $(OBJ)/source/StrongAI/AI/HumanAI || mkdir -p $(OBJ)/source/StrongAI/AI/HumanAI
	test -d $(OBJ)/source/StrongAI/AI/GeneralAI || mkdir -p $(OBJ)/source/StrongAI/AI/GeneralAI
	test -d $(OBJ)/source/StrongAI/AI/DarwinAI || mkdir -p $(OBJ)/source/StrongAI/AI/DarwinAI

after_darwintictactoe: 

darwintictactoe: before_darwintictactoe out_darwintictactoe after_darwintictactoe

out_darwintictactoe: before_darwintictactoe $(OBJ_DARWINTICTACTOE)
	$(LD) -o $(OUT_DARWINTICTACTOE) $(OBJ_DARWINTICTACTOE)

before_tictactoe: 
	test -d bin/TicTacToe || mkdir -p bin/TicTacToe
	test -d $(OBJ)/source/StrongAI/World/TicTacToe || mkdir -p $(OBJ)/source/StrongAI/World/TicTacToe
	test -d $(OBJ)/source/StrongAI/AI/HumanAI || mkdir -p $(OBJ)/source/StrongAI/AI/HumanAI
	test -d $(OBJ)/source/StrongAI/AI/GeneralAI || mkdir -p $(OBJ)/source/StrongAI/AI/GeneralAI
	test -d $(OBJ)/source/StrongAI/AI/CaseBasedAI || mkdir -p $(OBJ)/source/StrongAI/AI/CaseBasedAI

after_tictactoe: 

tictactoe: before_tictactoe out_tictactoe after_tictactoe

out_tictactoe: before_tictactoe $(OBJ_TICTACTOE)
	$(LD) -o $(OUT_TICTACTOE) $(OBJ_TICTACTOE)

$(OBJ)/source/StrongAI/World/TicTacToe/TicTacToeHuman.o: source/StrongAI/World/TicTacToe/TicTacToeHuman.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/World/TicTacToe/TicTacToeHuman.cpp -o $(OBJ)/source/StrongAI/World/TicTacToe/TicTacToeHuman.o

$(OBJ)/source/StrongAI/World/TicTacToe/main.o: source/StrongAI/World/TicTacToe/main.cpp
	$(CXX) $(CFLAGS) $(INC) -c source/StrongAI/World/TicTacToe/main.cpp -o $(OBJ)/source/StrongAI/World/TicTacToe/main.o

.PHONY: before_test after_test before_darwintictactoe after_darwintictactoe before_tictactoe after_tictactoe
