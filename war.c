#include <stdio.h>
#include <string.h>

//Definindo uma constante para o tamanho da variável nome e cor.
#define MAX_NOME 30 
#define MAX_COR 15

//Criação da struct usando a função typedef. E logo após nomeando a struct "territorio"
typedef struct{
    char nome [MAX_NOME];
    char cor [MAX_COR];
    int tropa;
}territorio;

/*Função para limpar o buffer:
A variável C recebe a função getchar() que ler caractere. E essa função está dentro do while que chama repetidamente essa função enquanto o caractere lido for diferente de \n (enter) ou EOF(final do arquivo)*/
void limparBuffer(){
    int c;                  
    while((c = getchar())!= '\n' && c != EOF);
    
}

//Iniciando a função principal 
int main(){

    territorio territorio[5];
   

    printf("=============================================\n");
    printf("B E M - V I N D O   A O   J O G O   W A R\n");
    printf("=============================================\n");


    for(int i = 0; i <= 4; i++){
        printf("---------- Cadastrando Território %d -----------\n", i + 1);

        printf("Nome do Território: ");
        fgets(territorio[i].nome, MAX_NOME, stdin);

        printf("Cor do Exército (ex: Azul, Verde): ");
        fgets(territorio[i].cor, MAX_COR, stdin);

        printf("Número de Tropas: ");
        scanf("%d", &territorio->tropa);

        limparBuffer();

        printf("\n");

        if(i == 4){
            printf("Tropas Cadastradas com Sucesso!");
        }
    }

    puts("\n");
    printf("==================================================================================\n");
    printf("\n                             MAPA DO MUNDO - SITUAÇÃO ATUAL                   \n" );
    printf("\n===================================================================================\n");

    for(int i = 0; i <= 4; i++){
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf("- Nome do território: %s", territorio[i].nome);
        printf("- Cor do território: %s", territorio[i].cor);
        printf("- Número de tropas: %d", territorio->tropa); 
        
        printf("\n");
    }
    printf("\n==================================================================================\n");
    

return 0;

}
