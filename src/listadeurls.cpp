//---------------------------------------------------------------------
// Arquivo	: listadeurls.cpp
// Conteudo	: implementacao da lista de urls 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "listadeurls.h"

using namespace std;

// construtor da Lista de URLs
ListaDeURLS::ListaDeURLS() {
    primeiro = new CelulaLista();
    ultimo = primeiro;
    ultimo->prox = NULL;
    
    tamanho = 0;
}

// checa se a Lista de URLs está vazia
bool ListaDeURLS::vazia() {
    return tamanho == 0;
}

// retorna o tamanho da Lista de URLs
int ListaDeURLS::getTamanho() {
    return tamanho;
}

// Descricao: retorna a string na posição especificada
// Entrada: pos
// Saida: string
string ListaDeURLS::getItem(int pos){
    CelulaLista *p;
    p = posiciona(pos, false);
    return p->item;
}

// Descricao: Retorna a Celula da Lista de URLs na posição especificada ou uma posição antes
// Entrada: pos, antes
// Saida: Celula de Lista de URLs 
CelulaLista* ListaDeURLS::posiciona(int pos, bool antes = false){
    CelulaLista *p; 
    int i;
    if ( (pos > tamanho) || (pos <= 0) ){
        throw "ERRO: Posicao Invalida!";
    }
    // posiciona na célula anterior a desejada
    p = primeiro;
    for(i=1; i<pos; i++){
        p = p->prox;
    }
    // vai para a próxima
    // se antes for false
    if(!antes){
        p = p->prox;
    }
    return p;
}

// Descricao: insere uma string no início da Lista de URLs
// Entrada: item
// Saida: -
void ListaDeURLS::insereInicio(string item){
    CelulaLista *nova;
    nova = new CelulaLista();
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;

    // nova celula é a ultima
    if(nova->prox == NULL){
        ultimo = nova;
    }
}

// Descricao: insere uma string no final da Lista de URLs
// Entrada: item
// Saida: -
void ListaDeURLS::insereFinal(string item){
    CelulaLista *nova;
    nova = new CelulaLista();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
}

// Descricao: insere uma string na posição especificada da Lista de URLs
// Entrada: item, pos
// Saida: -
void ListaDeURLS::inserePosicao(string item, int pos){
    CelulaLista *p, *nova;
    p = posiciona(pos,true); // posiciona na célula anterior
    nova = new CelulaLista();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;

    // nova celula é a última
    if(nova->prox == NULL){
        ultimo = nova;
    }
}

// Descricao: remove uma string do início da Lista de URLs
// Entrada: -
// Saida: string removida
string ListaDeURLS::removeInicio(){
    string aux;
    CelulaLista *p;
    if (tamanho == 0){
        throw "ERRO: Lista vazia!";
    }
    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;

    // string era a única na Lista de URLs
    if(primeiro->prox == NULL){
        ultimo = primeiro;
    }

    aux = p->item;
    delete p;
    return aux;
}

// Descricao: remove uma string do final da Lista de URLs
// Entrada: -
// Saida: string removida
string ListaDeURLS::removeFinal(){
    string aux;
    CelulaLista *p;
    if (tamanho == 0){
        throw "ERRO: Lista vazia!";
    }
    // posiciona p na celulaLista anterior à última
    p = posiciona(tamanho, true);
    p->prox = NULL;
    tamanho--;
    aux = ultimo->item;
    delete ultimo;
    ultimo = p;
    return aux;
}

// Descricao: remove uma string da posição especificada da Lista de URLs
// Entrada: pos
// Saida: string removida
string ListaDeURLS::removePosicao(int pos){
    string aux;
    CelulaLista *p, *q;
    if (tamanho == 0){
        throw "ERRO: Lista vazia!";
    }
    // posiciona p na celulaLista anterior à pos
    p = posiciona(pos, true);
    q = p->prox;
    p->prox = q->prox;
    tamanho--;
    aux = q->item;
    delete q;

    // string era a última da Lista de URLs
    if(p->prox == NULL){
        ultimo = p;
    }
    return aux;
}

// Descricao: imprime as strings da Lista De URLs
// Entrada: arquivoDeSaida
// Saida: -
void ListaDeURLS::imprime(ofstream& arquivoDeSaida){
    CelulaLista *p;
    p = primeiro->prox;
    
    while (p!=NULL) {
        arquivoDeSaida << p->item << endl;
        p = p->prox;
    }
}

// Descricao: limpa a Lista De URLs, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
void ListaDeURLS::limpa(){
    CelulaLista *p;
    p = primeiro->prox;
    while (p!=NULL) {
        primeiro->prox = p->prox;
        delete p;
        p = NULL;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}
