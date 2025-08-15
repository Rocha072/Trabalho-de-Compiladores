#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>


using namespace std;

class Anasint{
    
    private:
        ifstream arqLex;
        string token;
        int contador;
        

    public:
        bool error;

        Anasint();

        void prox_token();

        void erro(string mensagem);

        void program();
        bool bloco();
        bool parte_de_declaracoes_de_variaveis();
        bool declaracao_de_variaveis();
        bool lista_de_identificadores();
        bool parte_de_declaracoes_de_subrotinas();
        bool declaracao_de_procedimento();
        bool declaracao_de_funcao();
        void parametros_formais();
        bool secao_de_parametros_formais();
        bool comando_composto();
        bool comando();
        bool comando_sem_rotulo();
        bool atribuicao();
        bool chamada_de_procedimento();
        bool comando_condicional();
        bool comando_repetitivo();
        bool lista_de_expressoes();
        bool expressao();
        bool relacao();
        bool expressao_simples();
        bool termo();
        bool fator();
        bool variavel();
        bool chamada_de_funcao();
        bool numero();
        bool digito(char l);
        bool identificador();
        bool letra(char l);
        void start();
    };       