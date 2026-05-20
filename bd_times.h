#ifndef BDTIMES_H
#define BDTIMES_H

#include "time.h"

//estrutura para armazenar o banco de dados de times, com a quantidade de times cadastrados e um vetor de times, onde cada elemento é do tipo Time
typedef struct {

    int quantidade;
    Time times[10];

} BDTimes;

//função que lê os dados do arquivo times.csv e adiciona esse time ao banco de dados
void carregar_times(BDTimes *bd);

//função que busca a posição de um time no banco de dados a partir do seu ID
int buscar_time_por_id(BDTimes *bd, int id_procurado);

//função que mostra os dados dos times que correspondem ao prefixo de input
void consultar_times(BDTimes* bd, char* prefixo);

//função que imprime uma tabela de classificação de times com seus dados e requerindo a pontuação geral e seu saldo de gols
void tabela_classificacao(BDTimes *bd_t);

#endif