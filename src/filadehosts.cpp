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

// construtor da Fila de Hosts
FilaDeHosts::FilaDeHosts() {
    primeiro = new CelulaFilaDeHosts();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;
}

// checa se a Fila de Hosts está vazia
bool FilaDeHosts::vazia() {
    return tamanho == 0;
}

// retorna o tamanho da Fila de Hosts
int FilaDeHosts::getTamanho() {
    return tamanho;
}

// Descricao: retorna o endereço da Lista de URLs na posição especificada
// Entrada: pos
// Saida: endereço de ListaDeURLS
ListaDeURLS* FilaDeHosts::getItem(int pos){
    CelulaFilaDeHosts *p;
    p = posiciona(pos, false);
    return &(p->item);
}

// Descricao: retorna o host da Celula de Fila de Hosts na posição especificada
// Entrada: pos
// Saida: string
string FilaDeHosts::getHost(int pos){
    CelulaFilaDeHosts *p;
    p = posiciona(pos, false);
    return p->host;
}

// Descricao: etorna a Celula da Fila de Hosts na posição especificada ou uma posição antes
// Entrada: pos, antes
// Saida: Celula de Fila de Hosts
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

// Descricao: insere uma Lista de URLs no final da Celula de Fila de Hosts com o host especificado
// Entrada: item, host
// Saida: -
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

// Descricao: remove uma Lista de URLs do início da Fila de Hosts
// Entrada: -
// Saida: ListaDeURLS removida
ListaDeURLS FilaDeHosts::removeInicio(){
    ListaDeURLS aux;
    CelulaFilaDeHosts *p;
    if (tamanho == 0){
        throw "ERRO: Lista vazia!";
    }
    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;

    // ListaDeURLS era a única na Fila de Hosts
    if(primeiro->prox == NULL){
        ultimo = primeiro;
    }

    aux = p->item;
    delete p;
    return aux;
}

// Descricao: limpa a Fila De Hosts, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
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
