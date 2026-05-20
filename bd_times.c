#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_times.h"
#include "bd_partidas.h"

#include "bd_times.h"


void carregar_times(BDTimes *bd){

    //inicializa e abre o arquivo times.csv para modo leitura
    FILE *file;
    file = fopen("times.csv", "r");

    //verifica se o arquivo foi aberto corretamente
    if (file == NULL){
        printf("Erro ao abrir o arquivo times.csv\n");
        return;
    }

    //incializa uma variável para armazenar o cabeçalho de modo a ignorar essa linha
    char cabecalho[100];
    fscanf(file, "%[^\n]\n", cabecalho);

    //incialização da quantidade de times
    bd->quantidade = 0;

    //lê os dados do arquivo, linha por linha e verifica se contem os dados corretos
    while (fscanf(file, "%d,%[^\n]\n",
            &bd->times[bd->quantidade].ID,
            bd->times[bd->quantidade].Nome) == 2){

        //inicializa os campos de Time
        bd->times[bd->quantidade].V = 0;
        bd->times[bd->quantidade].E = 0;
        bd->times[bd->quantidade].D = 0;
        bd->times[bd->quantidade].GM = 0;
        bd->times[bd->quantidade].GS = 0;

        //incrementa a quantidade de times no banco de dados
        bd->quantidade++;
    }

    //fecha o arquivo
    fclose(file);
}


int buscar_time_por_id(BDTimes *bd, int id_procurado){

    //inicia uma busca até a quantidade de times cadastrados
    for (int i = 0; i < bd->quantidade; i++){

        //verifica se o ID do time na posição atual é igual ao ID procurado
        if (bd->times[i].ID == id_procurado){

            //retorna a posição
            return i;
        };
    };

    //se não achar o ID, retorna -1 para indicar que não encontrou
    return -1;
}

void consultar_times(BDTimes* bd, char* prefixo) {

    //inicializa e atribui o tamanho do prefixo
    int tamanho_prefixo = strlen(prefixo);

    //inicializa uma variável para indicar se encontrou algum time correspondente ao prefixo
    int encontrou = 0;

    //imprime o cabeçalho da tabela de times
    printf("\n%-5s %-15s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    //percorre o banco de dados de times
    for (int i = 0; i < bd->quantidade; i++) {

        //verifica se o prefixo corresponde ao time, ignorando diferenças entre maiúsculas e minúsculas
        if (!strncasecmp(bd->times[i].Nome, prefixo, tamanho_prefixo)) {

            //atribui o time a uma variável
            Time t = bd->times[i];
            
            //calcula o saldo de gols e os pontos do time e atribui a variáveis para facilitar a impressão
            int saldo = calcula_saldo(t);
            int pontos = calcula_pontos(t);

            //inicializa variáveis para calcular o espaçamento da tabela, considerando a possibilidade de acentos nos nomes dos times
            wchar_t w_nome[50];

            //a função converte e retorna a quantidade exata de letras visíveis
            int qtd_letras = mbstowcs(w_nome, t.Nome, 50);

            //atribui a base de 15 espaços
            int pad = 15;
            
            //se tiver acento, o strlen (bytes) vai ser maior que o mbstowcs (letras)
            //soma essa diferença no tamanho da coluna
            if (qtd_letras != -1) {
                pad += (strlen(t.Nome) - qtd_letras);
            }

            //imprime os dados do time na tabela de times, usando o pad para ajustar o espaçamento considerando os acentos
            printf("%-5d %-*s %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n", t.ID, pad, t.Nome, t.V, t.E, t.D, t.GM, t.GS, saldo, pontos);
            
            //indica que encontrou pelo menos um time correspondente ao prefixo
            encontrou = 1;
        };
    };

    //verifica se encontrou algum time correspondente ao prefixo, se não, mostra mensagem de erro
    if (!encontrou) {
        printf("Erro: Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
    };
}
void tabela_classificacao(BDTimes *bd_t) {

    //imprime o cabeçalho da tabela de classificação
    printf("\n%-5s %-15s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    
    //percorre o banco de dados de times
    for(int i = 0; i < bd_t->quantidade; i++) {

        //atribui o time atual a uma variável para facilitar o acesso aos seus dados
        Time t = bd_t->times[i];

        //calcula o saldo de gols e os pontos do time e atribui a variáveis para facilitar a impressão
        int saldo = calcula_saldo(t);
        int pontos = calcula_pontos(t);

        //inicializa variáveis para calcular o espaçamento da tabela, considerando a possibilidade de acentos nos nomes dos times
        wchar_t w_nome[50];

        //a função converte e retorna a quantidade exata de letras visíveis
        int qtd_letras = mbstowcs(w_nome, t.Nome, 50);

        //atribui a base de 15 espaços
        int pad = 15;
        
        //se tiver acento, o strlen (bytes) vai ser maior que o mbstowcs (letras)
        //soma essa diferença no tamanho da coluna
        if (qtd_letras != -1) {
            pad += (strlen(t.Nome) - qtd_letras);
        }

        //imprime os dados do time na tabela de classificação, usando o pad para ajustar o espaçamento considerando os acentos
        printf("%-5d %-*s %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n", 
               t.ID, pad, t.Nome, t.V, t.E, t.D, t.GM, t.GS, saldo, pontos);
    } 
}