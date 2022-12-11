#include <stdio.h>
#include <string.h>
#define MAX_QUARTOS 20

/* Alunos: Leonardo Moreira de Araújo; 
           João Gabriel Cavalcante França*/

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

typedef struct{

    char Nome[70];
    char CPF[15];
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

void inicia_quartos(HOTEL *q){

    for(int i = 0; i < MAX_QUARTOS; i++){
        q->quartos[i]=0;
    }

}

void Check_in(HOSPEDE *h, HOTEL *i){
    
    printf("Insira o nome do hospede:\n");
    fgets(h->Nome, 70, stdin);
    printf("Insira o CPF do hospede (ex: XXX.XXX.XX-XX):\n");
    fgets(h->CPF, 15, stdin);
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

    while(1){
        scanf("%d", &h->quarto);
        if(i->quartos[(h->quarto)-1]==0){
            i->quartos[(h->quarto)-1]=1;
            break;
        }
        else{
            printf("Quarto ocupado\n");
            printf("Insira o quarto novamente:\n");
        }
    }
    
    printf("Pagamento realizado na entrada? \n");
    fgets(i->status_pagamento, 4, stdin);
    while(1){
        
        if((i->status_pagamento[0] == 'S') || (i->status_pamento[0] == 's')){
            h->bolean_status_pagamento = 1;
        }
        else if((i->status_pagamento[0] == 'N') || (i->status_pamento[0] == 'n')){
            h->bolean_status_pagamento = 0;
        }  
    }
    
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

int main(){

    HOSPEDE hosp;
    HOTEL hot;

    inicia_quartos(&hot);
    Menu();
    Check_in(&hosp, &hot);


return 0;
}