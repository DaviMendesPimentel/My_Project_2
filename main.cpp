#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;


/** ESTRUTURA ENUM DE CONTROLE DE DECISÕES*/
enum escolha{ CRIAR = 1, LER, APAGAR, ATUALIZAR, FINALIZAR_PROGRAMA };


/** ESTRUTURA DE VARIAVEIS DE UM OBJETO TRABALHO */
struct Trabalho{
    int numTrab;
    int dia, mes, ano, abnt;
    char nome_do_trabalho[75];
    char nome_da_materia[75];
    char complemento[200];

};

/** FUNÇÕES PRINCIPAIS */
const char* criarArquivo();
const char* lerArquivo();
const char* apagar_arquivo();
const char* atualizar_arquivo();

/** FUNÇÕES UTILITÁRIAS*/
void printArquivo(Trabalho &);
const char* funcao_amz_data(Trabalho &, ofstream &);
bool verify(int);
void instrucoes();
void instrucoes_Update();

template< typename Any_type>
void Trabalho_update(Any_type *valor_legado, Any_type *new_val)
{
    valor_legado = new_val;
    cout << "Valores Alterados com sucesso" << endl;
}

/** MAIN EM AÇÃO */
int main()
{
    int choice;
    setlocale(LC_ALL, "Portuguese");

    do{

    try{
        cout << "Bem vindo ao meu programa:" << endl;
        cout << "Função \"lerArquivo\" chamada: " << endl;
        int i;
        cout << "\n";
        for(i = 0; i < 80; i++)
            cout << "-";
        lerArquivo();

        cout << "Digite uma opção de escolha: " << endl;

        Inc_Choice:
        instrucoes();
        cin >> choice;

        switch(choice){
        case CRIAR:
            criarArquivo();
            break;
        case LER:
            lerArquivo();
            break;
        case APAGAR:
            apagar_arquivo();
            break;
        case ATUALIZAR:
            atualizar_arquivo();
            break;
        case FINALIZAR_PROGRAMA:
            goto end_program;
        default:
            cout << "insira um valor válido.";
            goto Inc_Choice;
    }
    }
    catch(const char* message){
        cout << "um erro ocorreu: " << message << endl;
    }
    catch(...){
        cout << "Erro inesperado ocorreu." << endl;
    }

    }while(choice != FINALIZAR_PROGRAMA);

    end_program:
    return 0;
}
void instrucoes()
{
    cout << "1 - CRIAR TRABALHO\n"
         << "2 - LER TRABALHOS\n"
         << "3 - APAGAR TRABALHO\n"
         << "4 - ATUALIZAR TRABALHO\n"
         << "5 - FINALIZAR PROGRAMA\n";
}

const char *criarArquivo()
{
    ofstream outPutWrite("outTest.dat", ios::binary);
    Trabalho t;

    if(!outPutWrite){
        const char * message = "erro na função criarArquivo";
        throw *message;
    }
    funcao_amz_data(t, outPutWrite);

    outPutWrite.seekp(t.numTrab * sizeof(Trabalho));

    outPutWrite.write(reinterpret_cast<const char *>(&t), sizeof(Trabalho));

}
const char *funcao_amz_data(Trabalho &trabRef, ofstream &fileRef)
{
    const char *message_sucess = "Numero Permitido.\n";
    const char *message_failure = "Numero inválido ou já preenchido.\n";

    cout << "Num. do Trabalho: ";
    cin >> trabRef.numTrab;
    if(verify(trabRef.numTrab))  /** VERIFICA SE NUMTRAB É VALIDO PARA INSERIR UM TRABALHO */
        throw *message_failure;
    else
        cout << message_sucess;

    cout << "\n\nNome do Trabalho: ";
    cin.ignore();
    cin.getline(trabRef.nome_do_trabalho, 75);

    cout << "Nome da Matéria: ";
    cin.ignore();
    cin.getline(trabRef.nome_da_materia, 75);

    cout << "Data de entrega: ";
    cout << "Dia: ";
    cin >> setw(2) >> trabRef.dia;
    cout << "Mês: ";
    cin >> trabRef.mes;
    cout << "Ano: ";
    cin >> setw(4) >> trabRef.ano;
    cout << "\n\nABNT? (0 para \"falso\" e \nqualquer outro valor para \"true\": ";
    cin >> trabRef.abnt;

    cout << "Complemento:\n";
    cin.ignore();
    cin.getline(trabRef.complemento, 200);
}

bool verify(int number_trab)
{
    ifstream Input_file("outTest.dat", ios::binary); /** ABRE O ARQUIVO PARA LEITURA BINARIA */
    Trabalho t;     /** CRIA UM OBJETO "TRABALHO" */

    if(!Input_file){
        const char * const message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw *message_failure;
    }
    Input_file.seekg(number_trab * sizeof(Trabalho));  /** PONTEIRO DE LEITURA INSERIDO NO NUMERO DO TRABALHO
                                                       VEZES O TAMANHO DE TRABALHO */

    Input_file.read(reinterpret_cast<char *>(&t), sizeof(Trabalho)); /** LENDO DADOS E TRANSFERINDO
                                                                    PARA O OBJETO "t" */

    if(t.numTrab != 0 && t.numTrab == number_trab)
        return true;

    return false;
}

const char *lerArquivo()
{
    ifstream inPutReader("outTest.dat", ios::binary);
    Trabalho t;
    int Trabalhos_Pendentes = 0;

    if(!inPutReader){
        const char * const message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw *message_failure;
    }
    inPutReader.read(reinterpret_cast<char *>(&t), sizeof(Trabalho));

    while(inPutReader && !inPutReader.eof()){
        if(t.numTrab != 0){
            printArquivo(t);
            ++Trabalhos_Pendentes;
        }

        inPutReader.read(reinterpret_cast<char *>(&t), sizeof(Trabalho));

    }
    cout << "\nNumero de trabalhos pendentes: " << Trabalhos_Pendentes << endl;
}

void printArquivo(Trabalho &trabRef)
{
    int i;
    cout << "\n";

    cout << "\nNum. do Trabalho: " << trabRef.numTrab << '\n';
    cout << "Trabalho: " << trabRef.nome_do_trabalho
         << ios::right << "\nData de entrega: "
         << (trabRef.dia < 10 ? "0" : "") << trabRef.dia << "/"
         << (trabRef.mes < 10 ? "0" : "") << trabRef.mes << "/"
         << trabRef.ano << endl
         << "\nMatéria: " << trabRef.nome_da_materia << "\n\n"
         << "Complemento: \n" << trabRef.complemento << "\n"
         << setw(15) << "ABNT: " << (trabRef.abnt != 0 ? "sim" : "não") << endl;

    for(i = 0; i < 80; i++)
        cout << "-";

    cout << "\n\n";
}

const char *apagar_arquivo()
{
    const char * const message_invalid = "trabalho inexistente";
    const char * const message_dellSucess = "Trabalho deletado com sucesso!";

    ofstream Arquivo_Teste("outTest.dat", ios::binary);
    int number_Two;

    int trab_number;
    cout << "Insira o número do Trabalho: ";
    cin >> trab_number;

    if(verify(trab_number)){
        Trabalho t = {0, 0, 0, 0, 0, "", "", ""};
        Arquivo_Teste.seekp(trab_number * sizeof(Trabalho));
        Arquivo_Teste.write(reinterpret_cast<const char *>(&t), sizeof(Trabalho));
        throw *message_dellSucess;
    }
    else
        throw *message_invalid;
}

const char *atualizar_arquivo()
{
    enum atualizar_escolha{ DIA = 1, MES, ANO,
                            ABNT, NOME_TRAB, NOME_MAT, COMPLEMENTO};
    cout << "Digite o numero do trabalho: ";
    int number_Trab; cin >> number_Trab;

    ifstream Arquivo_entrada("outTest.dat", ios::binary);

    if(!Arquivo_entrada){
        const char * const message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw *message_failure;
    }
    Trabalho t;
    Arquivo_entrada.seekg(number_Trab * sizeof(Trabalho));
    Arquivo_entrada.read(reinterpret_cast<char *>(&t), sizeof(Trabalho));

    invalid_valor:
    int choice;
    cout << "Digite um valor a alterar: " << endl;
    instrucoes_Update();
    cin >> choice;

    cout << "Digite o novo valor a ser alocado: " << endl;
    switch(choice){
    case DIA:
        int update_dia;
        cin >> update_dia;
        Trabalho_update(&t.dia, &update_dia);
        break;

    case MES:
        int update_mes;
        cin >> update_mes;
        Trabalho_update(&t.mes, &update_mes);
        break;

    case ANO:
        int update_ano;
        cin >> update_ano;
        Trabalho_update(&t.ano, &update_ano);

    case ABNT:
        int update_abnt;
        cin >> update_abnt;
        Trabalho_update(&t.abnt, &update_abnt);
        break;
    case NOME_TRAB:
        char update_NT[75];
        cin >> update_NT;
        Trabalho_update(t.nome_do_trabalho, update_NT);
        break;
    case NOME_MAT:
        char update_NM[75];
        cin >> update_NM;
        Trabalho_update(t.nome_da_materia, update_NM);
        break;
    case COMPLEMENTO:
        char update_complemento[200];
        cin >> update_complemento;
        Trabalho_update(t.complemento, update_complemento);
        break;

    default:
        cout << "Valor inválido" << endl;
        goto invalid_valor;
    }
}
void instrucoes_Update()
{
    cout << "1 - ALTERAR DIA DE ENTREGA\n"
         << "2 - ALTERAR MÊS DE ENTREGA\n"
         << "3 - ALTERAR ANO DE ENTREGA\n"
         << "4 - ALTERAR ABNT PARA FALSO OU VERDADEIRO\n"
         << "5 - ALTERAR NOME DO TRABALHO\n"
         << "6 - ALTERAR NOME DA MATÉRIA\n"
         << "7 - ALTERAR COMPLEMENTO\n"
         << "8 - VOLTAR AO INÍCIO" << endl;
}

