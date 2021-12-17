//---------------------------------------------------------------------
// Arquivo	: filadehosts.cpp
// Conteudo	: implementacao da fila de hosts 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "filadehosts.h"
#include "listadeurls.h"

using namespace std;

FilaDeHosts::FilaDeHosts() {
    primeiro = new CelulaFilaDeHosts();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;
}

bool FilaDeHosts::vazia() {
    return tamanho == 0;
}

int FilaDeHosts::getTamanho() {
    return tamanho;
}

ListaDeURLS* FilaDeHosts::getItem(int pos){
    CelulaFilaDeHosts *p;
    p = posiciona(pos, false);
    return &(p->item);
}

string FilaDeHosts::getHost(int pos){
    CelulaFilaDeHosts *p;
    p = posiciona(pos, false);
    return p->host;
}

CelulaFilaDeHosts* FilaDeHosts::posiciona(int pos, bool antes = false){
    CelulaFilaDeHosts *p; 
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

void FilaDeHosts::insereFinal(ListaDeURLS item, string host){
    CelulaFilaDeHosts *nova;
    nova = new CelulaFilaDeHosts();
    nova->item = item;
    nova->host = host;
    ultimo->prox = nova;
    ultimo = nova;
    nova->prox = NULL;
    tamanho++;
}

ListaDeURLS FilaDeHosts::removeInicio(){
    ListaDeURLS aux;
    CelulaFilaDeHosts *p;
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

void FilaDeHosts::limpa(){
    CelulaFilaDeHosts *p;
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
