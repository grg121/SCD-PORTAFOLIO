SRC = src
INC = includes
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -ansi -pedantic -Wall -Wextra -Wwrite-strings  -g -c -std=c++0x -I$(INC)

all: $(BIN)/calculopi 

$(BIN)/calculopi: $(OBJ)/calculopi.o $(OBJ)/fun_tiempo.o
	$(CXX) $(OBJ)/calculopi.o $(OBJ)/fun_tiempo.o -o $(BIN)/calculopi  -lpthread

$(OBJ)/calculopi.o: $(SRC)/calculopi.cpp $(INC)/fun_tiempo.h
	$(CXX) $(CPPFLAGS) $(SRC)/calculopi.cpp -o $(OBJ)/calculopi.o
 
$(OBJ)/fun_tiempo.o: $(SRC)/fun_tiempo.c $(INC)/fun_tiempo.h 
	gcc -c -I$(INC) $(SRC)/fun_tiempo.c -o $(OBJ)/fun_tiempo.o 



