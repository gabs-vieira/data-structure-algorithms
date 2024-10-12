// Contexto: Organização de arquivos e índices baseado no comportamento de e-comerce de uma loja vários de departamentos

//Arquivo CSV 9GB -- Columns

/*
Columns
event_time
event_type
product_id
category_id
category_code
brand
price
user_id
user_session
*/


/*

Orientações
- Criar no mínimo 2 arquivos: produtos e acesso ao e-commerce
- Organização dos arquivos- Sequencial == Dados ordenados por ID ou outra key

• Escolher os arquivos que serão criados com o dataset fornecido;
• Cada arquivo deve ter pelo menos 3 campos (colunas) de informações: pelo menos um dos campos com dados não repetidos (o campo da chave), e pelo menos um dos campos com informações repetidas;
• Definir duas ou três perguntas que se poderia fazer a esse conjunto de dados (serão as consultas que serão realizadas nos dados);
• Ordenar os dados do arquivo de dados pelo campo chave (que não tem dados repetidos). É possível gerar as chaves pelo incremento de um número sequencial se não houver um identificador único;
• os arquivos de dados devem ser criados em modo binário (não textual).


###########################################################################3
- Registros dos arquivos de dados devem ter tamanho fixo (Inserir espaços em branco no final dos dados textuais se necessário)
- Cada linha do arquivo é encerrada no '\n'


- Para cada arquivo de dados implementar:
1. função p/ inserir dados: explicar como os dados foram ordenados e inseridos
2. Função para mostrar dados
3. Função para buscar dados com pesquisa binária
4. Função para consultar dados a partir da pesquisa binária
- Construir 2 índices, um para cada arquivo (salvos em arquivo no final da execução, e carregados quando o programa for aberto)


############################################################################
Índices em Arquivo

• Implemente um arquivo de índice parcial para o campo chave de cada arquivo de dados de acordo com a descrição do índice de arquivo da organização sequencial-indexado;
• Implemente uma função de consulta a partir deste índice usando a pesquisa binária para pesquisar no arquivo de índice e, depois o comando seek para pesquisar no arquivo de dados.
3. Inserção/remoção de dados em um dos arquivos de dados, e reconstrução do
    índice:
    • Como será gerenciada a inserção de um novo registro no arquivo de dados?
    • Como será gerenciada a remoção de um registro no arquivo de dados?

*/


#include <stdio>
#include <stdlib.h>
#include <string.h>

#DEFINE TAMANHO_BLOCO 426260 //100MB + ou - 

typedef struct{ 
    char event_time[25]; //2019-11-01 00:00:00 UTC -- 25bytes
    char event_type[25]; //vie, purchasez  -- 25bytes
    int product_id; // 4 bytes
    int category_id; // 4 bytes
    char category_code[100]; // acessos de objeto -- 100bytes 
    char brand[30]; // 30bytes
    float price; // 4 bytes
    int user_id; // 4 bytes
    char user_session[50]; //50bytes
} REGISTRO;
//Tamanho registro = 246 bytes
// Tamanho bloco  = numero registros * tamanho registro 

// Utilizando 100MB por bloco; Tamanho bloco / tamanho registro = 426.260 registros por bloco 


void particionar_csv(char *csv){

    FILE *csv_file = fopen(csv, "r");   
    if(csv_file == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    FILE *part_file;
    REGISTRO *bloco = (REGISTRO*) malloc(TAMANHO_BLOCO * sizeof(REGISTRO));
    char buffer[512]; //trocar caso algumal linha for mto maior, só fiz uma estimativa
    int count = 0, bloco_num = 0;

    while ( fgets(buffer, 512, csv_file) != NULL){
        
        //Usar regex pra pegar os valores, fica + facil
        sscanf(buffer, "%[^,],%[^,],%d,%d,%[^,],%[^,],%f,%d,%s",
            bloco[count].event_time,
            bloco[count].event_type,
            &bloco[count].product_id,
            &bloco[count].category_id,
            bloco[count].category_code,
            bloco[count].brand,
            &bloco[count].price,
            &bloco[count].user_id,
            bloco[count].user_session
        );
        count++;

        if (count == TAMANHO_BLOCO){
            char filename[50];
            sprintf(filename, "part_%d.dat", bloco_num);
            part_file = fopen(filename, "wb");
            fwrite(bloco, sizeof(REGISTRO), TAMANHO_BLOCO, part_file);
            fclose(part_file);
            bloco_num++;
            count = 0;
        }
    }

    // ultimo bloco se sobrou algum
    if( count > 0){
        char part_filenam[50];
        sprintf(part_filename, "part_%d.dat", bloco_num);
        part_file = fopen(part_filename, "wb");
        fwrite(bloco, sizeof(REGISTRO), TAMANHO_BLOCO, part_file);
        fclose(part_file);
    }

    free(bloco);
    fclose(csv_file);

}


int main (){

    particionar_csv("2019-Nov.csv");



    return 0;
}