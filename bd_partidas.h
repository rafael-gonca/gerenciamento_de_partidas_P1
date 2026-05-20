#ifndef BDPARTIDAS_H
#define BDPARTIDAS_H

#include "partida.h"
#include "bd_times.h"

//estrutura para armazenar o banco de dados de partidas, com a quantidade de partidas cadastradas e um vetor de partidas, onde cada elemento é do tipo Partida
typedef struct {

    int quantidade;
    Partida partidas[90];

} BDPartidas;

//função que lê os dados do arquivo partidas.csv e adiciona essa partida ao banco de dados
void carregar_partidas(BDPartidas *bd);

//função que mostra os dados das partidas que correspondem ao prefixo de input, já com o modo selecionado no main
void consultar_partidas(BDPartidas* bd_p, BDTimes* bd_t, int modo, char* prefixo);

#endif