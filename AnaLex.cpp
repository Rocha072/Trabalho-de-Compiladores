#include "AnaLex.h"


Analex::Analex(){
    letras = "abcdefghijklmnopqrstuvwxyz";
    digitos = "0123456789";
    simbolos = ".;,():=<>+-*";

    
    palavras_reservadas ={
        {"begin", "Lbeg"},
        {"integer", "Lint"},
        {"program", "Lprog"},
        {"label", "Llab"},
        {"var", "Lvar"},
        {"procedure", "Lproc"},
        {"function", "Lfunc"},
        {"end", "Lend"},
        {"if", "Lif"},
        {"then", "Lthen"},
        {"else", "Lelse"},
        {"while", "Lwhile"},
        {"do", "Ldo"},
        {"or", "Lor"},
        {"and", "Land"},
        {"div", "Ldiv"},
        {"not", "Lnot"},
        {"boolean", "Lbool"}
    };
    
    
    simbolos_especiais = {
        {":=", "L:="},
        {".", "L."},
        {";", "L;"},
        {",", "L,"},
        {"(", "L("},
        {")", "L)"},
        {":", "L:"},
        {"=", "L="},
        {"<", "L<"},
        {">", "L>"},
        {"<=", "L<="},
        {">=", "L>="},
        {"<>", "L<>"},
        {"+", "L+"},
        {"-", "L-"},
        {"*", "L*"},
    };
    
    start();
}


void Analex::PROXIMO(){                     //Função PRÓXIMO, que coloca na variável proximo o próximo caractere da cadeia e verifica se não é quebra linha, conta as linhas também
    proximo = tolower(arqOrig.get());
    if(proximo == '\n'){
        contador++;
    }
}

string Analex::CODIGO(string s){            //Função CÓDIGO, analisa se é palavra reservada ou simbolo especial e retorna o código associado ao átomo
    if(EH_PALAVRA_RESERVADA){
        return palavras_reservadas[s];
    }
    else{
        return simbolos_especiais[s];
    }
}

void Analex::ERRO(){                        //Função ERRO, que informa em que linha ocorreu um erro.
    cout<< "Erro na linha " << contador << endl;
};

bool Analex::buscaLetra(){                 //Função que verifica se o proximo é alguma letra

    for(char c : letras){
        if(proximo == c)
            return true;
    }

    return false;
}


bool Analex::buscaDigitos(){                //Função que verifica se o proximo é algum digito

    for(char c : digitos){
        if(proximo == c)
            return true;
    }

    return false;
}

bool Analex::verificaSimbolosEspeciais(){       //Função que verifica se proximo é algum símbolo especial
    for(char c : simbolos){
        if(proximo == c)
            return true;
    }

    return false;
}

string Analex::codigoDeIdentificador(){         //Função que atribui um código de identificador a um novo átomo identificador, ou se ja existir, retorna o código que ja existe
    auto it = find(identificadores.begin(), identificadores.end(),atomo);

    if(it != identificadores.end()){
        int indice = distance(identificadores.begin(),it);
        return "id" + to_string(indice);
    }
    else{
        identificadores.push_back(atomo);
        return "id" + to_string(identificadores.size()-1);
    }
}

string Analex::codigoDeNumero(){            //Função que atribui um código de número a um novo número, ou se ja existir, retorna o código que ja existe
    auto it = find(numeros.begin(), numeros.end(),atomo);

    if(it != numeros.end()){
        int indice = distance(numeros.begin(),it);
        return "num" + to_string(indice);
    }
    else{
        numeros.push_back(atomo);
        return "num" + to_string(numeros.size()-1);
    }
}

void Analex::verificaPalavra(){         //Função que verifica se o átomo é palavra reservada ou apenas identificador

    do{
        atomo += proximo;
        PROXIMO();
    }while(buscaLetra() || buscaDigitos());
    
    ok = false;
    
    if(palavras_reservadas.count(atomo)){
        EH_PALAVRA_RESERVADA = true;
        simbolo = CODIGO (atomo);
    }

    else
        simbolo = codigoDeIdentificador();


}



void Analex::start(){                  //Função que dá inicio ao algoritmo
    arqOrig.open("Exemplo1_Trab2_Compiladores.txt");
    arqObj.open("saida.txt");
    contador = 1;
    string s;
    bool erro;

    PROXIMO();

    while(proximo!=EOF){
        
        atomo.clear();
        simbolo.clear();
        ok = true;
        erro = false;

        while(proximo == ' ' || proximo == '	' || proximo == '\n'){
            arqObj << proximo;
            PROXIMO();
        }

        if(proximo != EOF){
            if(verificaSimbolosEspeciais()){
                s.clear();
                s += proximo;
                PROXIMO();
                if(s == ":" && proximo == '=')
                    s+=proximo;
                else if (s == "<" && proximo == '=')
                    s+=proximo;
                else if (s == ">" && proximo == '=')
                    s+=proximo;
                else if (s == "<" && proximo == '>')
                    s+=proximo;
                else
                    ok = false;
                EH_PALAVRA_RESERVADA = false;
                simbolo = CODIGO(s);

            }
    
            else if(buscaLetra()){
                verificaPalavra();
            }   

            else if(buscaDigitos()){
                do{
                    atomo += proximo;
                    PROXIMO();
                }while(buscaDigitos());
                ok = false;
                if(buscaLetra()){
                    erro = true;
                    ERRO();
                }

                else{   
                    simbolo = codigoDeNumero();
                }
                
            }   
            else{
                erro = true;
                ERRO();
            }

            if(!erro)
            arqObj << simbolo << ' ';

            if(ok)
                PROXIMO();
        }
        
    }

    
    arqOrig.close();
    arqObj.close();



}







