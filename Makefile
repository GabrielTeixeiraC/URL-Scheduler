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

OBJS = $(OBJ)/main.o $(OBJ)/escalonador.o $(OBJ)/listadehosts.o $(OBJ)/listaencadeada.o
HDRS = $(INC)/escalonador.h $(INC)/listadehosts.h $(INC)/listaencadeada.h

CXXFLAGS = -c -g -std=c++11 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CXX) -o $(BIN)/main $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/escalonador.o: $(HDRS) $(SRC)/escalonador.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/escalonador.o $(SRC)/escalonador.cpp

$(OBJ)/listadehosts.o: $(HDRS) $(SRC)/listadehosts.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/listadehosts.o $(SRC)/listadehosts.cpp

$(OBJ)/listaencadeada.o: $(HDRS) $(SRC)/listaencadeada.cpp
	$(CXX) $(CXXFLAGS) -o $(OBJ)/listaencadeada.o $(SRC)/listaencadeada.cpp
			
clean:
	rm $(EXE) $(OBJS)