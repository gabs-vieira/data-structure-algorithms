/*
TAD aeroportoEDAero {Fila FATE, FDEC; Lista LDISP, relatório de operações;

Operações:
cadastra_aviao(E: idAviao, ...): insere um avião em LDISP, ordenado pela sua identificação (ok)

avioes_cadastrados( ): informa na tela quais aviões estão cadastrados(lista LDISP), cada um com sua quantidade de decolagens e de aterrissagens. 

autoriza_decolar(E: idAviao): enfileira avião em FDEC; ()

decolar(...): desenfileira avião de FDEC, atualizando seu número de decolagens;

autoriza_aterrissar(E: idAviao): enfileira avião em FATE;

aterrissar(...): desenfileira avião de FATE, atualizando seu número de aterrissagens;

proximas_decolagens( ): informa na tela as próximas decolagens previstas (fila FDEC);

proximas_aterrissagens( ): informa na tela as próximas aterrissagens previstas (fila FATE);

relatorio_aeroporto( ): apresenta na tela um relatório com a descrição das aterrissagens e decolagens efetuadas até o momento da solicitação;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct nodo{
    char id[6];
    int dec;
    int att;
    struct nodo *prox; //endereço do próximo nodo no qual contém a informação'
}NODO;

typedef struct index{
    char ind;
    NODO *ini;
    struct index *prox;
}INDEX;

typedef struct smpnodo{
    char num[6];
    struct smpnodo *prox;
}SMPNODO;

typedef struct report{
    char num[6];
    char tag[12];
    struct report *prox;
}REPORT;


typedef struct header{
    int deco;
    int atte;
}HEADER;

int cadastra_aviao(INDEX **ini, char id[6]){ //cadastra e coloca em ordem crescente os aviões
    INDEX *sup = *ini;
    while (sup != NULL && sup->ind != id[0]){
        sup = sup->prox;
    }
    NODO *new, *aux = sup->ini, *ant = NULL; //new não precisa atribuir o ini. 
    new = (NODO*)malloc(sizeof(NODO));
    strcpy(new->id, id);
    new->dec = 0;
    new->att = 0;
    new->prox = NULL; //lembrar de nullar

    if(sup->ini == NULL || strcmp(aux->id, new->id) > 0){ //lista vazia e inserção no começo
        new->prox = sup->ini;
        sup->ini = new;
        return 0;
    } 

    while (aux != NULL && strcmp(aux->id, new->id) <= 0){ //percorre os nodos e compara  strcmp retorna um inteiro se for menor q zero t1 é menor que t2
        ant = aux;
        aux = aux -> prox;
    }
    if(strcmp(ant->id, new->id) == 0){
        free (new);
        printf("Avião %s já cadastrado!!!", id);
        return 1;
    }
    else{
        ant->prox = new; //serve para os dois casos meio e fim, pois aux se for no final ele é null
        new -> prox = aux;  
    }
    
}

void conv_id(char id[6]){ //converte o valor para maiusculo
    int i;
    for(i = 0; i < 5; i++){
        id[i] = toupper(id[i]);
    }
}

void esc_list(INDEX *ini){ //escreve a lista de aviões
    INDEX *aux = ini;
    NODO *aux2;

    while(aux != NULL){
        printf("%c : ", aux->ind);
        aux2 = aux->ini;
        while(aux2 != NULL){
            printf("\n\nAeronave: %s \n",aux2->id);
            printf("Número de aterissagens: %d\n", aux2->att);
            printf("Número de decolagens: %d\n", aux2->dec);
            aux2 = aux2->prox;
        }
        printf("\n");
        aux = aux->prox;
    }
}

int enfileira(SMPNODO **control, INDEX *ini, char cod[6]){ //em testes
    INDEX *sup = ini;
    while (sup != NULL && sup->ind != cod[0]){
        sup = sup->prox;
    }
    if (sup == NULL){
        printf("Avião não cadastrado tente novamente depois de cadastrar.");
        return 0;
    }

    SMPNODO *new, *aux = *control;
    NODO *check = sup->ini, *ant = NULL;

    new = (SMPNODO*)malloc(sizeof(SMPNODO));

    strcpy(new->num, cod);
    new->prox = NULL;
    
    if (aux == NULL){
        *control = new;
        return 1;
    }

    while (check != NULL && strcmp(check->id, cod) < 0){
        ant = check;
        check = check->prox;
    }

    if(check != NULL && strcmp(check->id, cod) == 0){
        printf("\nAvião já está na fila.\n");
        free(new);
        return 0;
    }

    if(ant == NULL){
        new->prox = aux;
        *control = new;
        return 1;
    }
}

int ver_ind(INDEX *ini, char cod[6]){
    INDEX *aux = ini;
    if(aux == NULL){
        return 0;
    }
    while(aux->ind < cod[0] && aux->prox != NULL){
        aux = aux->prox;
    }
    if(aux->ind == cod[0]){
        return 1;
    }
    else{
        return 0;
    }
}

void cad_ind(INDEX **ini, char cod[6]) {
    INDEX *new, *aux = *ini, *ant = NULL; 
    new = (INDEX*)malloc(sizeof(INDEX));
    if (new == NULL) {
        printf("Erro de alocação de memória.");
        return;
    }
    new->ind = cod[0];
    new->prox = NULL;
    new->ini = NULL;
    
    if (*ini == NULL) {
        *ini = new;
        return;
    }
    
    while (aux != NULL && new->ind > aux->ind) {
        ant = aux;
        aux = aux->prox;
    }
    
    if (aux == NULL) {
        ant->prox = new;
    } else if (ant == NULL) {
        new->prox = *ini;
        *ini = new;
    } else {
        ant->prox = new;
        new->prox = aux;
    }
}

char* aterissa(INDEX *ini, SMPNODO **control){
    SMPNODO *aux = *control, *ant = NULL;
    INDEX *indice = ini;
    NODO *val = NULL;

    if(aux == NULL){
        printf("Nenhum avião, escalado para aterrisar.");
        return NULL;
    }

    while(aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
    }

    while (indice != NULL && aux->num[0] != indice->ind) {
        indice = indice->prox;
    }

    val = indice->ini;

    while(strcmp(aux->num,val->id) != 0){
        val = val->prox;
    }
    val->att++;
    if (ant != NULL) {
        ant->prox = NULL;
    } else {
        *control = NULL;
    }
    free(aux);
    char* result = malloc(strlen(val->id));
    if(result == NULL){
        printf("Erro de alocação.");
        return NULL;
    }
    
    strcpy(result, val->id);
    return result;
}

char* decola(INDEX *ini, SMPNODO **control){
    SMPNODO *aux = *control, *ant = NULL;
    INDEX *indice = ini;
    NODO *val = NULL;

    if(aux == NULL){
        printf("Nenhum avião, escalado para decolar.");
        return NULL;
    }

    while(aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
    }

    while (indice != NULL && aux->num[0] != indice->ind) {
        indice = indice->prox;
    }

    val = indice->ini;

    while(strcmp(aux->num,val->id) != 0){
        val = val->prox;
    }
    val->att++;
    if (ant != NULL) {
        ant->prox = NULL;
    } else {
        *control = NULL;
    }
    free(aux);
    char* result = malloc(strlen(val->id));
    if(result == NULL){
        printf("Erro de alocação.");
        return NULL;
    }
    
    strcpy(result, val->id);
    return result;
}

void esc_smpnodo_aterrisagem(SMPNODO *ini, HEADER *cont) {
    SMPNODO *aux = ini;
    HEADER *num = cont;
    while (aux != NULL) {
        printf("%d - Avião: %s\n",num->atte, aux->num);
        (num->atte)--;
        aux = aux->prox;
    }
}

void esc_smpnodo_decola(SMPNODO *ini, HEADER *cont) {
    SMPNODO *aux = ini;
    HEADER *num = cont;
    while (aux != NULL) {
        printf("%d - Avião: %s\n",num->deco, aux->num);
        (num->deco)--;
        aux = aux->prox;
    }
}

void skip(){
    while (getchar() != '\n');
    printf("\n\nPressione Enter para retornar ao menu principal...\n");
    while (getchar() != '\n');
}

void add_relat(char *id, REPORT **ini, char tag[12]){
    REPORT *new, *sup = *ini;

    new = (REPORT*)malloc(sizeof(REPORT));
    if (new == NULL) {
        return;
    }

    strcpy(new->num, id);
    strcpy(new->tag, tag);
    new->prox = NULL;
    
    if (sup == NULL){
        *ini = new;
        return;
    }

    while (sup->prox != NULL){
        sup = sup->prox;
    }
    sup->prox = new;
}


void esc_relat(REPORT *ini) {
    REPORT *aux = ini;
    while (aux != NULL) {
        printf("Avião: %s / Tag: %s\n", aux->num, aux->tag);
        aux = aux->prox;
    }
}

int main(){
    INDEX *dicty; //Ponteiro index da lista
    SMPNODO *fdec; //Ponteiro lista de decolagens
    SMPNODO *fate; //Ponteiro lista de aterissagens
    REPORT *relat; //Ponteiro para os já executados
    HEADER *cont; //contador

    relat = NULL;
    cont = NULL;
    dicty = NULL;
    fdec = NULL;
    fate = NULL;
    
    cont = (HEADER*)malloc(sizeof(HEADER));
    cont->deco = 0;
    cont->atte = 0;

    int escolha;
    char id[6];
    int i;
    char *aviao;
    printf("\nBem-vindo ao FlightHub Manager!\n");
    while (1) {
        printf("╔═══════════════════════════════════════════════╗\n");
        printf("║                    Opções                     ║\n");
        printf("╠═══════════════════════════════════════════════╣\n");
        printf("║  1. Cadastrar nova aeronave    (ok)           ║\n");
        printf("║  2. Escrever lista de todos os aviões   (ok)  ║\n");
        printf("║  3. Inserir aeronave na fila de decolagem     ║\n");
        printf("║  4. Autorizar decolagem de aeronave           ║\n");
        printf("║  5. Inserir aeronave na lista de aterrisagem  ║\n");
        printf("║  6. Autorizar aterrisagem de aeronave         ║\n");
        printf("║  7. Próximas decolagens                       ║\n");
        printf("║  8. Próximas aterrisagens                     ║\n");
        printf("║  9. Relátorio de aterisagens e decolagens     ║\n");                 
        printf("║  0. Encerrar o programa                       ║\n");
        printf("╚═══════════════════════════════════════════════╝\n");
        printf("\nPor favor, escolha uma opção: ");
        
        scanf("%d", &escolha);
        memset(id,0,sizeof(id));
        
        switch (escolha) {
            case 1: //ok
                printf("\nVocê escolheu a opção 1: Cadastrar nova aeronave.\n");
                printf("Insira o código da aeronave a ser cadastrada: \n");
                printf("[Lembrando que o código é composto por 2 letras seguido por 3 números]\n");
                while (getchar() != '\n');
                fgets(id, sizeof(id), stdin);
                conv_id(id);
                if(ver_ind(dicty,id) == 0){
                    cad_ind(&dicty,id);
                }
                i = cadastra_aviao(&dicty,id);
                if(i != 1){
                    printf("\n\nAvião %s cadastrado com sucesso!\n",id);
                }
                skip();
                break;
            case 2: //ok
                printf("\nVocê escolheu a opção 2: Escrever lista de aviões.\n");
                esc_list(dicty);
                skip();
                break;
            case 3: //ok
                printf("\nVocê escolheu a opção 3: Inserir aeronave na fila de decolagem.\n");
                printf("Insira o código da aeronave a ser incluída na fila de decolagem: \n");
                printf("[Lembrando que o código é composto por 2 letras seguido por 3 números]\n");
                while (getchar() != '\n');
                fgets(id, sizeof(id), stdin);
                conv_id(id);
                i = enfileira(&fdec, dicty, id);
                if(i != 0){
                    printf("\nAvião %s foi inserido na fila de decolagem.\n", id);
                    (cont->deco)++;
                }
                skip();
                break;
            case 4: //ok
                printf("\nVocê escolheu a opção 4: Autorizar decolagem de aeronave.\n");
                aviao = decola(dicty, &fdec);
                if (aviao != NULL){
                    printf("Avião %s foi autorizado a decolar\n", aviao);
                    (cont->deco)--;
                    add_relat(aviao, &relat, "Decolagem");
                }
                skip();                
                break;
            case 5: //ok
                while (getchar() != '\n');
                printf("\nVocê escolheu a opção 5: Inserir aeronave na lista de aterrisagem.\n");
                printf("Insira o código da aeronave a ser incluída na fila de decolagem: \n");
                printf("[Lembrando que o código é composto por 2 letras seguido por 3 números]\n");
                fgets(id, sizeof(id), stdin);
                conv_id(id);
                i = enfileira(&fate, dicty, id);
                if(i != 0){
                    printf("\nAvião %s foi inserido na fila de aterrisagem.\n", id);
                    (cont->atte)++;
                }
                skip();
                break;
            case 6:
                printf("\nVocê escolheu a opção 6: Autorizar aterrisagem de aeronave.\n");
                aviao = decola(dicty, &fate);
                if (aviao != NULL){
                    printf("Avião %s foi autorizado a aterrisar\n", aviao);
                    (cont->atte)--;
                    add_relat(aviao, &relat, "Aterrisagem");
                }
                skip();
                break;
            case 7:
                printf("\nVocê escolheu a opção 7: Próximas decolagens.\n");
                esc_smpnodo_decola(fdec,cont);
                skip();
                break;
            case 8:
                printf("\nVocê escolheu a opção 8: Próximas aterrisagens.\n");
                esc_smpnodo_aterrisagem(fate, cont);
                skip();
                break;
            case 9:
                printf("\nVocê escolheu a opção 9. Relátorio de aterisagens e decolagens.\n");
                esc_relat(relat);
                skip();
                break;

            
            case 0:
                printf("\nEncerrando o programa...\n");
                return 0; 
            default:
                printf("\nOpção inválida.\n");
                break;
        }
    }

    return 0;
}