#include <stdio.h>
#include <string.h>
#define MAX_QUARTOS 20

/* Alunos: Leonardo Moreira de Araújo; 
           João Gabriel Cavalcante França*/

typedef struct{
    char Nome[70];
    char CPF[14];
    int RG;
    int quarto; // == 0(desocupado);
    char data_entrada[11]; // dd/mm/aa 
    char data_saida[11]; // dd/mm/aa 
    char hora_entrada[6]; // hh:mm
    char hora_saida[6]; // hh:mm
    char telefone[20]; // +55 (dd) 9xxxx-xxxx
    float valor;
    int bolean_status_pagamento; // == 0 (nõo pago);
    int quantidade_adultos;
    int quantidade_criancas;
} HOSPEDE;

typedef struct{
    HOSPEDE quantidade[MAX_QUARTOS];
    int quartos[MAX_QUARTOS];
    char status_pagamento[4];
} HOTEL;

/* TAD - HOTEL
1. Check-in do hóspede;
2. Checkout do hóspede;
3. Buscar hóspede;
4. Verificar os quartos disponíveis;
5. Tabela de valores dos quartos;
6. Calcular arrecadação diária;
7. Calcular arrecadação mensal;
8. Calcular arrecadação anual;
9. Emitir nota fiscal;
*/

void inicia_quartos(HOTEL *q){
    for(int i = 0; i < MAX_QUARTOS/2; i++){
        q->quartos[i]=0;
    }
    for(int i = MAX_QUARTOS/2; i < MAX_QUARTOS; i++){
        q->quartos[i]=1;
    }
}

void quarto(HOSPEDE *x, HOTEL *y){
    while(1){
        scanf("%d", &x->quarto);
        getchar();
        if(y->quartos[(x->quarto)-1]==0){
            y->quartos[(x->quarto)-1]=1;
            break;
        }
        else{
            printf("Quarto ocupado\n");
            printf("Insira o quarto novamente:\n");
        }
    }
}

void pagamento(HOSPEDE *x, HOTEL *y){
    while(1){
    fgets(y->status_pagamento, 4, stdin);
        
        if((y->status_pagamento[0] == 'S') || (y->status_pagamento[0] == 's')){
            x->bolean_status_pagamento = 1;
            break;
        }
        else if((y->status_pagamento[0] == 'N') || (y->status_pagamento[0] == 'n')){
            x->bolean_status_pagamento = 0;
            break;
        }
        printf("Insira uma resposta válida! Sim ou Não?\n");
    }
}


int verifica_cpf(HOSPEDE *h){
    printf("%s", h->CPF);
    if(
        ((h->CPF[0]*1 + h->CPF[1]*2 + h->CPF[2]*3 + h->CPF[4]*4 + h->CPF[5]*5 + h->CPF[6]*6 + h->CPF[8]*7 + h->CPF[9]*8 + h->CPF[10]*9)%11 == h->CPF[12]) &&
        ((h->CPF[0]*9 + h->CPF[1]*8 + h->CPF[2]*7 + h->CPF[4]*6 + h->CPF[5]*5 + h->CPF[6]*4 + h->CPF[8]*3 + h->CPF[9]*2 + h->CPF[10]*1)%11 == h->CPF[13])
        && h->CPF[3] == '.' && h->CPF[7] == '.' && h->CPF[11] == '-'){
            return 1;
        }
    else{
        return -1;
    }
}

void Check_in(HOSPEDE *h, HOTEL *i){
    
    printf("--------------------CHECK-IN-----------------------\n");
    printf("Insira o nome do hospede:\n");
    fgets(h->Nome, 70, stdin);

    /* printf("Insira o CPF do hospede (ex: XXX.XXX.XXX-XX):\n");
    while(1){
    fgets(h->CPF, 14, stdin);
    getchar();
        if(verifica_cpf(&h) == -1) {
            printf("Insira um CPF válido!\n");
        }
        else {
            break;
        }
    } */ 
        
    printf("Insira o RG do hospede:\n");
    scanf("%d", &h->RG);
    getchar();
    printf("Insira o telefone do hospede (ex: +XX (XX) 9XXXX-XXXX):\n");
    fgets(h->telefone, 20, stdin);
    printf("Insira a quantidade de adultos:\n");
    scanf("%d", &h->quantidade_adultos);
    getchar();
    printf("Insira a quantidade de criancas:\n");
    scanf("%d", &h->quantidade_criancas);
    getchar();
    printf("Insira a data de entrada (ex: XX/XX/XXXX):\n");
    fgets(h->data_entrada, 11, stdin);
    getchar();
    printf("Insira a hora de entrada (ex: XX:XX):\n");
    fgets(h->hora_entrada, 6, stdin);
    getchar();
    printf("Insira o numero do quarto:\n");
    quarto(h, i);
    printf("Pagamento realizado na entrada? \n");
    pagamento(h, i);
}

void Menu(){

    printf("----------------------------------------------\n");
    printf("MENU DE FUNCIONALIDADES DO HOTEL\n");
    printf("1. Check-in do hospede\n");
    printf("2. Checkout do hospede\n");
    printf("3. Buscar hospede\n");
    printf("4. Verificar os quartos disponiveis\n");
    printf("5. Tabela de valores dos quartos\n");
    printf("6. Calcular arrecadacao diaria\n");
    printf("7. Calcular arrecadacao mensal\n");
    printf("8. Calcular arrecadacao anual\n");
    printf("9. Fim\n");
    printf("----------------------------------------------\n");
    printf("Digite a opcao escolhida:\n");

}

void Tabela_quarto(){

    printf("----------------------------------------------\n");
    printf("VALORES DOS QUARTOS\n");
    printf("Quarto com uma cama de solteiro = 70,00\n");
    printf("Quarto com duas camas de solteiro = 95,00\n");
    printf("Quarto com uma cama de casal = 125,00\n");
    printf("Quarto com uma cama de casal e uma de solteiro = 145,00\n");
    printf("Colchao avulso = 30,00\n");
    printf("----------------------------------------------\n");

}

void Verificacao_quartos(HOTEL *x){
    // == 1(ocupado)
    // == 0(desocupado)
    printf("--------------------QUARTOS---------------------\n");
    for(int i= 0; i<MAX_QUARTOS; i++){
        if(x->quartos[i]==1){
            printf("Quarto %d: ocupado\n", i+1);
        }
        else{
            printf("Quarto %d: desocupado\n", i+1);
        }
    }
    printf("------------------------------------------------\n");
}

int main(){

    HOSPEDE hosp;
    HOTEL hot;
    int comando;

    inicia_quartos(&hot);
    do{
        Menu();
        scanf("%d", &comando);
        getchar();
        switch(comando){
            case 1:
                Check_in(&hosp, &hot);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                Verificacao_quartos(&hot);
                break;
            case 5:
                Tabela_quarto();
                break; 
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                printf("Obrigado por utilizar nosso sistema! Tchau tchau!\n");
                break;
            default:
                printf("Opca escolhida invalida!\nEscolha novamente - Obrigado!\n");
                break;
        }

    }while(comando!=9);


return 0;
}