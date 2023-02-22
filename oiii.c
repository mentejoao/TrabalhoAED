#include <stdio.h>
#include <string.h>
#define MAX_QUARTOS 20

/* Alunos: Leonardo Moreira de Araújo; 
           João Gabriel Cavalcante França*/

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
    int valor;
    int bolean_status_pagamento; // == 0 (não pago);
    int quantidade_adultos;
    int quantidade_criancas;
    int estadia;
    int tipo_quarto;
    int n_colchoes;
} HOSPEDE;

typedef struct{
    int quartos[MAX_QUARTOS];
    char status_pagamento[4];
} HOTEL;

/* TAD - HOTEL
1. Check-in do hóspede;
2. Checkout do hóspede;
3. Buscar hóspede;
4. Verificar os quartos disponíveis;
5. Tabela de valores dos quartos;
6. Calcular arrecadação mensal;
7. Calcular arrecadação anual;
8. Recibo;
*/

void inicia_quartos(HOTEL *q){

    for(int i = 0; i<MAX_QUARTOS; i++){
        q->quartos[i]=0;
    }

}

void quarto(HOSPEDE *h, HOTEL *y, int indice){
    while(1){
        scanf("%d", &h[indice].quarto);
        getchar();
        if((y->quartos[(h[indice].quarto)-1]==0) && (h[indice].quarto>0 && h[indice].quarto<MAX_QUARTOS)){
            y->quartos[(h[indice].quarto)-1]=1;
            break;
        }
        else{
            printf("Quarto indisponivel\n");
            printf("Insira o quarto novamente:\n");
        }
    }
}

void pagamento(HOSPEDE *h, HOTEL *y, int indice){

    while(1){
    fgets(y->status_pagamento, 4, stdin);
        
        if((y->status_pagamento[0] == 'S') || (y->status_pagamento[0] == 's')){
            h[indice].bolean_status_pagamento = 1;
            break;
        }
        else if((y->status_pagamento[0] == 'N') || (y->status_pagamento[0] == 'n')){
            h[indice].bolean_status_pagamento = 0;
            break;
        }
        printf("Insira uma resposta válida! Sim ou Não?\n");
    }
}

void Tabela_quarto2(){

    printf("\n");
    printf("TIPOS DE QUARTOS\n");
    printf("1 - Quarto com uma cama de solteiro = 70,00\n");
    printf("2 - Quarto com duas camas de solteiro = 95,00\n");
    printf("3 - Quarto com uma cama de casal = 125,00\n");
    printf("4 - Quarto com uma cama de casal e uma de solteiro = 145,00\n");
    printf("5 - Colchao avulso = 30,00\n");
    printf("\n");

}

void tipo_do_quarto(HOSPEDE *h, int indice){

   
    int tipo_quarto_valor = 0;

    scanf("%d", &h[indice].tipo_quarto);

    if(h[indice].tipo_quarto == 1){
        tipo_quarto_valor = 70;
    }
    if(h[indice].tipo_quarto == 2){
        tipo_quarto_valor = 95;
    }
    if(h[indice].tipo_quarto == 3){
        tipo_quarto_valor = 125;
    }
    if(h[indice].tipo_quarto == 4){
        tipo_quarto_valor = 145;
    }

    printf("Insira a quantidade de colchoes extras:\n");
    scanf("%d", &h[indice].n_colchoes);

    h[indice].valor = (tipo_quarto_valor*h[indice].estadia)+(30*h[indice].n_colchoes);
    
}

void Checkout(HOSPEDE *h){
    printf("--------------------CHECK-OUT-----------------------\n");
    printf("Insira o nome do hospede:\n");
    
    char hospede_procurado_checkout[70];
    int l, count=0;

    fgets(hospede_procurado_checkout, 70, stdin);
        for(l=0; l<MAX_QUARTOS; l++){
            if(strcmp(hospede_procurado_checkout, h[l].Nome) == 0){
                printf("---------------------------------------------------\n");
                printf("Hospede encontrado com sucesso!\n");
                printf("---------------DADOS-GERAIS------------------------\n");
                printf("Nome: %s", h[l].Nome);
                printf("CPF: %s\n", h[l].CPF);
                printf("RG: %d\n", h[l].RG);
                printf("Quarto: %d\n", h[l].quarto);
                printf("Telefone: %s\n", h[l].telefone);
                printf("------------------DADOS-DA-ESTADIA----------------\n");
                printf("Quantidadade de colchoes (extras): %.0lf\n", h[l].n_colchoes);
                printf("Diarias: %.0lf\n", h[l].estadia);
                printf("Tipo do quarto: ");
                if(h[l].tipo_quarto == 1){
                    printf("Quarto com uma cama de solteiro\n");
                }
                if(h[l].tipo_quarto == 2){
                    printf("Quarto com duas camas de solteiro\n");
                }
                if(h[l].tipo_quarto == 3){
                    printf("Quarto com uma cama de casal\n");
                }   
                else{
                    printf("Quarto com uma cama de casal e uma de solteiro\n");
                }
                count++;
            }
        }
    if(count == 0){
        printf("Nome do hospede invalido.\nTente novamente.\n");
    }
    
}

int Check_in(HOSPEDE *h, HOTEL *i, int indice){

    if(indice == MAX_QUARTOS+1){
        printf("Nao ha quartos disponíveis\n");
    }
    
    else{

        printf("--------------------CHECK-IN-----------------------\n");
        printf("Insira o nome do hospede:\n");
        fgets(h[indice].Nome, 70, stdin);
        printf("Insira o CPF do hospede (ex: XXX.XXX.XXX-XX):\n");
        fgets(h[indice].CPF, 15, stdin);
        getchar();
        printf("Insira o RG do hospede:\n");
        scanf("%d", &h[indice].RG);
        getchar();
        printf("Insira o telefone do hospede (ex: +XX (XX) 9XXXX-XXXX):\n");
        fgets(h[indice].telefone, 20, stdin);
        printf("Insira a quantidade de adultos:\n");
        scanf("%d", &h[indice].quantidade_adultos);
        getchar();
        printf("Insira a quantidade de criancas:\n");
        scanf("%d", &h[indice].quantidade_criancas);
        getchar();
        printf("Insira a data de entrada (ex: XX/XX/XXXX):\n");
        fgets(h[indice].data_entrada, 11, stdin);
        getchar();
        printf("Insira a hora de entrada (ex: XX:XX):\n");
        fgets(h[indice].hora_entrada, 6, stdin);
        getchar();
        printf("Insira o tempo de estadia (diarias):\n");
        scanf("%lf", &h[indice].estadia);
        Tabela_quarto2();
        printf("Insira o tipo do quarto:\n");
        tipo_do_quarto(h, indice);
        printf("Insira o numero do quarto:\n");
        quarto(h, i, indice);
        printf("Pagamento realizado na entrada? \n");
        pagamento(h, i, indice);
        indice++;
        
    }

    return(indice);
}

void Busca_hospede(HOSPEDE *h){

    char hospede_procurado[70];
    int i, count=0;

    printf("Digite o nome do hospede: ");
    fgets(hospede_procurado, 70, stdin);
    
        for(i=0; i<MAX_QUARTOS; i++){

            if(strcmp(hospede_procurado, h[i].Nome) == 0){

                printf("-------------------------------------------\n");
                printf("Nome: %s", h[i].Nome);
                printf("CPF: %s\n", h[i].CPF);
                printf("RG: %d\n", h[i].RG);
                printf("Quarto: %d\n", h[i].quarto);
                printf("Telefone: %s\n", h[i].telefone);
                printf("-------------------------------------------");
                count++;

            }

        }

    if(count == 0){
        printf("Nome do hospede invalido.\nTente novamente.\n");
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
    printf("6. Calcular arrecadacao mensal\n");
    printf("7. Calcular arrecadacao anual\n");
    printf("8. Fim\n");
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

    HOSPEDE hospede[MAX_QUARTOS];
    HOTEL hot;
    int comando, indice=0;

    inicia_quartos(&hot);
    do{
        Menu();
        scanf("%d", &comando);
        getchar();
        switch(comando){
            case 1:
                indice = Check_in(hospede, &hot, indice);
                break;
            case 2:
                Checkout(hospede);
                break;
            case 3:
                Busca_hospede(hospede);
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
                printf("Obrigado por utilizar nosso sistema! Tchau tchau!\n");
                break;
            default:
                printf("Opca escolhida invalida!\nEscolha novamente - Obrigado!\n");
                break;
        }

    }while(comando!=8);


return 0;
}