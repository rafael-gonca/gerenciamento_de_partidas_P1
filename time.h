#ifndef TIME_H
#define TIME_H

//estrutura para armazenar os dados de um único time
typedef struct {

    int ID;
    char Nome[50];
    int V;
    int E;
    int D;
    int GM; //gols marcados
    int GS; //gols sofridos

} Time;

//função que calcula os pontos de um time por requerimento
int calcula_pontos(Time t);

//função que calcula o saldo de gols de um time por requerimento
int calcula_saldo(Time t);

#endif