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

using namespace std;

int main(int argc, char *argv[]){
    Escalonador escalonador;

    if (!argv[1]){
        cerr << "Nome de arquivo de entrada inválido, abortar programa" << endl;
    }
    

    string nomeArquivoComandos = argv[1];
    string nomeArquivoSaida = "";

    smatch matches;
    regex regexNomeDoArquivo("([-/A-Za-z0-9]*)(.[a-z]*)");
    regex_match(nomeArquivoComandos, matches, regexNomeDoArquivo);

    string nomeDoArquivoSemExtensao = matches[1];
    string extensaoDoArquivo = matches[2];


    nomeArquivoSaida.append(nomeDoArquivoSemExtensao).append("-out").append(extensaoDoArquivo);
    
    ifstream arquivoDeComandos(nomeArquivoComandos);
    ofstream arquivoDeSaida(nomeArquivoSaida);

    string comando;
    string comandoFiltrado;
    
    string url;

    unsigned long parametroInteiro;
    string parametroString;



    if (arquivoDeComandos.is_open() && arquivoDeSaida.is_open()){
        while (getline(arquivoDeComandos, comando)){
            smatch matches;
            regex regexComando("([A-Z]*_?[A-Z]*) *([a-zA-Z./:0-9]*) *([0-9]*)([\\r]*)");
            regex_match(comando, matches, regexComando);
            
            comandoFiltrado = matches[1];

            if (comandoFiltrado == "ADD_URLS"){
                parametroInteiro = stoul(matches[2]);
                
                for (unsigned long i = 0; i < parametroInteiro; i++){
                    getline(arquivoDeComandos, url);
                    escalonador.addUrl(url);
                }
                
            }
            else if (comandoFiltrado == "ESCALONA_TUDO"){
                escalonador.escalonaTudo(arquivoDeSaida);
            }
            else if (comandoFiltrado == "ESCALONA"){
                parametroInteiro = stoul(matches[2]);
                escalonador.escalona(parametroInteiro, arquivoDeSaida);
            }
            else if (comandoFiltrado == "ESCALONA_HOST"){
                parametroString = matches[2];
                parametroInteiro =  stoul(matches[3]);
                escalonador.escalonaHost(parametroString, parametroInteiro, arquivoDeSaida);
            }
            else if (comandoFiltrado == "VER_HOST"){
                parametroString = matches[2];
                escalonador.verHost(parametroString, arquivoDeSaida);
            }            
            else if (comandoFiltrado == "LISTA_HOSTS"){
                escalonador.listaHosts(arquivoDeSaida);
            }
            else if (comandoFiltrado == "LIMPA_HOST"){
                parametroString = matches[2];
                escalonador.limpaHost(parametroString);
            }
            else if (comandoFiltrado == "LIMPA_TUDO"){
                escalonador.limpaTudo();
            }
            else {
                cerr << "Comando não existe" << endl;
            }           
        }

        arquivoDeComandos.close();
        arquivoDeSaida.close();
    }
    return 0;
}
