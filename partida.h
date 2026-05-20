#ifndef PARTIDA_H
#define PARTIDA_H

//estrutura para armazenar os dados de uma única partida, sem funções ou cálculos, apenas os dados brutos
typedef struct {

    int ID;
    int Time1ID;
    int Time2ID;
    int GolsTime1;
    int GolsTime2;

} Partida;

#endif