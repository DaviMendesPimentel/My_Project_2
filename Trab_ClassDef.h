#ifndef TRAB_CLASSDEF_H
#define TRAB_CLASSDEF_H

class Trab_ClassDef
{
    public:
        //Funções controladoras
        Trab_ClassDef(int = 0, int = 0, int = 0, int = 0, int = 0,
                      char * = '\0', char * = '\0', char * = '\0');    //construtor default

        void criarTrabalho();    //inicializa um Trabalho
        void lerArquivo();       //lê o arquivo por completo
        void apagarTrabalho();  //apaga o trabalho desejado através do num_trab
        void atualizarTrabalho(); //atualiza algum dado específico de um trabalho desejado
                                  //através do num_trab
        inline void instrucoes();

    private:
        //Funções utilitárias:
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
