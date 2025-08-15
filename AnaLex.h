#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <string.h>


using namespace std;

class Analex{
    private:
        ifstream arqOrig;
        ofstream arqObj;
        string letras;
        string digitos;
        string simbolos;

        bool EH_PALAVRA_RESERVADA;
        bool ok;

        map<string,string> palavras_reservadas;

        map<string,string> simbolos_especiais;

    public:

        vector<string> numeros;
        vector<string> identificadores;

        int contador;
        string atomo;
        char proximo;
        string simbolo;

        Analex();

        void PROXIMO();

        string CODIGO(string s);

        void ERRO();

        bool buscaLetra();

        bool buscaDigitos();

        bool verificaSimbolosEspeciais();

        string codigoDeIdentificador();

        string codigoDeNumero();

        void verificaPalavra();

        void start();

    };