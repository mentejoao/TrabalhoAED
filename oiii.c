#include <stdio.h>
#include <string.h>
#define MAX_QUARTOS 21
#define CASO_LIMITE 600
#define MAX_CLIENTE 1000

/* Alunos: Leonardo Moreira de Araújo; 
           João Gabriel Cavalcante França*/

typedef struct{
    char Nome[70];
    char CPF[15];
    int RG;
    int quarto; // == 0(desocupado);
    int dia_e, mes_e;
    int dia_s, mes_s; // dd/mm/aa 
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
    int tipo_quarto;
    int qtd_cama;
    int qtd_colchao;
    float valor_quarto;
    char CPF[15];
    int status;
    int numero;
}QUARTO;

typedef struct{
    QUARTO quarto[MAX_QUARTOS][32][13];
    HOSPEDE cliente[MAX_CLIENTE];
    int qtd;
    int ult;
    char status_pagamento[4];
    int arrecadacao;
    int valores[CASO_LIMITE];
} HOTEL;

void criar_arq (HOTEL A) {   // sem a struct...
   FILE *fp;  
 
   fp = fopen ("Hotel.dat", "wb"); //arquivo para escrita binária
   if (fp == NULL) {  
      printf ("Erro ao abrir o arquivo.\n");  
      return;  
   }  
   else {  
           printf ("Arquivo Binario criado com sucesso.\n");  
          fwrite(&A, sizeof(HOTEL), 1, fp); 
          }         
     fclose (fp);  
       
}/*Função reponsavel por exibir o conteudo do arquivo Binario.dat*/

/* TAD - HOTEL
1. Check-in do hóspede;
2. Checkout do hóspede;
3. Buscar hóspede;
4. Verificar os quartos disponíveis;
5. Tabela de valores dos quartos;
6. Calcular arrecadação total;
*/

void arrecada_total(HOTEL *p, int indice2){
    int q = 0;
    for(int w = 0; w < indice2; w++){
        q += p->valores[w];
    }
    p->arrecadacao = q;
    printf("Arrecadacao Total: R$ %d,00\n", p->arrecadacao);
}

void inicia_quartos(HOTEL *q){

    q -> ult = 0;
    q -> qtd = 0;
    QUARTO a;
    a.status = 0;
    a.tipo_quarto= 3;
    a.qtd_cama= 2;
    a.qtd_colchao= 1;
    a.valor_quarto= 70;
    a.status= 0;
    a.numero= 0;

    for(int i = 1; i<MAX_QUARTOS; i++){
        for(int j = 1; i<32; j++){
            for(int k = 1; k<13; k++){
                q->quarto[i][j][k] = a;
            }
        }
    }
    
    for(int i = 1; i<CASO_LIMITE; i++){
        q->valores[i]=0;
    }

    q->arrecadacao = 0;
}

void Carregar_Hotel(HOTEL *A){
     FILE *fp;
    
     fp = fopen ("Hotel.dat", "rb"); 
      if (fp == NULL) {  
        inicia_quartos(&(*A));
		return;
}  else {
          fread(&(*A),sizeof(HOTEL),1,fp);
          fclose(fp);
         }  
}

int quarto(HOTEL *y, int dia, int mes, int qtd){

    int i,q,flag;

    while(flag!=0 && q==0){
        scanf("%d", &q);
        flag=0;
        for(i=dia; i<dia+qtd; i++){
            if(y->quarto[q][i][mes].status!=0){
                flag=1;
            }
        }
        return (q);
    }
}

void pagamento(HOSPEDE *h, HOTEL *y){

    while(1){
    fgets(y->status_pagamento, 4, stdin);
        
        if((y->status_pagamento[0] == 'S') || (y->status_pagamento[0] == 's')){
            h->bolean_status_pagamento = 1;
            break;
        }
        else if((y->status_pagamento[0] == 'N') || (y->status_pagamento[0] == 'n')){
            h->bolean_status_pagamento = 0;
            break;
        }
        printf("Insira uma resposta válida! Sim ou Não?\n");
    }
}

void Tabela_quarto2(){

    printf("\n");
    printf("--------TIPOS-DE-QUARTOS--------\n");
    printf("1 - Quarto com uma cama de solteiro = 70,00\n");
    printf("2 - Quarto com duas camas de solteiro = 95,00\n");
    printf("3 - Quarto com uma cama de casal = 125,00\n");
    printf("4 - Quarto com uma cama de casal e uma de solteiro = 145,00\n");
    printf("5 - Colchao avulso = 30,00\n");
    printf("\n");

}

void tipo_do_quarto(HOSPEDE *h){
   
    int tipo_quarto_valor = 0;

    scanf("%d", h->tipo_quarto);

    if(h->tipo_quarto == 1){
        tipo_quarto_valor = 70;
    }
    if(h->tipo_quarto == 2){
        tipo_quarto_valor = 95;
    }
    if(h->tipo_quarto == 3){
        tipo_quarto_valor = 125;
    }
    if(h->tipo_quarto == 4){
        tipo_quarto_valor = 145;
    }

    printf("Insira a quantidade de colchoes extras:\n");
    scanf("%d", &h->n_colchoes);

    h->valor = (tipo_quarto_valor*h->estadia)+(30*h->n_colchoes);
    
}

int Checkout(HOSPEDE *h, HOTEL *y){
    printf("--------------------CHECK-OUT-----------------------\n");
    printf("Insira o nome do hospede:\n");
    
    char checkout_value;
    char hospede_procurado_checkout[70];
    int l, count=0;

    fgets(hospede_procurado_checkout, 70, stdin);
        for(l=0; l<MAX_QUARTOS; l++){
            if(strcmp(hospede_procurado_checkout, h[l].Nome) == 0){
                printf("---------------DADOS-GERAIS------------------------\n");
                printf("Nome: %s", h[l].Nome);
                printf("CPF: %s\n", h[l].CPF);
                printf("RG: %d\n", h[l].RG);
                printf("Quarto: %d\n", h[l].quarto);
                printf("Telefone: %s\n", h[l].telefone);
                printf("------------------DADOS-DA-ESTADIA----------------\n");
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
                if(h[l].tipo_quarto == 4){
                    printf("Quarto com uma cama de casal e uma de solteiro\n");
                }
                printf("Quantidadade de colchoes (extras): %d\n", h[l].n_colchoes);
                printf("Diarias: %.d\n", h[l].estadia);
                count++;
                printf("------------------VALOR----------------\n");
                printf("Valor total: R$ %d,00\n", h[l].valor);
                 printf("--------------------------------------\n");
                printf("Confirmar checkout?\n");
                scanf("%c", &checkout_value);

                    if(checkout_value == 'S' || checkout_value == 's'){
                        y->valores[indice] = h[l].valor;
                        memset(h[l].Nome, '0', 70);
                        memset(h[l].CPF, '0', 15);
                        h[l].RG = 0;
                        y->quartos[(h[l].quarto)-1] = 0;
                        memset(h[l].data_entrada, '0', 11);
                        memset(h[l].data_saida, '0', 11);
                        memset(h[l].hora_entrada, '0', 6);
                        memset(h[l].hora_saida, '0', 6);
                        memset(h[l].telefone, '0', 20);
                         h[l].valor = 0;
                         h[l].bolean_status_pagamento = 0;
                         h[l].quantidade_adultos = 0;
                         h[l].quantidade_criancas = 0;
                         h[l].estadia = 0;
                         h[l].tipo_quarto = 0;
                         h[l].n_colchoes = 0;
                         h[l].quarto = 0;
                         indice++;
                    }

                    else{
                        break;
                    }
            }
        }

    if(count == 0){
            printf("---------------------------------------------------\n");
            printf("Nome do hospede invalido.\nTente novamente.\n");
            printf("---------------------------------------------------\n");
    }
    
    return(indice);
}

int Check_in( HOTEL *i){

    HOSPEDE h;
    int j, q;  

        printf("--------------------CHECK-IN-----------------------\n");
        printf("Insira o nome do hospede:\n");
        fgets(h.Nome, 70, stdin);
        printf("Insira o CPF do hospede (ex: XXX.XXX.XXX-XX):\n");
        fgets(h.CPF, 15, stdin);
        getchar();
        printf("Insira o RG do hospede:\n");
        scanf("%d", &h.RG);
        getchar();
        printf("Insira o telefone do hospede (ex: +XX (XX) 9XXXX-XXXX):\n");
        fgets(h.telefone, 20, stdin);
        printf("Insira a quantidade de adultos:\n");
        scanf("%d", &h.quantidade_adultos);
        getchar();
        printf("Insira a quantidade de criancas:\n");
        scanf("%d", &h.quantidade_criancas);
        getchar();
        printf("Insira o dia e o mes de entrada (ex: XX/XX/XXXX):\n");
        scanf("%d %d",&h.dia_e, &h.mes_e);
        getchar();
        printf("Insira a hora de entrada (ex: XX:XX):\n");
        fgets(h.hora_entrada, 6, stdin);
        getchar();
        printf("Insira o tempo de estadia (diarias):\n");
        scanf("%d", &h.estadia);
        Tabela_quarto2();
        printf("Insira o tipo do quarto:\n");
        tipo_do_quarto(&h);
        printf("Insira o numero do quarto:\n");
        q = quarto(&(*i), h.dia_e, h.mes_e, h.estadia);
            if(q==0){
                printf("Nao existe quarto disponivel nessas datas\n");
            }
            else{

                printf("Pagamento realizado na entrada? \n");
                pagamento(&h, &(*i));
                printf("--------------------------------------------------\n");
                for(j=h.dia_e; j<h.dia_e+h.estadia; j++){
                    strcpy(i->quarto[q][j][h.mes_e].CPF, h.CPF);
                    i->quarto[q][j][h.mes_e].status = 1;
                    i->quarto[q][j][h.mes_e].valor_quarto = h.valor;
                }
                i->cliente[i->ult]=h;
                i->ult++;

            }

}

void Busca_hospede(HOSPEDE *h){

    char hospede_procurado[70];
    int i, count=0;

    printf("Digite o nome do hospede: ");
    fgets(hospede_procurado, 70, stdin);
    
        for(i=0; i<MAX_QUARTOS; i++){

            if(strcmp(hospede_procurado, h[i].Nome) == 0){
                printf("-------------------------------------------\n");
                printf("Hospede encontrado com sucesso!\n");
                printf("-------------------------------------------\n");
                printf("Nome: %s", h[i].Nome);
                printf("CPF: %s\n", h[i].CPF);
                printf("RG: %d\n", h[i].RG);
                printf("Quarto: %d\n", h[i].quarto);
                printf("Telefone: %s\n", h[i].telefone);
                printf("-------------------------------------------\n");
                count++;

            }

        }

    if(count == 0){
        printf("---------------------------------------------------\n");
        printf("Nome do hospede invalido.\nTente novamente.\n");
        printf("---------------------------------------------------\n");
    }
    
}

void Menu(){

    printf("----------------------MENU-DE-FUNCIONALIDADES-DO-HOTEL------------------------\n");
    printf("1. Check-in do hospede\n");
    printf("2. Checkout do hospede\n");
    printf("3. Buscar hospede\n");
    printf("4. Verificar os quartos disponiveis\n");
    printf("5. Tabela de valores dos quartos\n");
    printf("6. Calcular arrecadacao total\n");
    printf("7. Fim\n");
    printf("------------------------------------------------------------------------------\n");
    printf("Digite a opcao escolhida:\n");

}

void Tabela_quarto(){

    printf("-----------------------VALORES-DOS-QUARTOS-----------------------\n");
    printf("Quarto com uma cama de solteiro = 70,00\n");
    printf("Quarto com duas camas de solteiro = 95,00\n");
    printf("Quarto com uma cama de casal = 125,00\n");
    printf("Quarto com uma cama de casal e uma de solteiro = 145,00\n");
    printf("Colchao avulso = 30,00\n");
    printf("-----------------------------------------------------------------\n");

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

    HOSPEDE h;
    HOTEL hot;
    int comando, indice=0, indice2=0;

    Carregar_Hotel(&hot);
    do{
        Menu();
        scanf("%d", &comando);
        getchar();
        switch(comando){
            case 1:
                Check_in(&hot);
                break;
            case 2:
                Checkout(&h, &hot);
                break;
            case 3:
                Busca_hospede(&h);
                break;
            case 4:
                Verificacao_quartos(&hot);
                break;
            case 5:
                Tabela_quarto();
                break; 
            case 6:
                arrecada_total(&hot, indice2);
                break;
            case 7:
                criar_arq(hot);
                printf("Obrigado por utilizar nosso sistema! Tchau tchau!\n");
                break;
            default:
                printf("Opca escolhida invalida!\nEscolha novamente - Obrigado!\n");
                break;
        }

    }while(comando!=7);


return 0;
}