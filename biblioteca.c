#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void Carregar_Memoria_Instrucoes_Dados(struct instrucao *inst_name) { //carrega mem�ria de instru��es

setlocale(LC_ALL, "Portuguese");

    char nomefile[100];
    printf("\tDigite o nome do arquivo .mem: ");
    printf("\n\t");
    scanf("%s", nomefile);
    printf("\n");

// Abre o arquivo para leitura
    FILE *file = fopen(nomefile, "r");
    if (file == NULL) {
        printf("\tErro ao abrir o arquivo.\n");
    }
    else{
        printf("\tMemoria de instrucoes carregada!\n");
    }

    // Inicializa todos os 256 opcodes como -1, serve para sinalizar que o espa�o est� vazio, sem instru��es
    for (int i = 0; i < 256; i++) {
        inst_name[i].opcode = -1;
    }

    int posicao = 0;
    int tamanho = 0;
    // L� cada linha do arquivo
    while (fgets(inst_name[posicao].inst_char, sizeof(inst_name[posicao].inst_char), file)) {
        // Remove o caractere de nova linha, se presente
        inst_name[posicao].inst_char[strcspn(inst_name[posicao].inst_char, "\n")] = '\0';

        size_t tamanho_linha = strlen(inst_name[posicao].inst_char);

        if (tamanho_linha == 16) {
        // Separa o opcode (4 primeiros bits)
        char opcode[5] = {0}; // 4 bits + 1 para o caractere nulo
        strncpy(opcode, inst_name[posicao].inst_char, 4); // Copia os 4 primeiros bits para o opcode

        // Converte o opcode para n�mero inteiro
        unsigned int opcode_num = (unsigned int)strtol(opcode, NULL, 2);

        // Verifica o tipo de instru��o para armazenar os dados nas vari�veis corretas
        if (opcode_num == 4) {
            // Instru��o tipo I (ADDI)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};   // 3 bits + 1 para nulo
            char rt[4] = {0};   // 3 bits + 1 para nulo
            char imm[7] = {0};  // 6 bits + 1 para nulo

            // Copia os bits correspondentes para os campos
            strncpy(opcode, inst_name[posicao].inst_char, 4);   // Bits 1 a 4 (opcode)
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);   // Bits 5 a 7 (rs)
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);   // Bits 8 a 10 (rt)
            strncpy(imm, inst_name[posicao].inst_char + 10, 6); // Bits 11 a 16 (imm)

        //Verificar se o valor do imm � positivo ou negativo, se for negativo, desfazer a opera��o de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 � negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            inst_name[posicao].imm = inst_name[posicao].imm +1; //add +1 no valor convertido
            inst_name[posicao].imm = inst_name[posicao].imm*(-1); //inverte o sinal
        }

        else{
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);


        } else if (opcode_num == 11) {
            // Instru��o tipo I (LW)
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2);

        } else if (opcode_num == 15) {
            // Instru��o tipo I (SW)
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2);

        } else if (opcode_num == 8) {
            // Instru��o tipo I (BEQ)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(imm, inst_name[posicao].inst_char + 10, 6);

        //Verificar se o valor do imm � positivo ou negativo, se for negativo, desfazer a opera��o de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 � negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            inst_name[posicao].imm = inst_name[posicao].imm +1; //add +1 no valor convertido
            inst_name[posicao].imm = inst_name[posicao].imm*(-1); //inverte o sinal
        }

        else{
            inst_name[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);

        } else if (opcode_num == 2) {
            // Instru��o tipo J
            char opcode[5] = {0};
            char addr[8] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(addr, inst_name[posicao].inst_char + 9, 7);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].addr = (int)strtol(addr, NULL, 2);

        } else if (opcode_num == 0) {
            // Instru��o tipo R
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char rd[4] = {0};
            char funct[4] = {0};

            strncpy(opcode, inst_name[posicao].inst_char, 4);
            strncpy(rs, inst_name[posicao].inst_char + 4, 3);
            strncpy(rt, inst_name[posicao].inst_char + 7, 3);
            strncpy(rd, inst_name[posicao].inst_char + 10, 3);
            strncpy(funct, inst_name[posicao].inst_char + 13, 3);

            inst_name[posicao].opcode = (int)strtol(opcode, NULL, 2);
            inst_name[posicao].rs = (int)strtol(rs, NULL, 2);
            inst_name[posicao].rt = (int)strtol(rt, NULL, 2);
            inst_name[posicao].rd = (int)strtol(rd, NULL, 2);
            inst_name[posicao].funct = (int)strtol(funct, NULL, 2);

        } else {
            printf("Tipo de instrucao nao identificada.\n");
        }

        posicao++;

        if (posicao >= 256) {
            printf("\tLimite maximo de instrucoes atingido.\n");
            break;
            }
        } else if (tamanho_linha == 8) {
        // Separa os bits do dado (8 primeiros bits)
        char dado[9] = {0}; // 8 bits + 1 para o caractere nulo

        strcpy(dado, inst_name[posicao].inst_char); // Copia os 8 bits para o dado

        //Verificar se o valor do imm � positivo ou negativo, se for negativo, desfazer a opera��o de complemento de 2.
        if (dado[0] == '1'){ // Se for 1 � negativo, invertemos os bits.
            dado[0] = '0';
            for(int i=1; i<=7; i++){
                if(dado[i] == '1'){
                    dado[i] = '0';
                }else{
                    dado[i] = '1';
                }
            }
            inst_name[tamanho].dado = (int)strtol(dado, NULL, 2); //converte p/ inteiro
            inst_name[tamanho].dado = inst_name[tamanho].dado +1; //add +1 no valor convertido
            inst_name[tamanho].dado = inst_name[tamanho].dado*(-1); //inverte o sinal
        }
        else{
            inst_name[tamanho].dado = (int)strtol(dado, NULL, 2); //converte p/ inteiro
        }
            tamanho++;
        }
    }

    fclose(file);
}

void Imprimir_Memorias_Instrucoes(struct instrucao *inst_name) { //Imprime as mem�ria de instru��es

    for(int i=0; i<256; i++) {

        if (inst_name[i].opcode == -1) {
        }
        else if (inst_name[i].opcode == 0) {
            printf("Tipo R - opcode: %d, rs: %d, rt: %d, rd: %d, funct: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].rd, inst_name[i].funct);
        }
        else if(inst_name[i].opcode == 2) {
            printf("Tipo J - opcode: %d, addr: %d\n", inst_name[i].opcode, inst_name[i].addr);
        }
        else if(inst_name[i].opcode == 8) {
            printf("Tipo BEQ - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 15) {
            printf("Tipo SW - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 11) {
                printf("Tipo LW - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else if(inst_name[i].opcode == 4) {
                printf("Tipo ADDI - opcode: %d, rs: %d, rt: %d, imm: %d\n", inst_name[i].opcode, inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
        }
        else{
            printf("Tipo de instrucao invalida!\n");
        }
    }
    printf("\n");
}


void ImprimirMemorias_d(struct instrucao *inst_name){  //Imprime aa mem�ria de dados.

    for (int x = 0; x < 16; x++) {
        for(int y = 0; y < 16; y++) {
            int mem = x * 16 + y;
            if (mem < 256) {
                printf("Mem[%d] %d\t", mem, inst_name[mem].dado);
                }
            }
            printf("\n");
        }
}

//**Modelagem do banco de registradores**//

void Escrever_Registrador(int *banco_de_registradores, int indice, int valor) {     //salva valores nos registradores

    if(indice >= 0 && indice < 8) {
        banco_de_registradores[indice] = valor;
    }
    else {
        printf("\tindice de registrador nao encontrado!\n");
    }

}

int Ler_Registrador(int *banco_de_registradores, int indice) {          //l� valores armazenados nos registradores

    if(indice >= 0 && indice < 8) {
        return banco_de_registradores[indice];
    }
    else{
        printf("\tindice de registrador nao encontrado!\n");
    }
}

void Imprimir_BancoRG(int *banco_de_registradores) {                   //imprime os valores armazenados no banco de registradores
    printf("********Banco de Registradores********\n");
    printf("\n");
    for(int x=0; x<8; x++) {
        printf("\tRG[%d] = %d\n", x, banco_de_registradores[x]);
    }
    printf("\n");
}

//**Modelagem do banco de registradores**//

int Calculos_ULA(int *PC, struct instrucao *inst_name, int *banco_de_registradores) { //Executa os c�lculos

    int resultado = 0;

    if(inst_name[*PC].opcode == 0) { //Tipo R

        switch(inst_name[*PC].funct) {                                                                                                        // faz a verifica��o do campo funct para informar qual opera��o realizar
    case 0:     //soma
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + Ler_Registrador(banco_de_registradores, inst_name[*PC].rt); //faz a soma dos valores armazenados em rs e rt
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado nao foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);                                                          //guarda o resultado no registrador indicado por rd
        }
        break;

    case 2:     //sub
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) - Ler_Registrador(banco_de_registradores, inst_name[*PC].rt);
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado n�o foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);
        }
        break;

    case 4:     //and
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) & Ler_Registrador(banco_de_registradores, inst_name[*PC].rt);
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado nao foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);
        }
        break;

    case 5:     //or
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) | Ler_Registrador(banco_de_registradores, inst_name[*PC].rt);
            if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado nao foi armazenado!\n");
        }else{
            Escrever_Registrador(banco_de_registradores, inst_name[*PC].rd, resultado);
        }
         break;
        }
        (*PC)++;
    }
    else if(inst_name[*PC].opcode == 4) { //Tipo I Addi
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + inst_name[*PC].imm;  //faz a soma com o valor imm que pode ser negativo
        if(resultado >127 || resultado <-128){
            printf("\tOverflow. O resultado nao foi armazenado\n");
        }
        else{
        Escrever_Registrador(banco_de_registradores, inst_name[*PC].rt, resultado); //se n�o tiver overflow, guarda o resultado no registrador indicado por rt
        }
        (*PC)++;
    }
    else if(inst_name[*PC].opcode == 8) {   //Tipo I Beq
        if(Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) == Ler_Registrador(banco_de_registradores, inst_name[*PC].rt)){ //verifica se os valores armazenados nos registradores s�o iguais
            printf("\tInstrucao nao gerou valor de resultado.\n\n");
            *PC += inst_name[*PC].imm;      //se forem iguais, PC eh atualizado com um novo valor
        }
        else{
            printf("\tInstrucao nao gerou valor de resultado.\n\n");
            (*PC)++;                        // se n�o forem iguais, incrementa para a pr�xima instru��o
        }
    }
    else if(inst_name[*PC].opcode == 11){ //Tipo I LW
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + inst_name[*PC].imm;                // endere�o = rs + imm
        if(resultado < 0 || resultado > 255){
            printf("\tEndereco de memoria invalido!\n");
        }else{
        Escrever_Registrador(banco_de_registradores, inst_name[*PC].rt, Ler_Memoria_Dados(resultado, inst_name));      // armazena no registrador
        }
        (*PC)++;
    }
    else if(inst_name[*PC].opcode == 15){//Tipo I SW
        resultado = Ler_Registrador(banco_de_registradores, inst_name[*PC].rs) + inst_name[*PC].imm;                // endere�o = rs + imm. L� da mem�ria e armazena no registrador
        if(resultado < 0 || resultado > 255){
            printf("\tEndereco de memoria invalido!\n");
        }else{
        Escrever_Memoria_Dados(resultado, Ler_Registrador(banco_de_registradores, inst_name[*PC].rt), inst_name);      // Armazena na mem�ria de dados
        }
        (*PC)++;
    }
    return resultado;
}

void Executar_Instrucao(int *PC, struct instrucao *inst_name, int *banco_de_registradores) {   //Executa as instru��es

    Visualizar_Instrucao_Atual(PC, inst_name);

    if(inst_name[*PC].opcode == 2) {
         printf("\tInstrucao nao gerou valor de resultado.\n\n");
        *PC = inst_name[*PC].addr;                                                     //realiza as do tipo J, alterando diretamente o PC
    }
    else if(inst_name[*PC].opcode == -1) {                                            // se o opcode estiver como -1, indica que n�o h� mais instru��es v�lidas
            printf("\tPC esta apontando para um campo vazio!\n\n");
    }
    else if(inst_name[*PC].opcode != 8){
        int resultado = Calculos_ULA(PC, inst_name, banco_de_registradores);                    // chama a fun��o da ula que verifica o opcode e executa a opera��o
            printf("\tResultado da ULA: %d\n\n", resultado);
        }else{
            Calculos_ULA(PC, inst_name, banco_de_registradores);
        }
    Imprimir_BancoRG(banco_de_registradores);
}

int Ler_Memoria_Dados(int endereco, struct instrucao *inst_name){
    if (endereco < 0 || endereco >= 256) {
        printf("\tEndereco invalido.\n");
    }
    return inst_name[endereco].dado; // Retorna o dado no endere�o
}

void Escrever_Memoria_Dados(int endereco, int valor, struct instrucao *inst_name){
    if (endereco < 0 || endereco >= 256) {
        printf("\tEndereco invalido.\n");
    }
    inst_name[endereco].dado = valor; // Armazena o valor no endere�o
}

void Salva_Dado(struct instrucao *inst_name, int *tamanho){
        printf("\n\n");

        char nomearq[100];

        printf("\tDigite o nome do arquivo .dat: ");
        scanf("%s", nomearq);
        printf("\n");

        FILE *arq = fopen(nomearq, "w");
        if (arq == NULL) {
        printf("\tErro ao abrir o arquivo");
        }

        for(int x = 0; x<*tamanho; x++){
            fprintf(arq,"%d\n", inst_name[x].dado);
        }
        fclose(arq);
}

 void Salva_Asm(struct instrucao *inst_name){
        char nomearq[100];

        printf("\tDigite o nome do arquivo .asm: ");
        scanf("%s", nomearq);
        printf("\n");

        FILE *arq2 = fopen(nomearq, "w");
        if (arq2 == NULL) {
        printf("\tErro ao abrir o arquivo");
        }

        for(int i=0; i < 256; i++){
            if(inst_name[i].opcode == 0){
                if(inst_name[i].funct == 0){
                    fprintf(arq2,"ADD $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 2){
                    fprintf(arq2,"SUB $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 4){
                    fprintf(arq2,"AND $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 5){
                    fprintf(arq2,"OR $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
            }
            else if(inst_name[i].opcode == 4){
                    fprintf(arq2,"ADDI $t%d, $t%d, %d\n", inst_name[i].rt, inst_name[i].rs, inst_name[i].imm);
            }else if(inst_name[i].opcode == 11){
                    fprintf(arq2,"LW $t%d, %d($t%d)\n", inst_name[i].rt,inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 15){
                    fprintf(arq2,"SW $t%d, %d($t%d)\n", inst_name[i].rt, inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 8){
                    fprintf(arq2,"BEQ $t%d, $t%d, %d\n", inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
            }else if(inst_name[i].opcode == 2){
                    fprintf(arq2,"J %d\n", inst_name[i].addr);
            }
            if(inst_name[i].opcode == 0){
                if(inst_name[i].funct == 0){
                    printf("ADD $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 2){
                    printf("SUB $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 4){
                    printf("AND $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
                else if(inst_name[i].funct == 5){
                    printf("OR $t%d, $t%d, $t%d\n", inst_name[i].rd, inst_name[i].rs, inst_name[i].rt);
                }
            }
            else if(inst_name[i].opcode == 4){
                    printf("ADDI $t%d, $t%d, %d\n", inst_name[i].rt, inst_name[i].rs, inst_name[i].imm);
            }else if(inst_name[i].opcode == 11){
                    printf("LW $t%d, %d($t%d)\n", inst_name[i].rt,inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 15){
                    printf("SW $t%d, %d($t%d)\n", inst_name[i].rt, inst_name[i].imm, inst_name[i].rs);
            }else if(inst_name[i].opcode == 8){
                    printf("BEQ $t%d, $t%d, %d\n", inst_name[i].rs, inst_name[i].rt, inst_name[i].imm);
            }else if(inst_name[i].opcode == 2){
                    printf("J %d\n", inst_name[i].addr);
            }
        }

        fclose(arq2);
 }

void Visualizar_Instrucao_Atual(int *PC, struct instrucao *inst_name){

        printf("****************--INSTRUCAO ATUAL--****************\n\n");
            if(inst_name[*PC].opcode == 0){
                if(inst_name[*PC].funct == 0){
                    printf("\tADD $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
                else if(inst_name[*PC].funct == 2){
                    printf("\tSUB $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
                else if(inst_name[*PC].funct == 4){
                    printf("\tAND $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
                else if(inst_name[*PC].funct == 5){
                    printf("\tOR $t%d, $t%d, $t%d\n", inst_name[*PC].rd, inst_name[*PC].rs, inst_name[*PC].rt);
                }
            }
            else if(inst_name[*PC].opcode == 4){
                    printf("\tADDI $t%d, $t%d, %d\n", inst_name[*PC].rt, inst_name[*PC].rs, inst_name[*PC].imm);
            }else if(inst_name[*PC].opcode == 11){
                    printf("\tLW $t%d, %d($t%d)\n", inst_name[*PC].rt,inst_name[*PC].imm, inst_name[*PC].rs);
            }else if(inst_name[*PC].opcode == 15){
                    printf("\tSW $t%d, %d($t%d)\n", inst_name[*PC].rt, inst_name[*PC].imm, inst_name[*PC].rs);
            }else if(inst_name[*PC].opcode == 8){
                    printf("\tBEQ $t%d, $t%d, %d\n", inst_name[*PC].rs, inst_name[*PC].rt, inst_name[*PC].imm);
            }else if(inst_name[*PC].opcode == 2){
                    printf("\tJ %d\n", inst_name[*PC].addr);
            }
        printf("\n");
 }

void Salva_Estado(int *PC, struct instrucao *inst_name, struct estado_salvo *estado, int *banco_de_registradores) {
    // Salvar o PC
    estado->copia_PC = *PC;

    // Salvar o estado dos registradores
    for (int i = 0; i < 8; i++) {
        estado->copia_banco_de_registradores[i] = banco_de_registradores[i];
    }

    // Salvar o estado da mem�ria
    for (int i = 0; i < 256; i++) {
        estado->copia_memoria[i] = inst_name[i];
    }
}

void Retorna_Estado(struct estado_salvo *estado, int *PC, struct instrucao *inst_name, int *banco_de_registradores) {
    // Restaurar o PC
    *PC = estado->copia_PC;

    // Restaurar os registradores
    for (int i = 0; i < 8; i++) {
        banco_de_registradores[i] = estado->copia_banco_de_registradores[i];
    }

    // Restaurar a mem�ria
    for (int i = 0; i < 256; i++) {
        inst_name[i] = estado->copia_memoria[i];
    }
}












//INSTRUCOES MULTICICLO



void Executar_Instrucao_M(int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI) {   //Executa as instru��es
    if(RI->opcode == 2) {
         printf("\tInstrucao nao gerou valor de resultado.\n\n");
        *PC = RI->addr;                                                     //realiza as do tipo J, alterando diretamente o PC
    }
    else if(RI->opcode == -1) {                                            // se o opcode estiver como -1, indica que n�o h� mais instru��es v�lidas
            printf("\tPC esta apontando para um campo vazio!\n\n");
    }
    else if(RI->opcode != 8){
        int resultado = Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI);                    // chama a fun��o da ula que verifica o opcode e executa a opera��o
            printf("\tResultado da ULA: %d\n\n", resultado);
        }else{
            Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI);
        }
}

void Ciclo(int *reg_ULA, int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI, struct instrucao *inst_name,  int *banco_de_registradores){
    if(*estado_c == 0){
        if(inst_name[*PC].opcode != -1){
        *RI = inst_name[*PC];
}
    }
    if(*estado_c == 1){
        *reg_A = Ler_Registrador(banco_de_registradores, RI->rs);
        *reg_B = Ler_Registrador(banco_de_registradores, RI->rt);
        *reg_ULA = Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI);
    }
    if(*estado_c == 7){
        *reg_ULA = Calculos_ULA_M(reg_A, reg_B, estado_c, PC, RI);
    }
    if(*estado_c == 8){
        Escrever_Registrador(banco_de_registradores, RI->rd, *reg_ULA);
    }
}

void estado_M(int *estado_c, struct instrucao *RI){
    if(*estado_c == 8){
            (*estado_c) = 0;
    }
    else if(*estado_c == 7){
            (*estado_c) = 8;
    }
    else if(*estado_c == 1){
        if(RI->opcode == 0){
            (*estado_c) = 7;
        }
    }
    else if(*estado_c == 0){
            (*estado_c) = 1; 
    }
}

void imprime_estado(int *reg_ULA, int *reg_A, int *reg_B, int *estado_c, struct instrucao *RI, int *banco_de_registradores){
        if(*estado_c == 0){
            if (RI->opcode == -1) {}
            else if (RI->opcode == 0) {
                printf("\tTipo R - opcode: %d, rs: %d, rt: %d, rd: %d, funct: %d\n", RI->opcode, RI->rs, RI->rt, RI->rd, RI->funct);
            }
            else if(RI->opcode == 2) {
                printf("\tTipo J - opcode: %d, addr: %d\n", RI->opcode, RI->addr);
            }
            else if(RI->opcode == 8) {
                printf("\tTipo BEQ - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else if(RI->opcode == 15) {
                printf("\tTipo SW - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else if(RI->opcode == 11) {
                    printf("\tTipo LW - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else if(RI->opcode == 4) {
                    printf("\tTipo ADDI - opcode: %d, rs: %d, rt: %d, imm: %d\n", RI->opcode, RI->rs, RI->rt, RI->imm);
            }
            else{
                printf("Tipo de instrucao invalida!\n");
            }
            printf("\tEstado atual [%d]\n", *estado_c);
        }else if(*estado_c == 1){
            printf("\tRegistrador A [%d]\n", *reg_A);
            printf("\tRegistrador B [%d]\n", *reg_B);
            printf("\tEstado atual [%d]\n", *estado_c);
        }else if(*estado_c == 7){
            printf("\tSaida da ULA [%d]\n", *reg_ULA);
            printf("\tEstado atual [%d]\n", *estado_c);
        }else if(*estado_c == 8){
            Imprimir_BancoRG(banco_de_registradores);
            printf("\tEstado atual [%d]\n", *estado_c);
        }

}

int Calculos_ULA_M(int *reg_A, int *reg_B, int *estado_c, int *PC, struct instrucao *RI) { //Executa os c�lculos

    int resultado = 0;

    if(*estado_c == 7){
        if(RI->opcode == 0) { //Tipo R
            switch(RI->funct) {                                                                                                        // faz a verifica��o do campo funct para informar qual opera��o realizar
        case 0:     //soma
            resultado = *reg_A + *reg_B; //faz a soma dos valores armazenados em rs e rt
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }
            break;

        case 2:     //sub
            resultado = *reg_A - *reg_B;
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado n�o foi armazenado!\n");
            }

        case 4:     //and
            resultado = *reg_A & *reg_B;
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }

        case 5:     //or
            resultado = *reg_A | *reg_B;
                if(resultado >127 || resultado <-128){
                printf("\tOverflow. O resultado nao foi armazenado!\n");
            }
            break;
                }
            }
     }
    if(*estado_c == 0){
        (*PC)++;
        resultado = *PC;
    }
    return resultado;
}


