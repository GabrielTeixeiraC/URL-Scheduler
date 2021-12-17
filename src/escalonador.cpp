//---------------------------------------------------------------------
// Arquivo	: escalonador.cpp
// Conteudo	: implementacao do escalonador 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <regex>
#include "escalonador.h"

using namespace std;

Escalonador::Escalonador(){
    coletor = ListaDeHosts();   
}

void insereNaPosicaoCorreta(ListaEncadeada* listaDeURLS, string urlValida){
    string urlPresente;

    int profundidadeURLNova;
    int profundidadeURLAnterior;
    int profundidadeURLProxima;

    if (listaDeURLS->getTamanho() == 0){
        listaDeURLS->insereInicio(urlValida);
        return;
    }
    else if (listaDeURLS->getTamanho() == 1){
        profundidadeURLNova = count(urlValida.begin(), urlValida.end(), '/');
        urlPresente = listaDeURLS->getItem(1);
        profundidadeURLAnterior = count(urlPresente.begin(), urlPresente.end(), '/');
        
        if (urlValida == urlPresente){
            return;
        }

        if(profundidadeURLNova >= profundidadeURLAnterior){
            listaDeURLS->insereFinal(urlValida);
        }
        else{
            listaDeURLS->insereInicio(urlValida);
        }
        return;
    }
    else{
        //insere depois de igual
        for (int j = 0; j < listaDeURLS->getTamanho() - 1; j++){
            profundidadeURLNova = count(urlValida.begin(), urlValida.end(), '/');
            
            urlPresente = listaDeURLS->getItem(j + 1);
            profundidadeURLAnterior = count(urlPresente.begin(), urlPresente.end(), '/');

            if (urlValida == urlPresente){
                return;
            }
            
            if (profundidadeURLNova == profundidadeURLAnterior){
                listaDeURLS->inserePosicao(urlValida, j + 2);
                return;
            }
        }
        
        for (int j = 0; j < listaDeURLS->getTamanho() - 1; j++){
            profundidadeURLNova = count(urlValida.begin(), urlValida.end(), '/');
            profundidadeURLAnterior = 0;
            profundidadeURLProxima = 0;

            urlPresente = listaDeURLS->getItem(j + 1);
            profundidadeURLAnterior = count(urlPresente.begin(), urlPresente.end(), '/');

            if (urlValida == urlPresente){
                return;
            }

            urlPresente = listaDeURLS->getItem(j + 2);
            profundidadeURLProxima = count(urlPresente.begin(), urlPresente.end(), '/');
            
            if (profundidadeURLNova < profundidadeURLAnterior){
                listaDeURLS->insereInicio(urlValida);
            }
            else if (profundidadeURLNova > profundidadeURLAnterior and profundidadeURLNova < profundidadeURLProxima){
                listaDeURLS->inserePosicao(urlValida, j + 2);
            }
            else{
                listaDeURLS->insereFinal(urlValida);
            }
            return;
        }
    }    
}


void Escalonador::addUrls(int quantidade, string url){
    smatch matches;
    regex regexURL("(http:\\/\\/)(www.)?([A-Za-z0-9]*[.A-Za-z0-9]*)([-._=?\\/A-Za-z0-9]*)([\\/#A-Za-z0-9]*)([\\r]*)");
    if(regex_match(url, matches, regexURL)){
        bool hostPresente = false;

        ListaEncadeada* listaDeURLS = new ListaEncadeada();
        string host = matches[3];

        string urlValida = "";
        //URL: http:// + www. + xxxxxx.com + /xxxx/xxxxx + #<fragmento> - removendo www. e #<fragmento>
        urlValida.append(matches[1]).append(matches[3]).append(matches[4]);
        if (urlValida.find(".jpg") != string::npos || urlValida.find(".gif") != string::npos || urlValida.find(".mp3") != string::npos ||\
            urlValida.find(".avi") != string::npos || urlValida.find(".doc") != string::npos || urlValida.find(".pdf") != string::npos){
            cerr << "URL inválida" << endl;
            return;
        }
        

        if (urlValida.back() == '/'){
            urlValida.pop_back();
        }
        
        for (int i = 0; i < coletor.getTamanho(); i++){
            if (coletor.getHost(i + 1) == host){
                hostPresente = true;
                listaDeURLS = coletor.getItem(i + 1);

                insereNaPosicaoCorreta(listaDeURLS, urlValida);
                break;
            }
        }
        if (!hostPresente){
            listaDeURLS->insereInicio(urlValida);
            coletor.insereFinal(*(listaDeURLS), host);
        }
    }

    else{
        cerr << "URL inválida" << endl;
    }
}

void Escalonador::escalonaTudo(ofstream& arquivoDeSaida){
    for (int i = 0; i < coletor.getTamanho(); i++)    {
        ListaEncadeada *aux = coletor.getItem(i + 1);
        int tamanhoLista = aux->getTamanho();
        for (int j = 0; j < tamanhoLista; j++){
            arquivoDeSaida << aux->removeInicio() << endl;
        }            
    }
}

// Descricao: escalona a quantidade especificada de URLs seguindo a fila de hosts
// Entrada: quantidade e arquivoDeSaida
// Saida: URLs impressas
void Escalonador::escalona(int quantidade, ofstream& arquivoDeSaida){
    
    // nenhuma URL para escalonar
    if (quantidade <= 0){
        return;
    }

    int quantidadeAtual;
    ListaEncadeada* aux;
    
    // percorre a fila de hosts <---------------------------------------------------------------------- escalonando as URLs,
    // se um host for completamente escalonado, passa para o próximo na fila e continua escalonando   
    for (int i = 0; i < coletor.getTamanho(); i++){

        //
        aux = coletor.getItem(i + 1);
        quantidadeAtual = aux->getTamanho();

        if (quantidade >= quantidadeAtual){
            for (int j = 0; j < quantidadeAtual; j++){
                arquivoDeSaida << aux->removeInicio() << endl;
            }
            quantidade = quantidade - quantidadeAtual;
        }
        else{
            for (int j = 0; j < quantidade; j++){
                arquivoDeSaida << aux->removeInicio() << endl;
            }
        }
    }        
}

// Descricao: escalona a quantidade especificada de URLs de um host específico seguindo a fila de hosts
// Entrada: host, quantidade arquivoDeSaida
// Saida: URLs impressas
void Escalonador::escalonaHost(string host, int quantidade, ofstream& arquivoDeSaida){
    int quantidadeFinal;
    ListaEncadeada *aux;
    bool hostPresente = false;
    for (int i = 0; i < coletor.getTamanho(); i++){
        if (coletor.getHost(i + 1) == host){
            aux = coletor.getItem(i + 1);
            hostPresente = true;
            break;
        }
    }
    // erroAssert(hostPresente, "Host não está presente na fila");
    if (!hostPresente){
        cerr << "Host não está presente na fila" << endl;
        return;
    }
    
    quantidadeFinal = aux->getTamanho();
    if (quantidadeFinal >= quantidade){
        quantidadeFinal = quantidade;
    }

    for (int j = 0; j < quantidadeFinal; j++){
        arquivoDeSaida << aux->removeInicio() << endl; 
    }

}

void Escalonador::verHost(string host, ofstream& arquivoDeSaida){
    bool hostPresente = false;
    for (int i = 0; i < coletor.getTamanho(); i++){
        if (coletor.getHost(i + 1) == host){
            ListaEncadeada *aux = coletor.getItem(i + 1);
            aux->imprime(arquivoDeSaida);
            hostPresente = true;
            break;
        }
    }
    if(!hostPresente){
        cerr << "Host não está presente na fila, abortar" << endl;
        return;
    }
}

void Escalonador::listaHosts(ofstream& arquivoDeSaida){
    for (int i = 0; i < coletor.getTamanho(); i++){
        arquivoDeSaida << coletor.getHost(i + 1) << endl;
    }
}

void Escalonador::limpaHost(string host){
    for (int i = 0; i < coletor.getTamanho(); i++){
        if (coletor.getHost(i + 1) == host){
            coletor.removePosicao(i + 1);
        }
    }
}

void Escalonador::limpaTudo(){
    for (int i = 0; i < coletor.getTamanho(); i++){
        coletor.limpa();
    }
}