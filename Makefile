#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main
# Autor		: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
# Histórico	: 2021-11-23 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CXX = g++

BIN = bin
SRC = src
OBJ = obj
INC = include

OBJS = $(OBJ)/main.o $(OBJ)/escalonador.o $(OBJ)/filadehosts.o $(OBJ)/listadeurls.o
HDRS = $(INC)/escalonador.h $(INC)/filadehosts.h $(INC)/listadeurls.h

CXXFLAGS = -c -g -std=c++11 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CXX) -o $(BIN)/main $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/escalonador.o: $(HDRS) $(SRC)/escalonador.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/escalonador.o $(SRC)/escalonador.cpp

$(OBJ)/filadehosts.o: $(HDRS) $(SRC)/filadehosts.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/filadehosts.o $(SRC)/filadehosts.cpp

$(OBJ)/listadeurls.o: $(HDRS) $(SRC)/listadeurls.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/listadeurls.o $(SRC)/listadeurls.cpp
			
clean:
	rm $(EXE) $(OBJS)