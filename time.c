#include "time.h"

int calcula_pontos(Time t){
    //retorno do valor inteiro de pontos
    return (t.V*3 + t.E);
}

int calcula_saldo(Time t){
    //retorno do valor inteiro de saldo de gols
    return (t.GM - t.GS);
}