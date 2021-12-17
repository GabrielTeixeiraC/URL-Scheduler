//---------------------------------------------------------------------
// Arquivo	: listadehosts.cpp
// Conteudo	: implementacao do listadehosts 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "listadehosts.h"
#include "listadeurls.h"

using namespace std;

ListaDeHosts::ListaDeHosts() {
    primeiro = new CelulaListaDeHosts();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;
}

bool ListaDeHosts::vazia() {
    return tamanho == 0;
}

int ListaDeHosts::getTamanho() {
    return tamanho;
}

ListaDeURLS* ListaDeHosts::getItem(int pos){
    CelulaListaDeHosts *p;
    p = posiciona(pos, false);
    return &(p->item);
}

string ListaDeHosts::getHost(int pos){
    CelulaListaDeHosts *p;
    p = posiciona(pos, false);
    return p->host;
}

CelulaListaDeHosts* ListaDeHosts::posiciona(int pos, bool antes = false){
    CelulaListaDeHosts *p; 
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

void ListaDeHosts::setItem(ListaDeURLS item, int pos){
    CelulaListaDeHosts *p;
    p = posiciona(pos);
    p->item = item;
}

void ListaDeHosts::insereInicio(ListaDeURLS item){
    CelulaListaDeHosts *nova;
    nova = new CelulaListaDeHosts();
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        ultimo = nova;
    }
}

void ListaDeHosts::insereFinal(ListaDeURLS item, string host){
    CelulaListaDeHosts *nova;
    nova = new CelulaListaDeHosts();
    nova->item = item;
    nova->host = host;
    ultimo->prox = nova;
    ultimo = nova;
    nova->prox = NULL;
    tamanho++;
}

void ListaDeHosts::inserePosicao(ListaDeURLS item, int pos){
    CelulaListaDeHosts *p, *nova;
    p = posiciona(pos,true); // posiciona na célula anterior
    nova = new CelulaListaDeHosts();
    nova->item = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        ultimo = nova;
    }
}

ListaDeURLS ListaDeHosts::removeInicio(){
    ListaDeURLS aux;
    CelulaListaDeHosts *p;
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

ListaDeURLS ListaDeHosts::removePosicao(int pos){
    ListaDeURLS aux;
    CelulaListaDeHosts *p, *q;
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
// void ListaDeHosts::imprime(){
//     CelulaListaDeHosts *p;
//     p = primeiro->prox;
//     while (p!=NULL) {
//         cout << p->host << endl;
//         p = p->prox;
//     }
// }

void ListaDeHosts::limpa(){
    CelulaListaDeHosts *p;
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

// ListaDeHosts::~ListaDeHosts(){
//     limpa();
//     delete primeiro;
// }