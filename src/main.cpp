//---------------------------------------------------------------------
// Arquivo	: main.cpp
// Conteudo	: implementacao do programa principal
// Autor	: Gabriel Teixeira Carvalho (gabrielteixeirac@dcc.ufmg.br)
// Historico	: 2021-11-23 - arquivo criado
//---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <regex>
#include "listadeurls.h"
#include "filadehosts.h"
#include "escalonador.h"
#include "msgassert.h"
#include "memlog.h"

using namespace std;

// Descricao: programa principal para execucao do escalonador
// Entrada: argc e argv
// Saida: depende da operacao escolhida
int main(int argc, char *argv[]){
    // inicia registro de acesso à memória
    char nomeArquivoRegistro[100] = "tmp/log.txt";
    iniciaMemLog(nomeArquivoRegistro);
    ativaMemLog();

    defineFaseMemLog(0);
    Escalonador escalonador;

    erroAssert(argv[1], "Nome de arquivo de entrada deve ser especificado");
    
    // argv[1] = caminho do arquivo de comandos passado como parametro pela linha de comando
    string nomeArquivoComandos = argv[1];

    // regex para identificar nome do arquivo 
    // matches: [0] = nome do arquivo inteiro, [1] = /xxxx/xxxx (caminho), [2] = .xxx (extensão)
    smatch matches;
    regex regexNomeDoArquivo("([-/A-Za-z0-9]*)(.[a-z]*)");
    regex_match(nomeArquivoComandos, matches, regexNomeDoArquivo);

    string nomeDoArquivoSemExtensao = matches[1];
    string extensaoDoArquivo = matches[2];

    string nomeArquivoSaida = "";

    // adiciona o sufixo -out ao nome do arquivo passado como parametro 
    nomeArquivoSaida.append(nomeDoArquivoSemExtensao).append("-out").append(extensaoDoArquivo);
    
    // abrem arquivos de comandos e de saída
    ifstream arquivoDeComandos(nomeArquivoComandos.c_str());
    ofstream arquivoDeSaida(nomeArquivoSaida.c_str());

    string comando;
    
    if (arquivoDeComandos.is_open() && arquivoDeSaida.is_open()){
        while (getline(arquivoDeComandos, comando)){
            // regex para identificar comandos passados pelo arquivo
            // matches: [0] = comando inteiro, [1] = COMANDO, [2] = host, [3] = quantidade, [4] = \r
            smatch matches;
            regex regexComando("([A-Z]*_?[A-Z]*) *([-a-zA-Z./:0-9]*) *([0-9]*)([\\r]*)");
            regex_match(comando, matches, regexComando);
            
            unsigned long parametroInteiro;
            string parametroString;
            string comandoFiltrado;

            comandoFiltrado = matches[1];

            bool comandoExiste = false;

            if (comandoFiltrado == "ADD_URLS"){
                defineFaseMemLog(1);
                comandoExiste = true;
                // converte para unsigned long (só valores positivos) a string numérica identificada pelo regex
                parametroInteiro = stoul(matches[2]);
                
                string url;
                // pega a linha do arquivo de comandos e adiciona ao escalonador
                for (unsigned long i = 0; i < parametroInteiro; i++){
                    getline(arquivoDeComandos, url);
                    escalonador.addUrl(url);
                }
            }
            else if (comandoFiltrado == "ESCALONA_TUDO"){
                defineFaseMemLog(2);
                comandoExiste = true;
                escalonador.escalonaTudo(arquivoDeSaida);
            }
            else if (comandoFiltrado == "ESCALONA"){
                defineFaseMemLog(3);
                comandoExiste = true;
                parametroInteiro = stoul(matches[2]);
                escalonador.escalona(parametroInteiro, arquivoDeSaida);
            }
            else if (comandoFiltrado == "ESCALONA_HOST"){
                defineFaseMemLog(4);
                comandoExiste = true;
                parametroString = matches[2];
                parametroInteiro = stoul(matches[3]);                
                escalonador.escalonaHost(parametroString, parametroInteiro, arquivoDeSaida);
            }
            else if (comandoFiltrado == "VER_HOST"){
                defineFaseMemLog(5);
                comandoExiste = true;
                parametroString = matches[2];
                escalonador.verHost(parametroString, arquivoDeSaida);
            }            
            else if (comandoFiltrado == "LISTA_HOSTS"){
                defineFaseMemLog(6);
                comandoExiste = true;
                escalonador.listaHosts(arquivoDeSaida);
            }
            else if (comandoFiltrado == "LIMPA_HOST"){
                defineFaseMemLog(7);
                comandoExiste = true;
                parametroString = matches[2];
                escalonador.limpaHost(parametroString);
            }
            else if (comandoFiltrado == "LIMPA_TUDO"){
                defineFaseMemLog(8);
                comandoExiste = true;
                escalonador.limpaTudo();
            }
            else {
                avisoAssert(comandoExiste, "Comando não existe");
            }           
        }

        // fecha os arquivos abertos
        arquivoDeComandos.close();
        arquivoDeSaida.close();
    }
    else{
        erroAssert(arquivoDeComandos.is_open(), "Arquivo de Comandos não foi aberto");
        erroAssert(arquivoDeSaida.is_open(), "Arquivo de Saída não foi aberto");    
    }
    // finaliza registro de acesso à memória
    finalizaMemLog();
    return 0;
}
