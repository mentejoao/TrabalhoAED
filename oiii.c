#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_QUARTOS 21
#define CASO_LIMITE 650

/* Alunos: Leonardo Moreira de Araújo; 
           João Gabriel Cavalcante França*/
           
    int count_checkout=0;

typedef struct{
    char Nome[70];
    char CPF[15];
    int RG;
    int status; // == 0(desocupado);
    int dia_e, mes_e;
    int dia_s, mes_s; // dd/mm/aa 
    char hora_entrada[6]; // hh:mm
    char hora_saida[6]; // hh:mm
    char telefone[20]; // +55 (dd) 9xxxx-xxxx
    int bolean_status_pagamento; // == 0 (não pago);
    int qtd_adultos;
    int qtd_criancas;
    int estadia;
    int tipo_quarto;
    int qtd_colchao;
    int valor_quarto;
    int numero;
}QUARTO;

typedef struct{
    QUARTO quarto[MAX_QUARTOS][32][13];
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

void arrecada_total(HOTEL *p){
    int w, q = 0;
    for(w = 0; w < count_checkout; w++){
        q += p->valores[w];
    }
    p->arrecadacao = q;
    printf("------------------------------------------\n");
    printf("Arrecadacao Total: R$ %d,00\n", p->arrecadacao);
    printf("------------------------------------------\n");

}

void inicia_quartos(HOTEL *q){

    int i,j,k;
    q -> ult = 0;
    q -> qtd = 0;
    
    QUARTO a;
    a.status = 0;
    a.tipo_quarto= 0;
    a.qtd_colchao= 0;
    a.valor_quarto= 0;
    a.status= 0;
    a.numero= 0;

    for(i = 1; i<MAX_QUARTOS; i++){
        for(j = 1; j<32; j++){
            for(k = 1; k<13; k++){
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

    int i,q=0,flag=1, count=0;

    while(flag!=0){
        scanf("%d", &q);
        
            if(q!=0 && q<MAX_QUARTOS){
                
                for(i=dia; i<dia+qtd; i++){
                    if(y->quarto[q][i][mes].status==0){
                        count++;
                    }
                }
                if(count==qtd){
                    flag=0;
                }
            }
            else{
                printf("Quarto indisponivel nessas datas\nInsira outro quarto\n");
            }
    }
    return(q);
}

void pagamento(HOTEL *y, int dia, int mes, int quarto){

    while(1){
    fgets(y->status_pagamento, 4, stdin);
        
        if((y->status_pagamento[0] == 'S') || (y->status_pagamento[0] == 's')){
            y->quarto[quarto][dia][mes].bolean_status_pagamento = 1;
            break;
        }
        else if((y->status_pagamento[0] == 'N') || (y->status_pagamento[0] == 'n')){
            y->quarto[quarto][dia][mes].bolean_status_pagamento = 0;
            break;
        }
        printf("Insira uma resposta valida! Sim ou Nao?\n");
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

void tipo_do_quarto(HOTEL *y, int dia, int mes, int q, int tmp_estadia){
   
    int tipo_quarto_valor = 0;
    

    scanf("%d", &(y->quarto[q][dia][mes].tipo_quarto));

    if(y->quarto[q][dia][mes].tipo_quarto == 1){
        tipo_quarto_valor = 70;
    }
    if(y->quarto[q][dia][mes].tipo_quarto == 2){
        tipo_quarto_valor = 95;
    }
    if(y->quarto[q][dia][mes].tipo_quarto == 3){
        tipo_quarto_valor = 125;
    }
    if(y->quarto[q][dia][mes].tipo_quarto == 4){
        tipo_quarto_valor = 145;
    }

    printf("Insira a quantidade de colchoes extras:\n");
    scanf("%d", &(y->quarto[q][dia][mes].qtd_colchao));

    y->quarto[q][dia][mes].valor_quarto = (tipo_quarto_valor*tmp_estadia)+(30*y->quarto[q][dia][mes].qtd_colchao);
}

void Checkout(HOTEL *y){
    
    char checkout_value[4];
    char hospede_procurado_checkout[70];
    int l, w, k, p, q, count=0, count2=0;

    printf("--------------------CHECK-OUT-----------------------\n");
    printf("Insira o nome do hospede:\n");
    fgets(hospede_procurado_checkout, 70, stdin);
        for(l = 1; l < MAX_QUARTOS; l++){
            for(w = 1; w < 32; w++){
                for(k = 1; k < 13; k++){
                    if(strcmp(hospede_procurado_checkout, y->quarto[l][w][k].Nome) == 0){
                        
                        if(count2==0){
                            printf("---------------DADOS-GERAIS------------------------\n");
                            printf("Nome: %s", y->quarto[l][w][k].Nome);
                            printf("CPF: %s\n", y->quarto[l][w][k].CPF);
                            printf("RG: %d\n", y->quarto[l][w][k].RG);
                            printf("Quarto: %d\n", y->quarto[l][w][k].numero);
                            printf("Telefone: %s\n", y->quarto[l][w][k].telefone);
                            printf("------------------DADOS-DA-ESTADIA----------------\n");
                            printf("Tipo do quarto: ");
                            if(y->quarto[l][w][k].tipo_quarto == 1){
                                printf("Quarto com uma cama de solteiro\n");
                            }
                            if(y->quarto[l][w][k].tipo_quarto == 2){
                                printf("Quarto com duas camas de solteiro\n");
                            }
                            if(y->quarto[l][w][k].tipo_quarto == 3){
                                printf("Quarto com uma cama de casal\n");
                            }   
                            if(y->quarto[l][w][k].tipo_quarto == 4){
                                printf("Quarto com uma cama de casal e uma de solteiro\n");
                            }
                            printf("Quantidadade de colchoes (extras): %d\n", y->quarto[l][w][k].qtd_colchao);
                            printf("Diarias: %d\n", y->quarto[l][w][k].estadia);
                            printf("------------------VALOR----------------\n");
                            if( y->quarto[l][w][k].bolean_status_pagamento == 0){
                                printf("O pagamento ainda não foi realizado.\n");
                            }
                            else{
                                printf("O pagamento já foi realizado.\n");
                            }
                            printf("Valor total: R$ %d,00\n", y->quarto[l][w][k].valor_quarto);
                            printf("--------------------------------------\n");
                            printf("Confirmar checkout?\n");
                            fgets(checkout_value, 4, stdin);
    
                            if((checkout_value[0] == 'S') || (checkout_value[0] == 's')){
                                y->valores[count_checkout] = y->quarto[l][w][k].valor_quarto;
                                
                                for(p = 1; p <13; p++){
                                    
                                    for(q = 1 ; q < 32; q++){
                                        
                                        memset(y->quarto[l][q][p].Nome, '0', 70);
                                        memset(y->quarto[l][q][p].CPF, '0', 15);
                                        y->quarto[l][q][p].RG = 0;
                                        y->quarto[l][q][p].dia_e=0;
                                        y->quarto[l][q][p].dia_s=0;
                                        memset(y->quarto[l][q][p].hora_entrada, '0', 6);
                                        memset(y->quarto[l][q][p].hora_saida, '0', 6);
                                        memset(y->quarto[l][q][p].telefone, '0', 20);
                                         y->quarto[l][q][p].valor_quarto = 0;
                                         y->quarto[l][q][p].bolean_status_pagamento = 0;
                                         y->quarto[l][q][p].qtd_adultos = 0;
                                         y->quarto[l][q][p].qtd_criancas = 0;
                                         y->quarto[l][q][p].estadia = 0;
                                         y->quarto[l][q][p].tipo_quarto = 0;
                                         y->quarto[l][q][p].qtd_colchao = 0;
                                         y->quarto[l][q][p].numero = 0;
                                         y->quarto[l][q][p].status = 0;
                                         count_checkout++;
                                    }
                                }
                            }
                            printf("Checkout realizado com sucesso. Até a próxima!\n");
                            count++;
                            count2++;
                        }
                        
                        else{
                            for(p = 1; p <13; p++){
                                    
                                    for(q = 1 ; q < 32; q++){
                                        
                                        memset(y->quarto[l][q][p].Nome, '0', 70);
                                        memset(y->quarto[l][q][p].CPF, '0', 15);
                                        y->quarto[l][q][p].RG = 0;
                                        y->quarto[l][q][p].dia_e=0;
                                        y->quarto[l][q][p].dia_s=0;
                                        memset(y->quarto[l][q][p].hora_entrada, '0', 6);
                                        memset(y->quarto[l][q][p].hora_saida, '0', 6);
                                        memset(y->quarto[l][q][p].telefone, '0', 20);
                                         y->quarto[l][q][p].valor_quarto = 0;
                                         y->quarto[l][q][p].bolean_status_pagamento = 0;
                                         y->quarto[l][q][p].qtd_adultos = 0;
                                         y->quarto[l][q][p].qtd_criancas = 0;
                                         y->quarto[l][q][p].estadia = 0;
                                         y->quarto[l][q][p].tipo_quarto = 0;
                                         y->quarto[l][q][p].qtd_colchao = 0;
                                         y->quarto[l][q][p].numero = 0;
                                         y->quarto[l][q][p].status = 0;
                                    }
                                }
                        }
                    }
                }
            }
        }
            
    if(count == 0){
            printf("---------------------------------------------------\n");
            printf("Nome do hospede invalido.\nTente novamente.\n");
            printf("---------------------------------------------------\n");
    }
}

void Check_in(HOTEL *i){

    int j, q, RG, qtd_adultos, qtd_criancas, dia, mes, tmp_estadia;
    char nome_provisorio[70], CPF[15], telefone[20], hora_entrada[6];

        printf("--------------------CHECK-IN-----------------------\n");
        printf("Insira o nome do hospede:\n");
        fgets(nome_provisorio, 70, stdin);
        printf("Insira o CPF do hospede (ex: XXX.XXX.XXX-XX):\n");
        fgets(CPF, 15, stdin);
        getchar();
        printf("Insira o RG do hospede:\n");
        scanf("%d", &RG);
        getchar();
        printf("Insira o telefone do hospede (ex: +XX (XX) 9XXXX-XXXX):\n");
        fgets(telefone, 20, stdin);
        printf("Insira a quantidade de adultos:\n");
        scanf("%d", &qtd_adultos);
        getchar();
        printf("Insira a quantidade de criancas:\n");
        scanf("%d", &qtd_criancas);
        getchar();
        printf("Insira o dia e o mes de entrada (ex: DD MM):\n");
        scanf("%d %d",&dia, &mes);
        getchar();
        printf("Insira a hora de entrada (ex: XX:XX):\n");
        fgets(hora_entrada, 6, stdin);
        getchar();
        printf("Insira o tempo de estadia (diarias):\n");
        scanf("%d", &tmp_estadia);
        printf("Insira o numero do quarto:\n");
        q = quarto(&(*i), dia, mes, tmp_estadia);
        Tabela_quarto2();
        printf("Insira o tipo do quarto:\n");
        tipo_do_quarto(&(*i), dia, mes, q, tmp_estadia);
        printf("Pagamento realizado na entrada?\n");
        getchar();
        pagamento(&(*i), dia, mes, q);
        printf("--------------------------------------------------\n");
        for(j=dia; j<dia+tmp_estadia; j++){
            strcpy(i->quarto[q][j][mes].Nome, nome_provisorio);
            strcpy(i->quarto[q][j][mes].CPF, CPF);
            strcpy(i->quarto[q][j][mes].telefone, telefone);
            strcpy(i->quarto[q][j][mes].hora_entrada, hora_entrada);
            i->quarto[q][j][mes].qtd_adultos = qtd_adultos;
            i->quarto[q][j][mes].qtd_criancas = qtd_criancas;
            i->quarto[q][j][mes].RG = RG;
            i->quarto[q][j][mes].dia_e = dia;
            i->quarto[q][j][mes].mes_e = mes;
            i->quarto[q][j][mes].estadia = tmp_estadia;
            i->quarto[q][j][mes].numero = q;
            i->quarto[q][j][mes].status = 1;
            i->quarto[q][j][mes].dia_s = (i->quarto[q][j][mes].dia_e + i->quarto[q][j][mes].estadia)%31;
            i->quarto[q][j][mes].mes_s = (i->quarto[q][j][mes].dia_e + i->quarto[q][j][mes].estadia)/31 + i->quarto[q][j][mes].mes_e;
        }
}

void Busca_hospede(HOTEL *h){

    char hospede_procurado[70];
    int i, count=0;

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    printf("Digite o nome do hospede: ");
    fgets(hospede_procurado, 70, stdin);
    
        for(i=0; i<MAX_QUARTOS; i++){

            if(strcmp(hospede_procurado, h->quarto[i][tm.tm_mday][tm.tm_mon + 1].Nome) == 0){
                printf("-------------------------------------------\n");
                printf("Hospede encontrado com sucesso!\n");
                printf("-------------------------------------------\n");
                printf("Nome: %s", h->quarto[i][tm.tm_mday][tm.tm_mon + 1].Nome);
                printf("CPF: %s\n", h->quarto[i][tm.tm_mday][tm.tm_mon + 1].CPF);
                printf("RG: %d\n", h->quarto[i][tm.tm_mday][tm.tm_mon + 1].RG);
                printf("Quarto: %d\n", h->quarto[i][tm.tm_mday][tm.tm_mon + 1].numero);
                printf("Telefone: %s\n", h->quarto[i][tm.tm_mday][tm.tm_mon + 1].telefone);
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

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    printf("--------------------QUARTOS---------------------\n");
    for(int i= 1; i<MAX_QUARTOS; i++){
        if(x->quarto[i][tm.tm_mday][tm.tm_mon + 1].status==1){
            printf("Quarto %d: ocupado\n", i);
        }
        else{
            printf("Quarto %d: desocupado\n", i);
        }

    }
    printf("------------------------------------------------\n");
}

int main(){

    HOTEL hot;
    int comando;

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
                Checkout(&hot);
                break;
            case 3:
                Busca_hospede(&hot);
                break;
            case 4:
                Verificacao_quartos(&hot);
                break;
            case 5:
                Tabela_quarto();
                break; 
            case 6:
                arrecada_total(&hot);
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