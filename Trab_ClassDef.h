#ifndef TRAB_CLASSDEF_H
#define TRAB_CLASSDEF_H

class Trab_ClassDef
{
    public:
        //Fun��es controladoras
        Trab_ClassDef(int = 0, int = 0, int = 0, int = 0, int = 0,
                      char * = '\0', char * = '\0', char * = '\0');    //construtor default

        void criarTrabalho();    //inicializa um Trabalho
        void lerArquivo();       //l� o arquivo por completo
        void apagarTrabalho();  //apaga o trabalho desejado atrav�s do num_trab
        void atualizarTrabalho(); //atualiza algum dado espec�fico de um trabalho desejado
                                  //atrav�s do num_trab
        inline void instrucoes();

    private:
        //Fun��es utilit�rias:
        void printTrabalho(Trab_ClassDef &);
        void funcaoAmzData();
        bool verify();
        void instrucoesUpdate();

        //Atributos de um trabalho:
        int num_trab;
        int dia, mes, ano, abnt;
        char nome_do_trabalho[75];
        char nome_da_materia[75];
        char complemento[200];
};

#endif // TRAB_CLASSDEF_H
