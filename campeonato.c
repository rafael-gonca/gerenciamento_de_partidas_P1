#include <stdio.h>
#include "campeonato.h"

void processar_dados(BDTimes *bd_t, BDPartidas *bd_p){

    //carrega os dados dos arquivos de times e partidas
    carregar_times(bd_t);
    carregar_partidas(bd_p);

    //inicia um loop que percorre todas as partidas
    for (int i = 0; i < bd_p->quantidade; i++){

        //inicializa variáveis para armazenar os IDs dos times e as posições dos times no banco de dados, para facilitar o acesso aos dados dos times
        int id_time1 = bd_p->partidas[i].Time1ID;
        int pos_time1 = buscar_time_por_id(bd_t, id_time1);

        int id_time2 = bd_p->partidas[i].Time2ID;
        int pos_time2 = buscar_time_por_id(bd_t, id_time2);

        //processa os dados do time 1 e do time 2, atualizando as informações faltantes
        int gols1 = bd_p->partidas[i].GolsTime1;
        int gols2 = bd_p->partidas[i].GolsTime2;

        //adiciona gols marcados e sofridos para cada time
        bd_t->times[pos_time1].GM += gols1;
        bd_t->times[pos_time1].GS += gols2;
        bd_t->times[pos_time2].GM += gols2;
        bd_t->times[pos_time2].GS += gols1;
        
        //verifica se foi uma vitória, derrota ou empate para cada time, e atualiza os contadores
        if (gols1 > gols2){
            bd_t->times[pos_time1].V++;
            bd_t->times[pos_time2].D++;
        } else if (gols1 < gols2){
            bd_t->times[pos_time1].D++;
            bd_t->times[pos_time2].V++;
        } else if (gols1 == gols2){
            bd_t->times[pos_time1].E++;
            bd_t->times[pos_time2].E++;
        }
    }
}

void caso_1(BDTimes *bd_t){

    //inicializa uma variável para armazenar o nome ou prefixo do time
    char select_time[50];
    printf("Digite o nome ou prefixo do time: ");
    scanf(" %s", select_time);

    //faz a consulta de times
    consultar_times(bd_t, select_time);
}

void caso_2(BDTimes *bd_t, BDPartidas *bd_p, int opt){

    //inicializa uma variável para armazenar o nome ou prefixo do time, para a consulta de partidas com esse time
    char prefixo[50];
    printf("Digite o nome: ");
    scanf("%s", prefixo);

    //faz a consulta de partidas já com o modo selecionado
    consultar_partidas(bd_p, bd_t, opt, prefixo);
}