//---------------------------------------------------------------------
// Arquivo	: escalonador.cpp
// Conteudo	: implementacao do escalonador 
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-30 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <regex>
#include "escalonador.h"
#include "memlog.h"

using namespace std;

// construtor de um escalonador
Escalonador::Escalonador(){
    escalonador = FilaDeHosts();   

    // registra acesso à memoria
    escreveMemLog( (long int) (&escalonador), sizeof(FilaDeHosts), 2);
}

// Descricao: insere a URL na posição correta da lista de URLs do host em 
//            ordem crescente de profundidade (quantidade de barras na URL)
// Entrada: listaDeURLS, urlValida
// Saida: -
void insereNaPosicaoCorreta(ListaDeURLS* listaDeURLS, string urlValida){
    string urlPresente;

    // profundidade da URL a ser adicionada  
    int profundidadeURLNova;

    // profundidade das URLs já presentes na lista
    int profundidadeURLAnterior;
    int profundidadeURLProxima;

    // se a lista estiver vazia, apenas insere no início
    if (listaDeURLS->getTamanho() == 0){
        listaDeURLS->insereInicio(urlValida);
        return;
    }
    // se a lista tiver somente 1 elemento, compara a profundidade entre o elemento novo e o já presente
    else if (listaDeURLS->getTamanho() == 1){
        profundidadeURLNova = count(urlValida.begin(), urlValida.end(), '/');

        urlPresente = listaDeURLS->getItem(1);
        escreveMemLog( (long int) (&urlPresente), sizeof(string), 2);

        profundidadeURLAnterior = count(urlPresente.begin(), urlPresente.end(), '/');
        
        // impede inserção de URLs repetidas
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
    // lista com mais de 1 elemento
    else{
        // trata do caso em que a profundidade nova é igual a alguma profundidade já presente
        for (int j = 1; j <= listaDeURLS->getTamanho() - 1; j++){
            profundidadeURLNova = count(urlValida.begin(), urlValida.end(), '/');
            
            urlPresente = listaDeURLS->getItem(j);
            escreveMemLog( (long int) (&urlPresente), sizeof(string), 2);

            profundidadeURLAnterior = count(urlPresente.begin(), urlPresente.end(), '/');

            if (urlValida == urlPresente){
                return;
            }
            
            if (profundidadeURLNova == profundidadeURLAnterior){
                listaDeURLS->inserePosicao(urlValida, j + 1);
                return;
            }
        }
        
        // encaixa a nova URL entre uma URL anterior e uma próxima URL
        for (int j = 1; j <= listaDeURLS->getTamanho() - 1; j++){
            profundidadeURLNova = count(urlValida.begin(), urlValida.end(), '/');
            profundidadeURLAnterior = 0;
            profundidadeURLProxima = 0;

            // pega a profundidade da URL anterior
            urlPresente = listaDeURLS->getItem(j);
            escreveMemLog( (long int) (&urlPresente), sizeof(string), 2);

            profundidadeURLAnterior = count(urlPresente.begin(), urlPresente.end(), '/');

            // checa se a URL já está presente, só compara com a URL anterior pois a próxima URL
            // vai se tornar a URL anterior na próxima iteração do loop
            if (urlValida == urlPresente){
                return;
            }

            // pega a profundidade da próxima URL
            urlPresente = listaDeURLS->getItem(j + 1);
            escreveMemLog( (long int) (&urlPresente), sizeof(string), 2);

            profundidadeURLProxima = count(urlPresente.begin(), urlPresente.end(), '/');
            
            // encaixa a URL nova na posição correta, seja no início, no meio ou no final da lista
            if (profundidadeURLNova < profundidadeURLAnterior){
                listaDeURLS->insereInicio(urlValida);
            }
            else if (profundidadeURLNova > profundidadeURLAnterior and profundidadeURLNova < profundidadeURLProxima){
                listaDeURLS->inserePosicao(urlValida, j + 1);
            }
            else{
                listaDeURLS->insereFinal(urlValida);
            }
            return;
        }
    }    
}

// Descricao: adiciona ao escalonador a url passada como parametro
// Entrada: url
// Saida: -
void Escalonador::addUrl(string url){
    smatch matches;

    // padrão de regex seguindo as regras da especificação para identificar URLs válidas
    regex regexURL("(http:\\/\\/)(www.)?([A-Za-z0-9]*[.A-Za-z0-9]*)([-._=?\\/A-Za-z0-9]*)([\\/#A-Za-z0-9]*)([\\r]*)");
    if(regex_match(url, matches, regexURL)){    //URL válida
        
        // matches: [0] = URL inteira, [1] = http://, [2] = www., [3] = xxxx.com (host)
        //          [4] = /xxxx/xxxx?q=xxxx (path e query), [5] = #xxxxxx (fragmento), [6] = \r   
        
        string host = matches[3];

        string urlValida = "";

        //urlValida: http:// + xxxx.com + /xxxx/xxxx?q=xxxx -> <protocolo>://<host><path>?<query>
        urlValida.append(matches[1]).append(matches[3]).append(matches[4]);

        // invalida URLs com as extensões .jpg, .gif, .mp3, .avi, .doc e .pdf
        if (urlValida.find(".jpg") != string::npos || urlValida.find(".gif") != string::npos || urlValida.find(".mp3") != string::npos ||\
            urlValida.find(".avi") != string::npos || urlValida.find(".doc") != string::npos || urlValida.find(".pdf") != string::npos){
            cerr << "URL inválida" << endl;
            return;
        }

        // remove '/' no final
        if (urlValida.back() == '/'){
            urlValida.pop_back();
        }
        
        bool hostPresente = false;
        ListaDeURLS* listaDeURLS = new ListaDeURLS();
        escreveMemLog( (long int) (&listaDeURLS), sizeof(ListaDeURLS*), 2);

        
        // procura o host e insere a URL na posição correta da lista
        for (int i = 1; i <= escalonador.getTamanho(); i++){
            if (escalonador.getHost(i) == host){
                hostPresente = true;
                listaDeURLS = escalonador.getItem(i);
                escreveMemLog( (long int) (&listaDeURLS), sizeof(ListaDeURLS*), 2);

                insereNaPosicaoCorreta(listaDeURLS, urlValida);
                break;
            }
        }

        // cria um host novo no final da fila se o host não está presente
        if (!hostPresente){
            listaDeURLS->insereInicio(urlValida);
            escalonador.insereFinal(*(listaDeURLS), host);
        }
    }

    else{
        cerr << "URL inválida" << endl;
    }
}

// Descricao: escalona todas as URLs seguindo as regras estabelecidas.
//            Quando escalonadas, as URLs são exibidas e removidas da lista
// Entrada: arquivoDeSaida
// Saida: -
void Escalonador::escalonaTudo(ofstream& arquivoDeSaida){
    // percorre o escalonador imprimindo todas as URLs em cada host
    for (int i = 1; i <= escalonador.getTamanho(); i++)    {
        ListaDeURLS *aux = escalonador.getItem(i);
        escreveMemLog( (long int) (&aux), sizeof(ListaDeURLS), 2);
        int tamanhoLista = aux->getTamanho();
        for (int j = 0; j < tamanhoLista; j++){
            arquivoDeSaida << aux->removeInicio() << endl;
        }            
    }
}

// Descricao: escalona a quantidade especificada de URLs seguindo a fila de hosts
// Entrada: quantidade e arquivoDeSaida
// Saida: -
void Escalonador::escalona(int quantidade, ofstream& arquivoDeSaida){
    // nenhuma URL para escalonar
    if (quantidade <= 0){
        return;
    }

    int quantidadeAtual;
    ListaDeURLS* aux;
    
    // percorre a fila de hosts escalonando as URLs,
    // se um host for completamente escalonado, passa para o próximo na fila e continua escalonando   
    for (int i = 1; i <= escalonador.getTamanho(); i++){
        // a celula cabeça é pulada
        aux = escalonador.getItem(i);
        escreveMemLog( (long int) (&aux), sizeof(ListaDeURLS*), 2);
        quantidadeAtual = aux->getTamanho();

        // escalona todo o host e diminui a quantidade a ser escalonada nos proximos hosts
        if (quantidade >= quantidadeAtual){
            for (int j = 0; j < quantidadeAtual; j++){
                arquivoDeSaida << aux->removeInicio() << endl;
            }
            quantidade = quantidade - quantidadeAtual;
        }
        // escalona a quantidade de URLs que sobrou 
        else{
            for (int j = 0; j < quantidade; j++){
                arquivoDeSaida << aux->removeInicio() << endl;
                quantidade = 0;
            }
        }
        
        // já escalonou a quantidade especificada
        if (quantidade == 0){
            return;
        }
    }        
}

// Descricao: escalona a quantidade especificada de URLs de um host específico seguindo a fila de hosts
// Entrada: host, quantidade arquivoDeSaida
// Saida: -
void Escalonador::escalonaHost(string host, int quantidade, ofstream& arquivoDeSaida){
    int quantidadeFinal;
    ListaDeURLS *aux;
    bool hostPresente = false;

    // percorre o escalonador até achar o host passado como parametro
    for (int i = 1; i <= escalonador.getTamanho(); i++){
        if (escalonador.getHost(i) == host){
            aux = escalonador.getItem(i);
            escreveMemLog( (long int) (&aux), sizeof(ListaDeURLS*), 2);
            hostPresente = true;
            break;
        }
    }
    
    // imprime uma mensagem de erro se host não tiver sido achado e termina a execução do método
    if (!hostPresente){
        cerr << "Host não está presente na fila" << endl;
        return;
    }
    
    // limita a quantidade de escalonamentos ao tamanho da lista de URLs no host
    quantidadeFinal = aux->getTamanho();
    if (quantidadeFinal >= quantidade){
        quantidadeFinal = quantidade;
    }

    // escalona as URLs
    for (int j = 0; j < quantidadeFinal; j++){
        arquivoDeSaida << aux->removeInicio() << endl; 
    }

}

// Descricao: exibe todas as URLs do host, na ordem de prioridade
// Entrada: host, arquivoDeSaida
// Saida: -
void Escalonador::verHost(string host, ofstream& arquivoDeSaida){
    bool hostPresente = false;
    ListaDeURLS *aux;

    // percorre o escalonador até achar o host passado como parametro e imprime suas informações 
    for (int i = 1; i <= escalonador.getTamanho(); i++){
        if (escalonador.getHost(i) == host){
            aux = escalonador.getItem(i);
            escreveMemLog( (long int) (&aux), sizeof(ListaDeURLS*), 2);
            hostPresente = true;
            break;
        }
    }

    // imprime uma mensagem de erro se host não tiver sido achado e termina a execução do método
    if(!hostPresente){
        cerr << "Host não está presente na fila" << endl;
        return;
    }

    aux->imprime(arquivoDeSaida);
}

// Descricao: exibe todos os hosts, seguindo a ordem em que foram conhecidos
// Entrada: arquivoDeSaida
// Saida: -
void Escalonador::listaHosts(ofstream& arquivoDeSaida){
    // percorre o escalonador imprimindo os hosts
    for (int i = 1; i <= escalonador.getTamanho(); i++){
        arquivoDeSaida << escalonador.getHost(i) << endl;
    }
}

// Descricao:  limpa a lista de URLs do host passado como parametro
// Entrada: host
// Saida: -
void Escalonador::limpaHost(string host){
    bool hostPresente = false;
    ListaDeURLS *aux;

    // percorre o escalonador até achar o host passado como parametro e limpa-o
    for (int i = 1; i <= escalonador.getTamanho(); i++){
        if (escalonador.getHost(i) == host){
            aux = escalonador.getItem(i);
            escreveMemLog( (long int) (&aux), sizeof(ListaDeURLS*), 2);
            hostPresente = true;
            break;
        }
    }

    // imprime uma mensagem de erro se host não tiver sido achado e termina a execução do método
    if(!hostPresente){
        cerr << "Host não está presente na fila" << endl;
        return;
    }
    aux->limpa();
}

// Descricao:  limpa todas as URLs, inclusive os hosts
// Entrada: -
// Saida: -
void Escalonador::limpaTudo(){
    // limpa o escalonador
    // for (int i = 0; i < escalonador.getTamanho(); i++){
    // }
    escalonador.limpa();
}