#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "bd_times.h"
#include "bd_partidas.h"
#include "campeonato.h"

//limpa a tela do terminal
void limpar_cmd(){
    printf("\033[H\033[J");
}

//limpa o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//exibe o menu de opções principal
void menu_display(){
    printf("\nSistema de Gerenciamento de Partidas\n\n1 - Consultar time\n2 - Consultar partidas\n3 - Atualizar partida\n4 - Remover partida\n5 - Inserir partida\n6 - Imprimir tabela de classificação\nQ - Sair\n\n");
}

//função para funcionalidades ainda não implementados
void sem_func(){
    printf("\nFuncionalidade ainda não implementada\n");
}

int main(){
    setlocale(LC_ALL, "");

    //inicializa os bancos de dados
    BDTimes meus_times;
    BDPartidas minhas_partidas;

    //carrega os dados dos arquivos e processa os resultados
    processar_dados(&meus_times, &minhas_partidas);

    limpar_cmd();

    char menu_option;

    //inicia o menu principal
    while (menu_option != 'Q' && menu_option != 'q'){

        menu_display();
        scanf(" %c", &menu_option);
        limpar_buffer();

        //mostra as opções
        switch (menu_option){
            case '1':
                limpar_cmd();
                //roda a consulta de times
                caso_1(&meus_times);
                break;
            case '2':
                limpar_cmd();
                char case_2_option = '0';

                //inicia o menu secundario para consulta de partidas
                while (case_2_option != '4'){

                    //pega a opção de consulta
                    printf("\nEscolha o modo de consulta:\n1 - Por time mandante\n2 - Por time visitante\n3 - Por time mandante ou visitante\n4 - Retornar ao menu principal\n\n");
                    scanf(" %c", &case_2_option);
                    limpar_buffer();

                    //o if verifica se a opção é válida, se for, ele envia o número para a função caso_2, se não, ele mostra mensagem de erro ou fecha o menu
                    if (case_2_option == '1' || case_2_option == '2' || case_2_option == '3'){
                        limpar_cmd();
                        int opt = case_2_option - '0';
                        caso_2(&meus_times, &minhas_partidas, opt);
                    }
                    else if (case_2_option == '4') {
                        limpar_cmd();
                        break;
                    }
                    else {
                        limpar_cmd();
                        printf("selecione uma opção válida\n");
                    }
                }   

                break;
            //do 3 ao 5, as funcionalidades nao foram implementadas, então ele mostra uma mensagem dizendo isso
            case '3':
                limpar_cmd();
                sem_func();
                break;
            case '4':
                limpar_cmd();
                sem_func();
                break;
            case '5':
                limpar_cmd();
                sem_func();
                break;
            case '6':
                limpar_cmd();
                //roda a função para imprimir a tabela de classificação, sem outros argumentos ou prefixos
                tabela_classificacao(&meus_times);
                break;
            //fecha o menu e o programa
            case 'Q':
            case 'q':
                limpar_cmd();
                break;
            default:
                limpar_cmd();
                printf("\nselecione uma opção válida \n");
        }
    }
    return 0;
}