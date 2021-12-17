//---------------------------------------------------------------------
// Arquivo	: listadehosts.h
// Conteudo	: definicoes do listadehosts 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------
#ifndef LISTASDEHOSTSH
#define LISTASDEHOSTSH

#include <string>
#include "listadeurls.h"

using namespace std;

struct CelulaListaDeHosts
{
    string host;
    ListaDeURLS item;
    CelulaListaDeHosts* prox;

    CelulaListaDeHosts(){
        this->item = ListaDeURLS();
        this->prox = NULL;
    }
    
};

class ListaDeHosts {
    public:
        ListaDeHosts();
        bool vazia();
        int getTamanho();
        string getHost(int pos);
        ListaDeURLS* getItem(int pos);
        void setItem(ListaDeURLS item, int pos);
        void insereInicio(ListaDeURLS item);
        void insereFinal(ListaDeURLS item, string host);
        void inserePosicao(ListaDeURLS item, int pos);
        ListaDeURLS removeInicio();
        ListaDeURLS removePosicao(int pos);
        void imprime();
        void limpa();
    
    protected:
        int tamanho;
        CelulaListaDeHosts* primeiro;
        CelulaListaDeHosts* ultimo;
        CelulaListaDeHosts* posiciona(int pos, bool antes);
};

#endif
