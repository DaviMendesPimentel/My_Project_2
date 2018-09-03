#include "Trab_ClassDef.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template< typename Any_type>
void Trabalho_update(Any_type *valor_legado, Any_type *new_val)
{
    valor_legado = new_val;

    if(new_val != valor_legado){
        const char * message_upFailure = "Falha na atualizacao";
        throw message_upFailure;
    }
}


Trab_ClassDef::Trab_ClassDef(int num_T, int d, int m, int a, int norma,
                            char * nome_T, char * nome_M, char * comp)
{
    num_trab = ((num_T >= 1 && num_T <= 100) ? num_T : 0);
    dia = ((d >= 1 && d <= 31) ? d : 1);
    mes = ((m >= 1 && m <= 12) ? m : 1);
    ano = (a >= 2018 ? a : 2018);
    abnt = (norma != 0 ? 1 : 0);
    nome_do_trabalho[75] = *nome_T;
    nome_da_materia[75] = *nome_M;
    complemento[200] = *comp;
}

void Trab_ClassDef::atualizarTrabalho()
{
    const char * Numb_trab_fail = "Numero de trabalho inexistente"; //cria uma mensagem de falha
    const char * inicio = "Voltou ao inicio";           //cria uma mensagem de para retorno de inicio
    const char * update_sucess = "Trabalho atualizado com sucesso"; //cria uma mensagem de sucesso
    enum atualizar_escolha{ DIA = 1, MES, ANO,                          //cria uma enumera��o
                            ABNT, NOME_TRAB, NOME_MAT, COMPLEMENTO, INICIO};
    cout << "Digite o numero do trabalho: ";    //pede o n�mero do trabalho
    cin >> this->num_trab;  //insere o n�mero do trabalho
    if(!this->verify()) //verifica se o n�mero existe
        throw Numb_trab_fail;   //dispara uma exce��o

    ifstream Arquivo_entrada("Trabalhos.dat", ios::binary); //abre um arquivo para entrada de dados

    if(!Arquivo_entrada){   //verifica se o arquivo foi aberto com sucesso
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;  //se o arquivo n�o foi aberto com sucesso, dispara uma exce��o
    }
    Trab_ClassDef t;    //cria um objeto default de Trab_ClassDef
    Arquivo_entrada.seekg(this->num_trab * sizeof(Trab_ClassDef)); //direciona o ponteiro de leitura
    Arquivo_entrada.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef));  //l� os dados do arquivo

    invalid_valor:  //refer�ncia para goto para um valor inv�lido
    int choice; //cria uma vari�vel de escolha
    cout << "Digite um campo a alterar: " << endl;  //pede o campo a ser alterado
    this->instrucoesUpdate();   //mostra as intru��es de atualiza��o de dados
    cin >> choice;  //insere um valor e armazena-o em choice

    switch(choice){ //com base em choice, realiza a estrutura mais adequada
    case DIA:   //estrutura para alterar o dia
        cout << "Digite o novo dia a ser inserido: " << endl;  //pede um novo dia a ser inserido
        int update_dia;
        cin >> update_dia;
        Trabalho_update(&t.dia, &update_dia);
        break;
    case MES:
        cout << "Digite o novo mes a ser inserido: " << endl;
        int update_mes;
        cin >> update_mes;
        Trabalho_update(&t.mes, &update_mes);
        break;
    case ANO:
        cout << "Digite o novo ano a ser inserido: " << endl;
        int update_ano;
        cin >> update_ano;
        Trabalho_update(&t.ano, &update_ano);
    case ABNT:
        cout << "Digite o novo valor da abnt: " << endl;
        int update_abnt;
        cin >> update_abnt;
        Trabalho_update(&t.abnt, &update_abnt);
        break;
    case NOME_TRAB:
        cout << "Digite o novo valor a ser alocado: " << endl;
        char update_NT[75];
        cin >> update_NT;
        Trabalho_update(t.nome_do_trabalho, update_NT);
        break;
    case NOME_MAT:
        cout << "Digite o novo valor a ser alocado: " << endl;
        char update_NM[75];
        cin >> update_NM;
        Trabalho_update(t.nome_da_materia, update_NM);
        break;
    case COMPLEMENTO:
        cout << "Digite o novo valor a ser alocado: " << endl;
        char update_complemento[200];
        cin >> update_complemento;
        Trabalho_update(t.complemento, update_complemento);
        break;
    case INICIO:
        goto voltar_ao_inicio;
        break;
    default:
        cout << "Valor inv�lido" << endl;
        goto invalid_valor;
    }
    voltar_ao_inicio:
    if(choice == 8)
        throw inicio;

    Arquivo_entrada.close();
    ofstream Arquivo_saida("Trabalhos.dat", ios::binary);

    if(!Arquivo_saida){
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;
    }
    Arquivo_saida.seekp((this->num_trab - 1) * sizeof(Trab_ClassDef));
    Arquivo_saida.write(reinterpret_cast<const char *>(&t), sizeof(Trab_ClassDef));

    throw update_sucess;
}

//Fun��o apagarTrabalho():
void Trab_ClassDef::apagarTrabalho()
{
    const char * message_invalid = "trabalho inexistente";  //cria uma mensagem para falha
    const char * message_dellSucess = "Trabalho deletado com sucesso!"; //cria uma mensagem para sucesso

    ofstream Arquivo_Teste("Trabalhos.dat", ios::binary);   //abre arquivo para saida de dados

    cout << "Insira o n�mero do Trabalho: ";    //pede o n�mero do trabalho para verifica��o
    cin >> this->num_trab;  //insere o n�mero do trabalho

    if(this->verify()){ //verifica se o n�mero existe
        Trab_ClassDef t;    //cria um objeto com valor nulos(objeto default)
        Arquivo_Teste.seekp((this->num_trab - 1) * sizeof(Trab_ClassDef));  //direciona o ponteiro de leitura
        Arquivo_Teste.write(reinterpret_cast<const char *>(&t), sizeof(Trab_ClassDef)); //grava os dados do objeto
                                                                            //default "t" no arquivo
        throw message_dellSucess;   //dispara a mensagem de sucesso
    }
    else    //de o n�mero n�o existir
        throw message_invalid;  //dispara a mensagem de falha
}

//fun��o lerArquivo():
void Trab_ClassDef::lerArquivo()
{
    ifstream inPutReader("Trabalhos.dat", ios::binary); //abre arquivo para leitura bin�ria
    Trab_ClassDef t;    //cria um objeto Trab_ClassDef
    int Trabalhos_Pendentes = 0;    //cria uma vari�vel para guardar a quantidade
                                    //de trabalhos pendentes
    if(!inPutReader){   //verifica se o arquivo conseguiu ser aberto com sucesso
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;  //se o arquivo falhou na abertura, dispara uma exce��o
    }
    inPutReader.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef)); //l� o arquivo desde o in�cio
                                                                    //lembrando que n�o foi utilizado o seekg()
    while(inPutReader && !inPutReader.eof()){   //verifica se o arquivo n�o chegou ao fim
        if(t.num_trab != 0){         //verifica se o numero do trabalho � diferente de 0
            this->printTrabalho(t); //se o numero do trabalho for diferente de 0, imprime os dados desse trabalho
            ++Trabalhos_Pendentes;  //incrementa o valor de Trabalhos_Pendentes
        }

        inPutReader.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef));  //l� o pr�ximo Trabalho
    }
    if(Trabalhos_Pendentes > 0) //verifica se existem trabalhos pendentes
        cout << "\nNumero de trabalhos pendentes: " << Trabalhos_Pendentes << endl; //imprime a quantidade de
                                                                                    //trabalhos pendentes
    else    //se n�o existirem trabalhos pendentes:
        cout << "\nNenhum trabalho pendente" << endl; //informa que n�o existem trabalho a serem concluidos
}

//fun��o criarTrabalho():
void Trab_ClassDef::criarTrabalho()
{
    ofstream outPutWrite("Trabalhos.dat", ios::binary); //abre arquivo para saida no estilo bin�rio
    Trab_ClassDef t;    //cria um objeto Trab_ClassDef

    if(!outPutWrite){ //verifica se o arquivo conseguiu ser aberto com sucesso
        const char * message_failure = "erro na fun��o criarArquivo";
        throw message_failure;  //se o arquivo falhou na abertura, dispara uma exce��o
    }
    t.funcaoAmzData();   //chama a fun��o funcaoAmzData() atraves do objeto "t"

    outPutWrite.seekp((t.num_trab -1) * sizeof(Trab_ClassDef));  //Direciona o ponteiro de leitura

    outPutWrite.write(reinterpret_cast<const char *>(&t), sizeof(Trab_ClassDef));    //escreve os dados armazenados
                                                                                //no arquivo aberto
}

//fun��o utilit�ria para colher dados
void Trab_ClassDef::funcaoAmzData()
{
    const char *message_sucess = "Numero Permitido.\n"; //cria uma mensagem de sucesso
    const char *message_failure = "Numero inv�lido ou j� preenchido.\n";    //cria uma mensagem de falha

    cout << "Num. do Trabalho: ";
    cin >> num_trab;    //colhe o n�mero do trabalho
    if(this->verify())    //verifica se o n�mero do trabalho est� v�lido para uso
        throw message_failure;  //se o n�mero estiver invalido, dispara uma exce��o
    else    //se n�o:
        cout << message_sucess; //exibe uma mensagem de validez de n�mero - mensagem de sucesso

    cout << "\n\nNome do Trabalho: ";   //pede o nome do trabalho
    cin.ignore();
    cin.getline(nome_do_trabalho, 75);  //l� o nome do trabalho

    cout << "Nome da Mat�ria: ";        //pede o nome da materia
    cin.getline(nome_da_materia, 75);   //l� o nome da materia

    cout << "Data de entrega: ";        //pede a data de entrega
    cout << "Dia: ";                    //pede o dia de entrega
    cin >> setw(2) >> dia;              //l� apenas dois d�gitos e armazena-os em "dia"
    cout << setw(22) << "M�s: ";        //pede o mes de entrega
    cin >> setw(2) >>mes;               //l� apenas dois d�gitos e armazena-os em "mes"
    cout << setw(22) << "Ano: ";        //pede o ano de entrega
    cin >> setw(4) >> ano;              //l� quatro d�gitos e armazena-os em "ano"
    cout << "\n\nABNT? (0 para \"falso\" e \nqualquer outro valor para \"true\": "; //instrui o usu�rio sobre ABNT
    cin >> abnt;                        //l� um valor e armazena-os em "abnt"

    cout << "Complemento:\n";       //pede um complemento(se tiver)
    cin.ignore();                   //ignora o '\n' da linha � cima(linha 72)
    cin.getline(complemento, 200);  //l� o complemento e armazena-o em "complemento"
}

//fun��o utilit�ria para verificar num_trab:
bool Trab_ClassDef::verify()
{
    ifstream Input_file("Trabalhos.dat", ios::binary); // abre arquivo para entrada no estilo bin�rio
    Trab_ClassDef t;     //cria um objeto Trab_ClassDef

    if(!Input_file){    //verifica se o arquivo conseguiu ser aberto com sucesso
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;  //se o arquivo falhou na abertura, dispara uma exce��o
    }
    Input_file.seekg((this->num_trab - 1) * sizeof(Trab_ClassDef));  //direcionando o ponteiro de leitura

    Input_file.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef)); //lendo dados e transferindo-os
                                                                        //para o objeto "t"

    if(t.num_trab != 0 && t.num_trab == this->num_trab) //verifica se o numero do trabalho � valido
        return true;        //se o numero for inv�lido (i.e.,se o n�mero ja existir) retorna true

    return false; //se n�o, retorna false
}

//fun��o utilit�ria para imprimir dos dados do trabalho na tela:
void Trab_ClassDef::printTrabalho(Trab_ClassDef &tRef)
{
    int i;
    cout << "\n";

    cout << "\nNum. do Trabalho: " << tRef.num_trab
         << ios::right << "Data de entrega: "
         << (tRef.dia < 10 ? "0" : "") << tRef.dia << "/"
         << (tRef.mes < 10 ? "0" : "") << tRef.mes << "/"
         << tRef.ano << endl;
    cout << "Trabalho: " << tRef.nome_do_trabalho
         << "\nMat�ria: " << tRef.nome_da_materia << "\n\n"
         << "Complemento: \n" << tRef.complemento << "\n"
         << setw(15) << "ABNT: " << (tRef.abnt != 0 ? "sim" : "n�o") << endl;

    for(i = 0; i < 80; i++)
        cout << "-";

    cout << "\n\n";
}

//fun��o utilit�ria instrucoes():
inline void Trab_ClassDef::instrucoes()
{
    cout << "1 - criar trabalho\n"
         << "2 - ler trabalho\n"
         << "3 - apagar trabalho\n"
         << "4 - atualizar trabalho\n"
         << "5 - finalizar programa\n";
}

//fun��o utilit�ria instrucoesUpdate():
void Trab_ClassDef::instrucoesUpdate()
{
    cout << "1 - alterar dia de entrega\n"
         << "2 - alterar m�s de entrega\n"
         << "3 - alterar ano de entrega\n"
         << "4 - alterar abnt para falso ou verdadeiro\n"
         << "5 - alterar nome do trabalho\n"
         << "6 - alterar nome da mat�ria\n"
         << "7 - alterar complemento\n"
         << "8 - voltar ao in�cio" << endl;
}
