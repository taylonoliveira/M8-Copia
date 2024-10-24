#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    //Declara��o de structs
    struct instrucao *inst_name = malloc(256 * sizeof(struct instrucao)); //alocando dinamicamente a mem�ria para receber 256 espa�os de mem do tipo instrucao
    struct estado_salvo estado;
    struct instrucao RI;

    //Declara��o de vari�veis
    int num_opcao = 0;                        //Controla o menu
    int PC = 0;                                 //Vari�vel que controla o valor do PC durante a execu��o do programa
    int estado_c = 0; 
    int reg_A = 0;
    int reg_B = 0;
    int reg_ULA = 0;
    int memoria_instrucoes_carregada = 0;     //Indica se as mem�rias de instru��es foi carregada
    int banco_de_registradores[8] = {0};      //Inicializa o banco de rg
    int tamanho = 0;                          //vari�vel utilizada em algumas fun��es da mem�ria de dados
    banco_de_registradores[1] = 2;
    banco_de_registradores[2] = 2;
    banco_de_registradores[4] = 5;
    //Inicio do menu
    while(num_opcao != 10){
    printf("\n");
    printf("\n");
    printf("\t\tMenu Principal \n\n");
    printf("\t(1)  Carregar memoria de Instrucoes e Dados.\n"); //.mem
    printf("\t(2)  Imprimir memorias (instrucoes e dados).\n"); //(instucoes e dados)
    printf("\t(3)  Imprimir banco de registradores.\n");
    printf("\t(4)  Imprimir todo o simulador (registradores e memorias).\n"); //(registradores e memorias)
    printf("\t(5)  Salvar .asm\n");
    printf("\t(6)  Salvar .dat\n");
    printf("\t(7)  Executar Programa.\n"); //run
    printf("\t(8)  Executar uma instrucao.\n"); //step
    printf("\t(9)  Voltar uma instrucao.\n"); //back
    printf("\t(10) Encerrar o programa.\n\n");

            printf("\n");
            printf("\tINFORME QUAL OPCAO DESEJA: ");
            scanf("%d", &num_opcao);
            printf("\n");

            switch (num_opcao){

            case 1 :
                Carregar_Memoria_Instrucoes_Dados(inst_name);
                memoria_instrucoes_carregada = 1;                                       // Atualiza para 1 indicando que a mem�ria foi carregada
                break;

            case 2 :
                if (memoria_instrucoes_carregada == 1) {
                    printf("********Memoria de Instrucoes e Dados********\n\n");
                    Imprimir_Memorias_Instrucoes(inst_name);
                }
                else {
                    printf("\tMemorias de instrucoes nao carregada.\n\n");
                }
                printf("********Memoria de Dados********\n\n");
                ImprimirMemorias_d(inst_name);
                break;

            case 3 :
                Imprimir_BancoRG(banco_de_registradores);
                break;

            case 4 :
                Visualizar_Instrucao_Atual(&PC, inst_name);
                printf("\tPC = %d\n", PC);
                Imprimir_BancoRG(banco_de_registradores);
                if (memoria_instrucoes_carregada == 1) {
                printf("********Memoria de Instrucoes********\n\n");
                Imprimir_Memorias_Instrucoes(inst_name);
                }
                else{
                    printf("\tMemoria de instrucoes nao carregada.\n\n");
                }
                printf("********Memoria de Dados********\n\n");
                ImprimirMemorias_d(inst_name);
                break;

            case 5 :
                if (memoria_instrucoes_carregada == 1) {
                    Salva_Asm(inst_name);
                    }
                    else{
                    printf("\tMemorias de instrucoes nao foi carregada.\n");
                    }
                break;

            case 6 :
                    Salva_Dado(inst_name, &tamanho);
                break;

            case 7 :
                if (memoria_instrucoes_carregada == 1) {
                    while (PC < 256 && inst_name[PC].opcode != -1) {                                    // Programa roda at� n�o haver mais instru��es
                        if (inst_name[PC].opcode == 2 || inst_name[PC].opcode == 8) {                   // se for do tipo J ou BEQ, ele realiza a mudan�a no PC diretamente pelas fun��es
                            Salva_Estado(&PC, inst_name, &estado, banco_de_registradores);
                            Executar_Instrucao(&PC, inst_name, banco_de_registradores);
                            printf("********Proxima Instrucao********\n\n");
                            printf("\tPC = %d\n\n", PC);
                        } else {
                            Salva_Estado(&PC, inst_name, &estado, banco_de_registradores);
                            Executar_Instrucao(&PC, inst_name, banco_de_registradores);
                            printf("********Proxima Instrucao********\n\n");
                            printf("\tPC = %d\n\n", PC);
                        }
                    }
                } else {
                    printf("\tMemorias de instrucoes nao foi carregada.\n");
                }
                break;

            case 8 :
                if (memoria_instrucoes_carregada == 1) {
                    if (inst_name[PC].opcode == 2 || inst_name[PC].opcode == 8) {                        // se for do tipo J ou BEQ, ele realiza a mudan�a do PC diretamente pelas fun��es
                        Salva_Estado(&PC, inst_name, &estado, banco_de_registradores);
                        Executar_Instrucao(&PC, inst_name, banco_de_registradores);
                        printf("********Proxima Instrucao********\n\n");
                        printf("\tPC = %d\n", PC);
                    } else {
                        Ciclo(&reg_ULA, &reg_A, &reg_B, &estado_c, &PC, &RI, inst_name, banco_de_registradores);
                        imprime_estado(&reg_ULA, &reg_A, &reg_B, &estado_c, &RI, banco_de_registradores);
                        Executar_Instrucao_M(&reg_A, &reg_B, &estado_c, &PC, &RI);
                        estado_M(&estado_c, &RI);
                        printf("\tPC = %d\n", PC);
                    }
                } else {
                    printf("\tMemorias de instrucoes nao foi carregada.\n");
                }
                break;

            case 9 :
                if(PC == 0){
                    printf("\tNao e possivel retornar uma instrucao\n\n");
                }
                else{
                    Retorna_Estado(&estado, &PC, inst_name, banco_de_registradores);
                    printf("\tPC = %d\n", PC);
                }

                break;

            case 10:
                printf("\tPrograma encerrado!\n");
                break;

            default:
                printf("\tOpcao invalida.\n");
                break;
            }
    }

    //libera a mem�ria alocada dinamicamente pelo malloc
    free(inst_name);
    return 0;
}
