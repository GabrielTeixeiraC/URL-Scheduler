//---------------------------------------------------------------------
// Arquivo	: listadehosts.h
// Conteudo	: definicoes do listadehosts 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------
#ifndef LISTASDEHOSTSH
#define LISTASDEHOSTSH

#include <string>
#include "listaencadeada.h"

using namespace std;

struct CelulaListaDeHosts
{
    string host;
    ListaEncadeada item;
    CelulaListaDeHosts* prox;

    CelulaListaDeHosts(){
        this->item = ListaEncadeada();
        this->prox = NULL;
    }
    
};

class ListaDeHosts {
    public:
        ListaDeHosts();
        // ~ListaDeHosts();
        bool vazia();
        int getTamanho();
        string getHost(int pos);
        ListaEncadeada* getItem(int pos);
        void setItem(ListaEncadeada item, int pos);
        void insereInicio(ListaEncadeada item);
        void insereFinal(ListaEncadeada item, string host);
        void inserePosicao(ListaEncadeada item, int pos);
        ListaEncadeada removeInicio();
        ListaEncadeada removePosicao(int pos);
        void imprime();
        void limpa();
    
    protected:
        int tamanho;
        CelulaListaDeHosts* primeiro;
        CelulaListaDeHosts* ultimo;
        CelulaListaDeHosts* posiciona(int pos, bool antes);
};

#endif
