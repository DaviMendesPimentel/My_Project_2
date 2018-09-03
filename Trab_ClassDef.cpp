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
    enum atualizar_escolha{ DIA = 1, MES, ANO,                          //cria uma enumeração
                            ABNT, NOME_TRAB, NOME_MAT, COMPLEMENTO, INICIO};
    cout << "Digite o numero do trabalho: ";    //pede o número do trabalho
    cin >> this->num_trab;  //insere o número do trabalho
    if(!this->verify()) //verifica se o número existe
        throw Numb_trab_fail;   //dispara uma exceção

    ifstream Arquivo_entrada("Trabalhos.dat", ios::binary); //abre um arquivo para entrada de dados

    if(!Arquivo_entrada){   //verifica se o arquivo foi aberto com sucesso
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;  //se o arquivo não foi aberto com sucesso, dispara uma exceção
    }
    Trab_ClassDef t;    //cria um objeto default de Trab_ClassDef
    Arquivo_entrada.seekg(this->num_trab * sizeof(Trab_ClassDef)); //direciona o ponteiro de leitura
    Arquivo_entrada.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef));  //lê os dados do arquivo

    invalid_valor:  //referência para goto para um valor inválido
    int choice; //cria uma variável de escolha
    cout << "Digite um campo a alterar: " << endl;  //pede o campo a ser alterado
    this->instrucoesUpdate();   //mostra as intruções de atualização de dados
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
        cout << "Valor inválido" << endl;
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

//Função apagarTrabalho():
void Trab_ClassDef::apagarTrabalho()
{
    const char * message_invalid = "trabalho inexistente";  //cria uma mensagem para falha
    const char * message_dellSucess = "Trabalho deletado com sucesso!"; //cria uma mensagem para sucesso

    ofstream Arquivo_Teste("Trabalhos.dat", ios::binary);   //abre arquivo para saida de dados

    cout << "Insira o número do Trabalho: ";    //pede o número do trabalho para verificação
    cin >> this->num_trab;  //insere o número do trabalho

    if(this->verify()){ //verifica se o número existe
        Trab_ClassDef t;    //cria um objeto com valor nulos(objeto default)
        Arquivo_Teste.seekp((this->num_trab - 1) * sizeof(Trab_ClassDef));  //direciona o ponteiro de leitura
        Arquivo_Teste.write(reinterpret_cast<const char *>(&t), sizeof(Trab_ClassDef)); //grava os dados do objeto
                                                                            //default "t" no arquivo
        throw message_dellSucess;   //dispara a mensagem de sucesso
    }
    else    //de o número não existir
        throw message_invalid;  //dispara a mensagem de falha
}

//função lerArquivo():
void Trab_ClassDef::lerArquivo()
{
    ifstream inPutReader("Trabalhos.dat", ios::binary); //abre arquivo para leitura binária
    Trab_ClassDef t;    //cria um objeto Trab_ClassDef
    int Trabalhos_Pendentes = 0;    //cria uma variável para guardar a quantidade
                                    //de trabalhos pendentes
    if(!inPutReader){   //verifica se o arquivo conseguiu ser aberto com sucesso
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;  //se o arquivo falhou na abertura, dispara uma exceção
    }
    inPutReader.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef)); //lê o arquivo desde o início
                                                                    //lembrando que não foi utilizado o seekg()
    while(inPutReader && !inPutReader.eof()){   //verifica se o arquivo não chegou ao fim
        if(t.num_trab != 0){         //verifica se o numero do trabalho é diferente de 0
            this->printTrabalho(t); //se o numero do trabalho for diferente de 0, imprime os dados desse trabalho
            ++Trabalhos_Pendentes;  //incrementa o valor de Trabalhos_Pendentes
        }

        inPutReader.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef));  //lê o próximo Trabalho
    }
    if(Trabalhos_Pendentes > 0) //verifica se existem trabalhos pendentes
        cout << "\nNumero de trabalhos pendentes: " << Trabalhos_Pendentes << endl; //imprime a quantidade de
                                                                                    //trabalhos pendentes
    else    //se não existirem trabalhos pendentes:
        cout << "\nNenhum trabalho pendente" << endl; //informa que não existem trabalho a serem concluidos
}

//função criarTrabalho():
void Trab_ClassDef::criarTrabalho()
{
    ofstream outPutWrite("Trabalhos.dat", ios::binary); //abre arquivo para saida no estilo binário
    Trab_ClassDef t;    //cria um objeto Trab_ClassDef

    if(!outPutWrite){ //verifica se o arquivo conseguiu ser aberto com sucesso
        const char * message_failure = "erro na função criarArquivo";
        throw message_failure;  //se o arquivo falhou na abertura, dispara uma exceção
    }
    t.funcaoAmzData();   //chama a função funcaoAmzData() atraves do objeto "t"

    outPutWrite.seekp((t.num_trab -1) * sizeof(Trab_ClassDef));  //Direciona o ponteiro de leitura

    outPutWrite.write(reinterpret_cast<const char *>(&t), sizeof(Trab_ClassDef));    //escreve os dados armazenados
                                                                                //no arquivo aberto
}

//função utilitária para colher dados
void Trab_ClassDef::funcaoAmzData()
{
    const char *message_sucess = "Numero Permitido.\n"; //cria uma mensagem de sucesso
    const char *message_failure = "Numero inválido ou já preenchido.\n";    //cria uma mensagem de falha

    cout << "Num. do Trabalho: ";
    cin >> num_trab;    //colhe o número do trabalho
    if(this->verify())    //verifica se o número do trabalho está válido para uso
        throw message_failure;  //se o número estiver invalido, dispara uma exceção
    else    //se não:
        cout << message_sucess; //exibe uma mensagem de validez de número - mensagem de sucesso

    cout << "\n\nNome do Trabalho: ";   //pede o nome do trabalho
    cin.ignore();
    cin.getline(nome_do_trabalho, 75);  //lê o nome do trabalho

    cout << "Nome da Matéria: ";        //pede o nome da materia
    cin.getline(nome_da_materia, 75);   //lê o nome da materia

    cout << "Data de entrega: ";        //pede a data de entrega
    cout << "Dia: ";                    //pede o dia de entrega
    cin >> setw(2) >> dia;              //lê apenas dois dígitos e armazena-os em "dia"
    cout << setw(22) << "Mês: ";        //pede o mes de entrega
    cin >> setw(2) >>mes;               //lê apenas dois dígitos e armazena-os em "mes"
    cout << setw(22) << "Ano: ";        //pede o ano de entrega
    cin >> setw(4) >> ano;              //lê quatro dígitos e armazena-os em "ano"
    cout << "\n\nABNT? (0 para \"falso\" e \nqualquer outro valor para \"true\": "; //instrui o usuário sobre ABNT
    cin >> abnt;                        //lê um valor e armazena-os em "abnt"

    cout << "Complemento:\n";       //pede um complemento(se tiver)
    cin.ignore();                   //ignora o '\n' da linha à cima(linha 72)
    cin.getline(complemento, 200);  //lê o complemento e armazena-o em "complemento"
}

//função utilitária para verificar num_trab:
bool Trab_ClassDef::verify()
{
    ifstream Input_file("Trabalhos.dat", ios::binary); // abre arquivo para entrada no estilo binário
    Trab_ClassDef t;     //cria um objeto Trab_ClassDef

    if(!Input_file){    //verifica se o arquivo conseguiu ser aberto com sucesso
        const char * message_failure = "Arquivo impossibilitado ou inexistente\n";
        throw message_failure;  //se o arquivo falhou na abertura, dispara uma exceção
    }
    Input_file.seekg((this->num_trab - 1) * sizeof(Trab_ClassDef));  //direcionando o ponteiro de leitura

    Input_file.read(reinterpret_cast<char *>(&t), sizeof(Trab_ClassDef)); //lendo dados e transferindo-os
                                                                        //para o objeto "t"

    if(t.num_trab != 0 && t.num_trab == this->num_trab) //verifica se o numero do trabalho é valido
        return true;        //se o numero for inválido (i.e.,se o número ja existir) retorna true

    return false; //se não, retorna false
}

//função utilitária para imprimir dos dados do trabalho na tela:
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
         << "\nMatéria: " << tRef.nome_da_materia << "\n\n"
         << "Complemento: \n" << tRef.complemento << "\n"
         << setw(15) << "ABNT: " << (tRef.abnt != 0 ? "sim" : "não") << endl;

    for(i = 0; i < 80; i++)
        cout << "-";

    cout << "\n\n";
}

//função utilitária instrucoes():
inline void Trab_ClassDef::instrucoes()
{
    cout << "1 - criar trabalho\n"
         << "2 - ler trabalho\n"
         << "3 - apagar trabalho\n"
         << "4 - atualizar trabalho\n"
         << "5 - finalizar programa\n";
}

//função utilitária instrucoesUpdate():
void Trab_ClassDef::instrucoesUpdate()
{
    cout << "1 - alterar dia de entrega\n"
         << "2 - alterar mês de entrega\n"
         << "3 - alterar ano de entrega\n"
         << "4 - alterar abnt para falso ou verdadeiro\n"
         << "5 - alterar nome do trabalho\n"
         << "6 - alterar nome da matéria\n"
         << "7 - alterar complemento\n"
         << "8 - voltar ao início" << endl;
}
