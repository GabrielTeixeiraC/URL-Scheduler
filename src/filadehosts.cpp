//---------------------------------------------------------------------
// Arquivo	: filadehosts.cpp
// Conteudo	: implementacao da fila de hosts 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include "filadehosts.h"
#include "listadeurls.h"
#include "memlog.h"

using namespace std;

// construtor da Fila de Hosts
FilaDeHosts::FilaDeHosts() {
    primeiro = new CelulaFilaDeHosts();
    ultimo = primeiro;
    ultimo->prox = NULL;
    tamanho = 0;

    // registra acesso à memória
    escreveMemLog( (long int) (&primeiro), sizeof(CelulaFilaDeHosts*), 1);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&primeiro), sizeof(CelulaFilaDeHosts*), 1);    
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

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);

    return &(p->item);
}

// Descricao: retorna o host da Celula de Fila de Hosts na posição especificada
// Entrada: pos
// Saida: string
string FilaDeHosts::getHost(int pos){
    CelulaFilaDeHosts *p;
    p = posiciona(pos, false);

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);

    return p->host;
}

// Descricao: etorna a Celula da Fila de Hosts na posição especificada ou uma posição antes
// Entrada: pos, antes
// Saida: Celula de Fila de Hosts
CelulaFilaDeHosts* FilaDeHosts::posiciona(int pos, bool antes = false){
    CelulaFilaDeHosts *p; 
    int i;

    if ( (pos > tamanho) || (pos <= 0) ){
        cerr << "ERRO: Posicao Invalida!" << endl;
    }

    // Posiciona na célula anterior a desejada
    p = primeiro;
    for(i = 1; i < pos; i++){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);
        leMemLog( (long int) (&p->prox), sizeof(CelulaFilaDeHosts*), 1);
    }
    
    // vai para a próxima se antes for false
    if(!antes){
        p = p->prox;

        // registra acesso à memoria
        escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);
        leMemLog( (long int) (&p->prox), sizeof(CelulaFilaDeHosts*), 1);
    }

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&primeiro), sizeof(CelulaFilaDeHosts*), 1);   

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

    // registra acesso à memoria
    escreveMemLog( (long int) (&nova), sizeof(CelulaFilaDeHosts*), 1);
    escreveMemLog( (long int) (&nova->item), sizeof(ListaDeURLS), 1);
    escreveMemLog( (long int) (&ultimo->prox), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&nova), sizeof(CelulaFilaDeHosts*), 1);
    escreveMemLog( (long int) (&ultimo), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&nova), sizeof(CelulaFilaDeHosts*), 1);
}

// Descricao: remove uma Lista de URLs do início da Fila de Hosts
// Entrada: -
// Saida: ListaDeURLS removida
ListaDeURLS FilaDeHosts::removeInicio(){
    ListaDeURLS aux;
    CelulaFilaDeHosts *p;
    if (tamanho == 0){
        cerr << "ERRO: Lista vazia!" << endl;
    }
    p = primeiro->prox;
    primeiro->prox = p->prox;
    tamanho--;

    // ListaDeURLS era a única na Fila de Hosts
    if(primeiro->prox == NULL){
        ultimo = primeiro;

        // registra acesso à memoria
        escreveMemLog( (long int) (&ultimo), sizeof(CelulaFilaDeHosts*), 1);
        leMemLog( (long int) (&primeiro), sizeof(CelulaFilaDeHosts*), 1);        
    }

    aux = p->item;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaFilaDeHosts*), 1);
    escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&p->prox), sizeof(CelulaFilaDeHosts*), 1);
    escreveMemLog( (long int) (&aux), sizeof(ListaDeURLS), 1);
    leMemLog( (long int) (&p->item), sizeof(ListaDeURLS), 1);  

    delete p;
    return aux;
}

// Descricao: limpa a Fila De Hosts, permite evitar vazamentos de memória
// Entrada: -
// Saida: -
void FilaDeHosts::limpa(){
    CelulaFilaDeHosts *p;
    p = primeiro->prox;

    // registra acesso à memoria
    escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&primeiro->prox), sizeof(CelulaFilaDeHosts*), 1);

    while (p != NULL) {
        primeiro->prox = p->prox;
        
        // registra acesso à memoria
        escreveMemLog( (long int) (&primeiro->prox), sizeof(CelulaFilaDeHosts*), 1);
        leMemLog( (long int) (&p->prox), sizeof(CelulaFilaDeHosts*), 1);        
                
        delete p;
        p = NULL;
        p = primeiro->prox;

        escreveMemLog( (long int) (&p), sizeof(CelulaFilaDeHosts*), 1);
        leMemLog( (long int) (&primeiro->prox), sizeof(CelulaFilaDeHosts*), 1);        
    }
    ultimo = primeiro;
    tamanho = 0;

    escreveMemLog( (long int) (&ultimo), sizeof(CelulaFilaDeHosts*), 1);
    leMemLog( (long int) (&primeiro), sizeof(CelulaFilaDeHosts*), 1);    
}
