//---------------------------------------------------------------------
// Arquivo	: filadehosts.h
// Conteudo	: definicoes da fila de hosts 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------
#ifndef FILADEHOSTSH
#define FILADEHOSTSH

#include <string>
#include "listadeurls.h"

using namespace std;

// Celula da lista de hosts com um host, uma lista de URLs e um apontador para a próxima Celula
struct CelulaFilaDeHosts
{
    string host;
    ListaDeURLS item;
    CelulaFilaDeHosts* prox;

    // Construtor de uma Celula de Fila de Hosts
    CelulaFilaDeHosts(){
        this->item = ListaDeURLS();
        this->prox = NULL;
    }
    
};

class FilaDeHosts {
    public:
        FilaDeHosts();
        bool vazia();
        int getTamanho();
        string getHost(int pos);
        ListaDeURLS* getItem(int pos);
        ListaDeURLS removeInicio();
        void insereFinal(ListaDeURLS item, string host);
        void limpa();
    
    protected:
        int tamanho;
        CelulaFilaDeHosts* primeiro;
        CelulaFilaDeHosts* ultimo;
        CelulaFilaDeHosts* posiciona(int pos, bool antes);
};

#endif
