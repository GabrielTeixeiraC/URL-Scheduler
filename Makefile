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
TMP = tmp
INC = include

OBJS = $(OBJ)/main.o $(OBJ)/escalonador.o $(OBJ)/filadehosts.o $(OBJ)/listadeurls.o $(OBJ)/memlog.o
HDRS = $(INC)/escalonador.h $(INC)/filadehosts.h $(INC)/listadeurls.h $(INC)/memlog.h

CXXFLAGS = -c -std=c++11 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS) | $(BIN)
	$(CXX) -o $(BIN)/main $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp | $(OBJ) $(TMP)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/escalonador.o: $(HDRS) $(SRC)/escalonador.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/escalonador.o $(SRC)/escalonador.cpp

$(OBJ)/filadehosts.o: $(HDRS) $(SRC)/filadehosts.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/filadehosts.o $(SRC)/filadehosts.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c | $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c

$(OBJ)/listadeurls.o: $(HDRS) $(SRC)/listadeurls.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/listadeurls.o $(SRC)/listadeurls.cpp
		
$(BIN):
	mkdir $(BIN)

$(OBJ):
	mkdir $(OBJ)

$(TMP):
	mkdir $(TMP)

clean:
	rm $(BIN) $(OBJ) $(TMP) -rf