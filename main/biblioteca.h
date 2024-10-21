#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

struct instrucao {
    char dado_char[9];
    char inst_char[17];
    int opcode;
    int rs;
    int rt;
    int rd;
    int funct;
    int imm;
    int addr;
    int dado;
};


struct estado_salvo {
    int copia_PC;
    int copia_banco_de_registradores[8];
    struct instrucao copia_memoria[256];
};

void Carregar_Memoria_Instrucoes(struct instrucao *inst_name);

void Escrever_Registrador(int *banco_de_registradores, int indice, int valor);

void Executar_Instrucao(int *PC, struct instrucao *inst_name, int *banco_de_registradores);

int Ler_Registrador(int *banco_de_registradores, int indice);

int Calculos_ULA(int *PC, struct instrucao *inst_name, int *banco_de_registradores);

void Imprimir_Memorias_Instrucoes(struct instrucao *inst_name);

void ImprimirMemorias_d(struct instrucao *inst_name);

void Imprimir_BancoRG(int *banco_de_registradores);

void Escrever_Memoria_Dados(int endereco, int valor, struct instrucao *inst_name);

int Ler_Memoria_Dados(int endereco, struct instrucao *inst_name);

void Salva_Dado(struct instrucao *inst_name, int *tamanho);

void Salva_Asm(struct instrucao *inst_name);

void Visualizar_Instrucao_Atual(int *PC, struct instrucao *inst_name);

void Retorna_Estado(struct estado_salvo *estado, int *PC, struct instrucao *inst_name,  int *banco_de_registradores);

void Salva_Estado(int *PC, struct instrucao *inst_name, struct estado_salvo *estado, int *banco_de_registradores);

#endif // BIBLIOTECA_H_INCLUDED