#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Definindo uma constante para o tamanho da variável nome e cor.
#define MAX_NOME 30 
#define MAX_COR 10


struct territorio{
    char nome [MAX_NOME];
    char cor [MAX_COR];
    int tropa;
};
void limparBuffer(){
    /*Função para limpar o buffer:
    A variável C recebe a função getchar() que ler caractere. E essa função está dentro do while que chama repetidamente essa função enquanto o caractere lido for diferente de \n (enter) ou EOF(final do arquivo)*/
    int c;                  
    while((c = getchar())!= '\n' && c != EOF);
    
}

void cadastramento_de_cartas(struct territorio *mapa, int num_territorio){  
     for(int i = 0; i < num_territorio; i++){
        printf("---------- Cadastrando Território %d -----------\n", i + 1);

        printf("Nome do Território: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';   //Essa função procura a \n e substitui por \0 que para marcar o fim da string e não pular linha. Já que o fgets adiciona o \n no final da string.

        printf("Cor do Exército (ex: Azul, Verde): ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropa);

        limparBuffer();

        printf("\n");

    }

    printf("Tropas Cadastradas com Sucesso!");

}
void exibir_cartas(struct territorio *mapa, int num_territorio){
    puts("\n");
    printf("==================================================================================\n");
    printf("\n                             MAPA DO MUNDO - SITUAÇÃO ATUAL                   \n" );
    printf("\n===================================================================================\n");

    for(int i = 0; i < num_territorio; i++){
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf("- Nome do território: %s\n", mapa[i].nome);
        printf("- Cor do território: %s\n", mapa[i].cor);
        printf("- Número de tropas: %d\n", mapa[i].tropa); 
        
        printf("\n");
    }
    printf("\n==================================================================================\n");


}
int escolha_atacante(struct territorio *mapa, int num_territorio){
    int opcao_atacante;
    printf("========= FASE DE BATALHA ========\n");
    do {
        printf("Escolha o território atacante (1 a %d) ou Digite 0 para sair\n",num_territorio);
        scanf("%d", &opcao_atacante);
        limparBuffer();
        if (opcao_atacante == 0){
            printf("Até logo!");
            exit(1);
        }
        
        
    }while (opcao_atacante > num_territorio || opcao_atacante < 1);
    
    return opcao_atacante;
}

int escolha_defensor(struct territorio *mapa, int num_territorio){
    int opcao_defensor;
    do{
        printf("Escolha o território defensor (1 a %d) ou Digite 0 para sair:\n", num_territorio);
        scanf("%d", &opcao_defensor);
        limparBuffer();
        if(opcao_defensor == 0){
            printf("Até logo!");
            exit(1);
        }

    }while (opcao_defensor > num_territorio || opcao_defensor < 1);

    return opcao_defensor;
}

void atacar(struct territorio* atacante, struct territorio* defensor){
    //Verifica a quantidade de tropa do atacante para saber se ele pode atacar. Regra: o atacante que ter 2 ou mais tropas para atacar.
    if(atacante ->tropa >= 2){ 
        //Logo após define a quantidade de dados que o atacante pode lançar. O atacante precisa deixar uma tropa na base, então o cálculo é: atacante ->tropa - 1;

        int dados_atacante = atacante ->tropa - 1;

        //O atacante só pode lançar até 3 dados. Aqui verificamos se e alteramos para 3 se o resultado for maior que 3;
        if(dados_atacante > 3){      
            dados_atacante = 3;
        }

        //Agora verificar se o defensor tem pelo menos uma (1) tropa para se defender.
        if(defensor ->tropa >= 1){
            //Array para armazenar os dados do atacante e do defensor.
            int resultado_atacante[3];
            int resultado_defensor[2];
            int dados_defensor = defensor->tropa;  
        

            //O defensor só pode lançar até 2 dados. Nessa condição garantimos que o ele não tenha mais que 2 dados.
            if(dados_defensor > 2){
                dados_defensor = 2;
            }
            
            //Preenchemos as posições da array do atacante.
            for(int i = 0; i < dados_atacante; i++){
                resultado_atacante[i] = (rand() % 6) + 1;
            }

            //Preenchemos as posições da array do defensor.
            for(int i = 0; i < dados_defensor; i++){
                resultado_defensor[i] = (rand() % 6) + 1;
            }
            //Ordenação dos dados do atacante
            for(int i = 0; i < dados_atacante - 1; i++){
                for(int j = 0; j < dados_atacante - i - 1; j++){ 
                    //se o dado atual for menor que o próximo dado haverá uma troca;
                    if(resultado_atacante[j] < resultado_atacante[j+1]){
                        int temp = resultado_atacante[j];
                        resultado_atacante[j] = resultado_atacante[j+1];
                        resultado_atacante[j+1] = temp;
                    }

                }
            }
            //ordenação dos dados do defensor.
            for(int i = 0; i < dados_defensor - 1; i++){
                for(int j = 0; j < dados_defensor - i - 1; j++){
                    if(resultado_defensor[j] < resultado_defensor[j+1]){
                        int temp = resultado_defensor[j];
                        resultado_defensor[j] = resultado_defensor[j+1];
                        resultado_defensor[j+1] = temp;
                    }
                }
            }

            //Aqui começa a comparação dos dados;
            //logo abaixo temos contadores para verificar quem ganhou;
            int vitoria_atacante = 0;   
            int vitoria_defensor = 0;
            for(int i = 0; i < dados_defensor; i++){
                if(resultado_atacante[i] > resultado_defensor[i]){
                    vitoria_atacante++;
                    defensor ->tropa = defensor->tropa - 1;

                }else{
                    vitoria_defensor++;
                    atacante->tropa = atacante->tropa - 1;
                
                }
            }

            //Se o atacante tiver o maior número de vitória;
            if(vitoria_atacante > vitoria_defensor){
                //A variável tropa_transferida recebe metade das tropas do atacante; Logo após o território do defensor recebe o valor da tropa transferida (metade das tropas do atacante domina o território do defensor.); E o número de tropas do atacante é diminuida (Após enviar metade de suas tropas para o outro território);
                int tropa_transferida = atacante->tropa/2;
                defensor->tropa = tropa_transferida;
                atacante->tropa -= tropa_transferida;
                //A cor do território do defensor muda para a cor do território do atacante.
                strcpy(defensor->cor, atacante->cor);
                printf("O atacante tirou %s rolou o dado e tirou %d. Vitória do atacante!\n", atacante->nome, vitoria_atacante);
                printf(" (%s) Esse território foi dominado pelo exército %s.\n", defensor ->nome, atacante ->nome);

            } else {
                atacante ->tropa = atacante->tropa - 1;
                printf("O defensor %s rolou o dado e tirou %d. Vitória do defensor!\n", defensor ->nome, vitoria_defensor);
                printf("O atacante perdeu uma tropa\n");
                
            }
           

        }else {
            //Caso o defensor não tenha tropa (tropa == 0), o seu território será dominado pelo atacante. Aqui a função strcpy faz exatemente isso: cor do atacante = cor do defensor. Como em C para fazer atribuição de uma string para outra não pode ser usado o operador(=), então usei strcpy.
            strcpy(defensor ->cor, atacante ->cor);
            printf(" (%s) Esse território foi dominado pelo exército %s por não haver tropa para lutar.", defensor ->nome, atacante ->nome);
            
            //Em vitória automática por falta de tropa, o atacante domina o território com metade de sua tropa.
            int tropas_transferidas = atacante->tropa / 2;
            defensor ->tropa = tropas_transferidas;
            atacante ->tropa -= tropas_transferidas;
            

        }

    } else{
         printf("%s Não pode atacar o número de tropa não permite!", atacante ->nome);
    }
  

}

void verificar_alocacao_de_memoria(void* ponteiro){
    //Função para verificar se a memória foi alocada com sucesso.
    if(ponteiro == NULL){
        printf("ERRO: falha ao alocar memória!\n");
        exit(1);
    }

}



//Iniciando a função principal 
int main(){
    srand(time(NULL));

    struct territorio *mapa;
    int num_territorio;
    

    
    printf("=============================================\n");
    printf("B E M - V I N D O   A O   J O G O   W A R\n");
    printf("=============================================\n");

    printf("\nQuantos territórios você deseja cadastrar?\n");
    scanf("%d", &num_territorio);
    limparBuffer();

    //Alocação da memória 
    mapa = (struct territorio *)calloc (num_territorio, sizeof(struct territorio));

    //Chama a função para verificar memoria.
    verificar_alocacao_de_memoria(mapa);

    cadastramento_de_cartas(mapa, num_territorio);

    exibir_cartas(mapa, num_territorio);

    int atacante;
    int defensor;

    do { 
        atacante = escolha_atacante(mapa, num_territorio);
        defensor = escolha_defensor(mapa, num_territorio);

        if(strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0){
            printf("------------------------------------------------------------------\n");
            printf("Territórios com a mesma cor nao podem atacar!\n");
            printf("Escolha novamente.\n");
            printf("------------------------------------------------------------------\n");
        }

    }while(strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0);
    
    
    atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
   
    free(mapa); //libera a memória alocada 
    printf("\nMemória liberada com sucesso! Até mais!\n");

return 0;

}
