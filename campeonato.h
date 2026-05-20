#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "bd_times.h"
#include "bd_partidas.h"

//função que lê os dados dos arquivos e atualiza os bancos de dados
void processar_dados(BDTimes *bd_t, BDPartidas *bd_p);

//função que lê o prefixo e executa a consulta de times
void caso_1(BDTimes *bd_t);

//função que lê o prefixo e executa a consulta de partidas, já com o modo selecionado no main
void caso_2(BDTimes *bd_t, BDPartidas *bd_p, int opt);

#endif