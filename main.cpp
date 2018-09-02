#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "Trab_ClassDef.h"
#include <locale.h>

using namespace std;

// estrutura enum para controle de entrada
enum escolha{ CRIAR = 1, LER, APAGAR, ATUALIZAR, FINALIZAR_PROGRAMA };

// main em acao
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int choice;		// variavel escolha criada
    Trab_ClassDef t;	// objeto trabalho criado

    do{		// cria um laço

    try{	// tentará executar este código
        cout << "Bem vindo ao meu programa:" << endl;
        cout << "Função \"lerArquivo\" chamada: " << endl;
        int i;	// cria um iterador
        cout << '\n';	// executa uma quebra de linha
        for(i = 0; i < 80; i++)	// itera até que o prompt seja preenchido
            cout << "-";

        cout << "Digite uma opção de escolha: " << endl;// pede uma entrada

        Inc_Choice:	// cria uma referência ao goto
        t.instrucoes();	// informa as intruções de entrada
        cin >> choice;	// insere um valor em choice

	// teste se o valor, e executa algo com base em choice
        switch(choice){	// cria uma estrutura de caso
        case CRIAR:	// caso o valor seja 1:
            cout << "função criarTrabalho chamada" << endl;
            t.criarTrabalho();	// chama a função criarTrabalho
            break;	// encerra o caso
        case LER:	// caso o valor seja 2:
            cout << "função lerArquivo chamada" << endl;
            t.lerArquivo();	// chama a função lerArquivo
            break;	// encerra o caso
        case APAGAR:	// caso o valor seja 3:
            cout << "função apagarTrabalho chamada" << endl;
            t.apagarTrabalho();	// chama a função apagarTrabalho
            break;	// encerra o caso
        case ATUALIZAR:	// caso o valor seja 4:
            cout << "função atualizarTrabalho chamada" << endl;
            t.atualizarTrabalho();	// chama a função atualizarTrabalho
            break;	// encerra o caso
        case FINALIZAR_PROGRAMA:	// caso o valor seja 5:
            cout << "Fim do programa :)" << endl;
            goto end_program;	// utiliza o goto para ir para o fim
				// do programa
        default:	// caso o valor seja inválido(> 5 && < 1):
            cout << "insira um valor válido.";
            goto Inc_Choice;	// utiliza o goto para retornar ao início
    }	// fim de switch
    }	// fim de try
    catch(const char* message){	// captura uma exceção const char *
        cout << message << endl; // message é impresso
    }	// fim de catch const char *
    catch(...){	// captura todas as exceções que passarem pelos catchs (erros inesperados)
        cout << "Erro inesperado ocorreu." << endl;	// informa ao usuário que ocorreu um erro
        exit(1);	// aborta o programa
    }	// fim de catch(...)

    }while(choice != FINALIZAR_PROGRAMA); // testa se o valor é diferente de 5 (novamente)

    end_program:	// referência para goto para o fim do programa
    return 0;	// finaliza o programa
}
