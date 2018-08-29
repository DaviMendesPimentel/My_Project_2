#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "Trab_ClassDef.h"

using namespace std;

/** ESTRUTURA ENUM DE CONTROLE DE DECIS�ES*/
enum escolha{ CRIAR = 1, LER, APAGAR, ATUALIZAR, FINALIZAR_PROGRAMA };

/** MAIN EM A��O */
int main()
{
    int choice;
    setlocale(LC_ALL, "Portuguese");
    Trab_ClassDef t;

    do{

    try{
        cout << "Bem vindo ao meu programa:" << endl;
        cout << "Fun��o \"lerArquivo\" chamada: " << endl;
        int i;
        cout << '\n';
        for(i = 0; i < 80; i++)
            cout << "-";
        //t.lerArquivo();

        cout << "Digite uma op��o de escolha: " << endl;

        Inc_Choice:
        t.instrucoes();
        cin >> choice;

        switch(choice){
        case CRIAR:
            cout << "fun��o criarArquivo chamada" << endl;
            t.criarTrabalho();
            break;
        case LER:
            cout << "fun��o lerArquivo chamada" << endl;
            t.lerArquivo();
            break;
        case APAGAR:
            cout << "fun��o apagar_arquivo chamada" << endl;
            t.apagarTrabalho();
            break;
        case ATUALIZAR:
            cout << "fun��o atualizar_arquivo chamada" << endl;
            t.atualizarTrabalho();
            break;
        case FINALIZAR_PROGRAMA:
            cout << "Fim do programa :)" << endl;
            goto end_program;
        default:
            cout << "insira um valor v�lido.";
            goto Inc_Choice;
    }
    }
    catch(const char* message){
        cout << message << endl;
    }
    catch(...){
        cout << "Erro inesperado ocorreu." << endl;
        exit(1);
    }

    }while(choice != FINALIZAR_PROGRAMA);

    end_program:
    return 0;
}

