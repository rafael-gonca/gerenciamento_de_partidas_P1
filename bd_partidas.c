#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

#include "bd_partidas.h"

void carregar_partidas(BDPartidas *bd){

    //inicializa e abre o arquivo partidas.csv para modo leitura
    FILE *file;
    file = fopen("partidas.csv", "r");

    //verifica se o arquivo foi aberto corretamente
    if (file == NULL){
        printf("Erro ao abrir o arquivo partidas.csv\n");
        return;
    }

    //incializa uma variável para armazenar o cabeçalho de modo a ignorar essa linha
    char cabecalho[100];
    fscanf(file, "%[^\n]\n", cabecalho);

    //incialização da quantidade de times
    bd->quantidade = 0;

    //lê os dados do arquivo, linha por linha e verifica se contem os dados corretos
    while (fscanf(file, "%d,%d,%d,%d,%d\n",
        &bd->partidas[bd->quantidade].ID,
        &bd->partidas[bd->quantidade].Time1ID,
        &bd->partidas[bd->quantidade].Time2ID,
        &bd->partidas[bd->quantidade].GolsTime1,
        &bd->partidas[bd->quantidade].GolsTime2) == 5){
        
        //incrementa a quantidade de partidas no banco de dados
        bd->quantidade++;
    }

    //fecha o arquivo
    fclose(file);
};

void consultar_partidas(BDPartidas* bd_p, BDTimes* bd_t, int modo, char* prefixo) {

    //inicializa e atribui o tamanho do prefixo
    int tamanho_prefixo = strlen(prefixo);

    //inicializa uma variável para indicar se encontrou algum time correspondente ao prefixo
    int encontrou_algum = 0;
    
    //inicializa um array para armazenar os IDs dos times que correspondem ao prefixo, para facilitar a consulta das partidas
    int ids_encontrados[100] = {0};
    
    //percorre o banco de dados de times
    for (int i = 0; i < bd_t->quantidade; i++) {

        //verifica se o prefixo corresponde ao time, ignorando diferenças entre maiúsculas e minúsculas
        if (!strncasecmp(bd_t->times[i].Nome, prefixo, tamanho_prefixo)) {

            //marca a posição no array se o time foi encontrado
            ids_encontrados[bd_t->times[i].ID] = 1;

            //indica que encontrou pelo menos um time correspondente ao prefixo
            encontrou_algum = 1;
        }
    }

    //verifica se encontrou algum time correspondente ao prefixo, se não, mostra mensagem de erro e retorna para evitar mostrar partidas sem sentido
    if (!encontrou_algum) {
        printf("\nNenhum time foi encontrado com o prefixo '%s'. \n", prefixo);
        return;
    }
    
    //inicializa uma variável para indicar se encontrou alguma partida correspondente aos critérios 
    int encontrou_partida = 0;

    //imprime o cabeçalho da tabela de partidas
    printf("\n%-5s %-15s %-10s %-15s\n", "ID", "Time1", "Placar", "Time2");

    //percorre o banco de dados de partidas
    for (int i = 0; i < bd_p->quantidade; i++) {

        //atribui a partida atual a uma variável para facilitar o acesso aos seus dados
        Partida p = bd_p->partidas[i];

        //inicializa uma variável para indicar se a partida corresponde aos critérios de consulta do modo e do prefixo
        int mostrar_partida = 0;

        //verifica se a partida corresponde aos critérios de consulta do modo e do prefixo

        //caso seja 1, imprime as partidas onde o time mandante corresponde ao prefixo
        if (modo == 1 && ids_encontrados[p.Time1ID]) {
            mostrar_partida = 1;

        //caso seja 2, imprime as partidas onde o time visitante corresponde ao prefixo
        } else if (modo == 2 && ids_encontrados[p.Time2ID]) {
            mostrar_partida = 1;
             
        //caso seja 3, imprime as partidas onde qualquer um dos times corresponde ao prefixo
        } else if (modo == 3 && (ids_encontrados[p.Time1ID] || ids_encontrados[p.Time2ID])) {
            mostrar_partida = 1;
        }

        //se a partida corresponde aos critérios, imprime os dados da partida
        if (mostrar_partida) {

            //busca os nomes dos times a partir dos IDs para mostrar na tabela, percorrendo o banco de dados de times
            char nome1[50] = "\0", nome2[50] = "\0";

            for (int j = 0; j < bd_t->quantidade; j++) {
                if (bd_t->times[j].ID == p.Time1ID) strcpy(nome1, bd_t->times[j].Nome);
                if (bd_t->times[j].ID == p.Time2ID) strcpy(nome2, bd_t->times[j].Nome);
            }

            //inicializa variáveis para calcular o espaçamento da tabela, considerando a possibilidade de acentos nos nomes dos times
            wchar_t w_nome1[50], w_nome2[50];
            
            //a função converte e retorna a quantidade exata de letras visíveis
            int qtd_letras1 = mbstowcs(w_nome1, nome1, 50);
            int qtd_letras2 = mbstowcs(w_nome2, nome2, 50);

            //atribui a base de 15 espaços
            int pad1 = 15;
            int pad2 = 15;

            //se tiver acento, o strlen (bytes) vai ser maior que o mbstowcs (letras)
            //soma essa diferença no tamanho da coluna
            if (qtd_letras1 != -1) {
                pad1 += (strlen(nome1) - qtd_letras1);
            }
            if (qtd_letras2 != -1) {
                pad2 += (strlen(nome2) - qtd_letras2);
            }

            // O "%-*s" permite que a gente passe o tamanho do espaçamento por variável (pad1 e pad2) e imprime as informações da partida
            printf("%-5d %-*s %d x %d      %-*s\n", p.ID, pad1, nome1, p.GolsTime1, p.GolsTime2, pad2, nome2);
            
            //indica que encontrou pelo menos uma partida correspondente aos critérios de consulta
            encontrou_partida = 1;
        }
    }

    //verifica se encontrou alguma partida correspondente aos critérios de consulta, se não, mostra mensagem de erro
    if (!encontrou_partida) {
        printf("Nenhuma partida encontrada para os criterios informados.\n");
    }
}
