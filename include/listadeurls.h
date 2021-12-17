//---------------------------------------------------------------------
// Arquivo	: listadeurls.h
// Conteudo	: definicoes do listadeurls 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------
#ifndef LISTADEURLSH
#define LISTADEURLSH

#include <string>
#include <fstream>
using namespace std;

struct CelulaLista
{
    string item;
    CelulaLista* prox;

    CelulaLista(){
        this->item = "";
        this->prox = NULL;
    }
    
};


class ListaDeURLS {
    public:
        ListaDeURLS();
        bool vazia();
        int getTamanho();
        string getItem(int pos);
        void setItem(string item, int pos);
        void insereInicio(string item);
        void insereFinal(string item);
        void inserePosicao(string item, int pos);
        string removeInicio();
        string removeFinal();
        string removePosicao(int pos);
        void imprime(ofstream& arquivoDeSaida);
        void limpa();
    
    protected:
        int tamanho;
        CelulaLista* primeiro;
        CelulaLista* ultimo;
        CelulaLista* posiciona(int pos, bool antes);
};

#endif
