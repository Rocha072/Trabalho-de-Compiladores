# 🖥️ Analisador Léxico e Sintático - Pascal Simplificado

Este projeto implementa um **Analisador Léxico e Sintático** em **C++** para uma versão simplificada da linguagem **Pascal**.  
Ele faz a leitura de um código-fonte, identifica os **tokens** e realiza a análise sintática conforme a gramática definida.

---

## 📌 Funcionalidades

- **Análise Léxica**: 
  - Identifica palavras-chave, identificadores, números, símbolos e operadores.
  - Ignora espaços e quebras de linha irrelevantes.
- **Análise Sintática**: 
  - Verifica se a sequência de tokens segue a gramática da linguagem Pascal simplificada.
  - Aponta erros de sintaxe indicando a linha.
---

## 📂 Estrutura do Projeto
```plaintext
📁 Trabalho-de-Compiladores/       
 ├── AnaLex.cpp       # Implementação do analisador léxico
 ├── AnaLex.h         # Cabeçalho do analisador léxico
 ├── AnaSint.cpp      # Implementação do analisador sintático
 ├── AnaSint.cpp      # Cabeçalho do analisador sintático
 ├── Exemplo_1_Trab2_Compiladores.txt  # Exemplo de entrada do Compilador
 ├── Main.cpp         # Arquivo principal
 ├── Main.cpp         # Executavel
 ├── README.md        # Este arquivo
 └── saida.txt        # Exemplo de saida da analise léxica
