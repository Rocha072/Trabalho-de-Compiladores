#include "AnaSint.h"


Anasint :: Anasint(){
    error = false;
    start();
}


void Anasint :: prox_token(){
    
    token.clear();
    char c;

    
    while (arqLex.get(c)) {
        if (c == '\n') 
            contador++;
        if (!isspace(c))
            break;
    }

    
    if (arqLex.eof()) 
        return;

    
    token += c;

    
    while (arqLex.get(c)) {
        if (c == '\n') 
            contador++;
        if (isspace(c)) 
            break;
        token += c;
    }
}


void Anasint :: erro(string mensagem){
    error = true;
    cout << "Deu erro na linha " << contador << "   token atual:" << token << endl;
    cout << mensagem << endl << endl;
}


void Anasint :: program(){                                 //Funcao 1
    prox_token();

    if(token == "Lprog"){
        prox_token();
        if(identificador()){
            prox_token();
            if(token == "L;"){
                prox_token();
                if(bloco()){
                    if(token == "L.")
                        return;
                    else
                        erro("falta de ponto final");
                }
                else 
                    erro("falta de bloco de comandos");
            }
            else
                erro("falta de ponto e virgula");
        }
        else
            erro("esperava-se identificador");
                    
    }
    else
        erro("esperava-se \"program\"");
}


bool Anasint :: bloco(){                                   //Funcao 2
    bool certo = false;

    
    if(parte_de_declaracoes_de_variaveis())
        certo = true;
    
    if(parte_de_declaracoes_de_subrotinas())
        certo = true;

        
    if(comando_composto())
        certo = true;

    else if(certo)
        erro("esperava-se pelo menos um comando");

    

    return certo;

    
}


bool Anasint :: parte_de_declaracoes_de_variaveis(){       //Funcao 3
    string ulttok;
    if(token=="Lvar"){
        prox_token();
        if(declaracao_de_variaveis()){
            ulttok = token;
            while(token == "L;"){
                ulttok = token;
                prox_token();
                if(!declaracao_de_variaveis())
                    break;
            }

            if(ulttok != "L;")
                erro("falta de ponto e virgula");
                
        }
        else
            erro("esperava-se declaração de variaveis");
        return true;
    }
    else
        return false;
    

}


bool Anasint :: declaracao_de_variaveis(){                 //Funcao 4

    if(lista_de_identificadores()){
        if(token == "L:"){
            prox_token();
            if(token=="Lint" || token == "Lbool")
                prox_token();                  
            else
                erro("esperava-se tipo");
        }
        else
            erro("falta de dois pontos");

        return true;
    }
    else
        return false;

    
}


bool Anasint :: lista_de_identificadores(){                //Funcao 5
    if(identificador()){
        prox_token();
        while(token=="L,"){
            prox_token();
            if(identificador()){
                prox_token();
            }
            else
                break;
        }
        return true;
    }
    else
        return false;

}


bool Anasint :: parte_de_declaracoes_de_subrotinas(){      //Funcao 6
    bool certo = false;

    while(declaracao_de_procedimento() || declaracao_de_funcao()){
        if(token=="L;"){
            prox_token();
        }
        else
            erro("falta de ponto e virgula");                  
        certo = true;   
    }
            
    return certo;

    
}


bool Anasint :: declaracao_de_procedimento(){              //Funcao 7
    if(token=="Lproc"){              
        prox_token();

        if(identificador()){
            prox_token();
            parametros_formais();
            if(token=="L;"){
                prox_token();
                if(!bloco())
                    erro("falta de bloco de comandos");
                
            }
            else
                erro("falta de ponto e virgula");
        }
        else
            erro("falta de identificador");

        return true;
    }
    else
        return false;
}


bool Anasint :: declaracao_de_funcao(){                    //Funcao 8
    if(token=="Lfunc"){
        prox_token();

        if(identificador()){
            prox_token();
            parametros_formais();
            if(token=="L:"){
                prox_token();
                if(token == "Lint" || token == "Lbool"){
                    prox_token();
                    if(token=="L;"){
                        prox_token();
                        if(!bloco())
                            erro("falta de bloco");
                    }
                    else
                        erro("falta de ponto e virgula");
                }
                else
                    erro("falta de tipo");       
            }
            else
                erro("falta de dois pontos");
        }
        else
        erro("falta de identificador");
        return true;
    }
    else
        return false;
}


void Anasint :: parametros_formais(){                      //Funcao 9

    if(token=="L("){
        prox_token();
        if(secao_de_parametros_formais()){
            
            while(token=="L;"){
                prox_token();
                if(!secao_de_parametros_formais()){
                    erro("falta de seção de parametros formais");
                    break;
                }
            }

            if(token=="L)")
                prox_token();
            else
                erro("falta de \')\'");

        }
        else
            erro("falta de seção de parametros formais");
    }
    else
        return;
}


bool Anasint :: secao_de_parametros_formais(){             //Funcao 10
    if(token=="Lvar"){
        prox_token();
        if(lista_de_identificadores()){
            if(token=="L:"){
                prox_token();
                if(token == "Lint" || token == "Lbool")
                    prox_token();
                else
                    erro("falta de tipo");
            }
            else
                erro("falta de dois pontos");
        }
        else
            erro("falta de lista de identificador");

        return true;
    }

    else if(lista_de_identificadores()){
        if(token=="L:"){
            prox_token();
            if(identificador())
                prox_token();
            else
                erro("falta de identificador");
        }
        else
            erro("falta de dois pontos");

        return true;
    }

    else
        return false;
        
}


bool Anasint :: comando_composto(){                        //Funcao 11

    if(token == "Lbeg"){
        prox_token();
        
        if(comando()){

            while(token=="L;"){
                prox_token();
                if(!comando()){
                    
                    erro("falta de outro comando");
                    break;
                }
            }

            if(token == "Lend")               
                prox_token();
            else
                erro("falta de \"end\"");
            
            
        }
        else
            erro("falta de comando");

        return true;
    }   
    else
        return false;
}


bool Anasint :: comando(){                                 //Funcao 12
    if(numero()){

        if(token == "L:"){
            prox_token();
            if(!comando_sem_rotulo())
                erro("falta de comando sem rotulo");
        }
        else
            erro("falta de dois pontos");
        

        return true;
    }
        
    else if(comando_sem_rotulo()){
        return true;
    }

    else
        return false;
}


bool Anasint :: comando_sem_rotulo(){                      //Funcao 13
    bool certo = false;

    if(atribuicao()){
        certo = true;
    }

    if(chamada_de_procedimento())
        certo = true;


    else if(comando_composto())
        certo = true;

    else if(comando_condicional())
        certo = true;   

    else if(comando_repetitivo())
        certo = true;

    return certo;
}


bool Anasint :: atribuicao(){                              //Funcao 14

    bool certo = false;

    if(variavel()){
    
        prox_token();
        if(token == "L:="){
            prox_token();
            if(!expressao())
                erro("falta de expressão");

            certo = true;
        }
        
        certo = true;
    }

    return certo;
}


bool Anasint :: chamada_de_procedimento(){                 //Funcao 15
    bool certo = false;

    if(identificador()){
        prox_token();
        certo = true;
    }
    
    if(token=="L("){
        prox_token();
        if(lista_de_expressoes()){
            if(token == "L)")
                prox_token();
            else
                erro("esperava-se \")\"");
        }
        else
            erro("falta de lista de expressões");
        certo = true;
    }

    
    return certo;
}


bool Anasint :: comando_condicional(){                     //Funcao 16
    if(token=="Lif"){
        prox_token();

        if(expressao()){

            if(token=="Lthen"){
                prox_token();

                if(comando_sem_rotulo()){
                    if(token=="Lelse"){
                        prox_token();
                        if(!comando_sem_rotulo())
                            erro("falta de comando sem rótulo");
                    }
                }
                else
                    erro("falta de comando sem rótulo");
            }
            else
                erro("falta de \"then\"");
        }
        else
            erro("falta de expressao");

        return true;
    }
    else
        return false;
}


bool Anasint :: comando_repetitivo(){                      //Funcao 17
    if(token=="Lwhile"){
        prox_token();

        if(expressao()){

            if(token=="Ldo"){
                prox_token();

                if(!comando_sem_rotulo()){
                    erro("falta de comando sem rótulo");
                }

            }
            else
                erro("falta de \"do\"");
        }
        else
            erro("falta de expressao");

        return true;
    }
    else
        return false;
}


bool Anasint :: lista_de_expressoes(){                     //Funcao 18
    if(expressao()){
        while(token=="L,"){
            prox_token();
            if(!expressao()){
                erro("falta de expressao");
                break;
            }
        }

        return true;
    }
    else
        return false;
}


bool Anasint :: expressao(){                               //Funcao 19
    if(expressao_simples()){

        if(relacao()){
            if(!expressao_simples())
                erro("falta de expressao simples");
        }

        return true;
    }   
    else
        return false;
}


bool Anasint :: relacao(){                                 //Funcao 20
    if(token == "L=" || token == "L<>" || token == "L<" || token == "L<=" || token == "L>=" || token == "L>"){
        prox_token();
        return true;
    }
    else
        return false;
}


bool Anasint :: expressao_simples(){                       //Funcao 21
    bool certo = false;

    if(token == "L+" || token == "L-"){
        prox_token();
        certo = true;
    }

    if(termo()){
        while(token == "L+" || token == "L-" || token == "Lor"){
            prox_token();
            if(!termo()){
                erro("falta de termo");
                break;
            }
        }

        certo = true;
    }

    else if(certo)
        erro("falta de termo");

    return certo;

}


bool Anasint :: termo(){                                   //Funcao 22
    if(fator()){
        while(token == "L*" || token == "Ldiv" || token == "Land"){
            prox_token();
            if(!fator()){
                erro("falta de fator");
                break;
            }
        }

        return true;
    }   
    else
        return false;
}


bool Anasint :: fator(){                                   //Funcao 23
    bool certo = false;

    if(variavel())
        certo = true;

    if(chamada_de_funcao())
        certo = true;

    else if(numero())
        certo = true;

    

    else if(token == "L("){
        prox_token();
        if(expressao()){
            if(token=="L)")
                prox_token();
            else
                erro("esperava-se \")\""); 
        }
        else
            erro("falta de expressao");
        certo = true;
    }

    else if(token == "Lnot"){
        prox_token();
        if(!fator())
            erro("falta de fator");
        certo = true;
    }

    return certo;

}


bool Anasint :: variavel(){                                //Funcao 24
    if(identificador())
        return true;
    else
        return false;

}


bool Anasint :: chamada_de_funcao(){                       //Funcao 25
    if(identificador()){
        prox_token();
        if(token=="L("){
            prox_token();
            if(lista_de_expressoes()){
                if(token == "L)")
                    prox_token();
                else
                    erro("falta de \")\"");
            }
            else
                erro("falta de lista de expressões");
        }

        return true;
    }

    else
        return false;
}


bool Anasint :: numero(){                                  //Funcao 26
    char c = token[0];
    int i = 0;
    if(c=='n'){
        i++;
        c = token[i];
        while( i < static_cast<int>(token.length()) && (letra(c) || digito(c)) ){
            c = token[i];
            i++;
        }
        
        prox_token();
        return true;
    }
    else
        return false;
}


bool Anasint :: digito(char l){                            //Funcao 27
    return isdigit(l);
}


bool Anasint :: identificador(){                           //Funcao 28
    char c = token[0];
    int i = 0;
    if(c=='i'){
        i++;
        c = token[i];
        while( i < static_cast<int>(token.length()) && (letra(c) || digito(c)) ){
            c = token[i];
            i++;
        }
        
        return true;
    }
    else
        return false;
}


bool Anasint :: letra(char l){                             //Funcao 29
    return isalpha(l);
}



void Anasint :: start(){
        contador = 1;
        arqLex.open("saida.txt");

        if(!arqLex.is_open())
            cout << "Nao abriu o arquivo";
        else{
            program();
            if(!error)
                cout << "Analise sintatica bem sucedida";

            arqLex.close();
        }
    }




