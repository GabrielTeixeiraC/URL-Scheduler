//---------------------------------------------------------------------
// Arquivo	: escalonador.h
// Conteudo	: definicoes do escalonador 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------
#ifndef ESCALONADORH
#define ESCALONADORH

#include <string>
#include <fstream>
#include "listaencadeada.h"
#include "listadehosts.h"
using namespace std;

class Escalonador {
    private:
        ListaDeHosts coletor;
    public:
        Escalonador();
        void addUrls(int quantidade, string url);
        void escalonaTudo(ofstream& arquivoDeSaida);
        void escalona(int quantidade, ofstream& arquivoDeSaida);
        void escalonaHost(string host, int quantidade, ofstream& arquivoDeSaida);
        void verHost(string host, ofstream& arquivoDeSaida);
        void listaHosts(ofstream& arquivoDeSaida);
        void limpaHost(string host);
        void limpaTudo();
};



#endif
