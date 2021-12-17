//---------------------------------------------------------------------
// Arquivo	: filaencadeada.cpp
// Conteudo	: implementacao do filaencadeada 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "listadeurls.h"

using namespace std;

// construtor da Lista 
ListaDeURLS::ListaDeURLS() {
    primeiro = new CelulaLista();
    ultimo = primeiro;
    ultimo->prox = NULL;
    
    tamanho = 0;
}

bool ListaDeURLS::vazia() {
    return tamanho == 0;
}

int ListaDeURLS::getTamanho() {
    return tamanho;
}

string ListaDeURLS::getItem(int pos){
    CelulaLista *p;
    p = posiciona(pos, false);
    return p->item;
}

CelulaLista* ListaDeURLS::posiciona(int pos, bool antes = false){
    CelulaLista *p; 
    int i;
    if ( (pos > tamanho) || (pos <= 0) ){
        throw "ERRO: Posicao Invalida!";
    }
    // Posiciona na célula anterior a desejada
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

void ListaDeURLS::setItem(string item, int pos){
    CelulaLista *p;
    p = posiciona(pos);
    p->item = item;
}

void ListaDeURLS::insereInicio(string item){
    CelulaLista *nova;
    nova = new CelulaLista();
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        ultimo = nova;
    }
}

void ListaDeURLS::insereFinal(string item){
    CelulaLista *nova;
    nova = new CelulaLista();
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
}

void ListaDeURLS::inserePosicao(string item, int pos){
    CelulaLista *p, *nova;
    p = posiciona(pos,true); // posiciona na célula anterior
    nova = new CelulaLista();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        ultimo = nova;
    }
}

string ListaDeURLS::removeInicio(){
    string aux;
    CelulaLista *p;
    if (tamanho == 0){
        throw "ERRO: Lista vazia!";
    }
    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;
    if(primeiro->prox == NULL){
        ultimo = primeiro;
    }
    aux = p->item;
    delete p;
    return aux;
}

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
    if(p->prox == NULL){
        ultimo = p;
    }
    return aux;
}

void ListaDeURLS::imprime(ofstream& arquivoDeSaida){
    CelulaLista *p;
    p = primeiro->prox;
    
    while (p!=NULL) {
        arquivoDeSaida << p->item << endl;
        p = p->prox;
    }
}

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
