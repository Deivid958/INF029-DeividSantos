#include <stdio.h>
#include <stdlib.h>
#define TAM 3
typedef struct{
    int chassi;
    int ano;
} info;
int main()
{
    info carro[TAM];
    int resposta = 1,qtdCarro = 0;
    int i,j,exclui,lista;
    while(resposta != 0)
    {
        printf("[0]Sair\n");
        printf("[1]Cadastrar carro\n");
        printf("[2]Atualizar carrro\n");
        printf("[3]Listar carro\n");
        printf("[4]Excluir carro\n");
        scanf("%d",&resposta);
        switch (resposta)
        {
            case 0:
                break;    
            case 1:
            {
                if(qtdCarro == TAM)
                {
                    printf("Limite atingido\n");
                    break;
                }
                else
                {
                    printf("Chassi:");
                    scanf("%d",&carro[qtdCarro].chassi);
                    printf("Ano:");
                    scanf("%d",&carro[qtdCarro].ano);
                    qtdCarro++;
                    printf("Carro cadastrado\n");
                }
                break;
            }
            case 2:
            {
                if(qtdCarro == 0)
                {
                    printf("Lista vazia\n");
                }
                else
                {
                    printf("Chassi que quer atualizar:");
                    scanf("%d",&lista);
                    for(i = 0;i < qtdCarro;i++)
                    {
                        if(carro[i].chassi == lista)
                        {
                            printf("\tAtualize\n");
                            printf("Chassi:");
                            scanf("%d",&carro[i].chassi);
                            printf("Ano:");
                            scanf("%d",&carro[i].ano);
                            printf("Carro atualizado\n");
                            break;
                        }
                        else if(i+1 == qtdCarro)
                        {
                            printf("Chassi inexistente\n");
                        }
                    }
                }
                
                break;
            }
            case 3:
            {
                if(qtdCarro == 0)
                {
                    printf("Lista vazia\n");
                }
                else
                {
                    for(i = 0;i < qtdCarro;i++)
                    {
                        printf("Carro %d:\n",i+1);
                        printf("\tChassi:%d\n",carro[i].chassi);
                        printf("\tAno:%d\n",carro[i].ano);
                    }
                }
                break;
            }
            case 4:
            {
                if(qtdCarro == 0)
                {
                    printf("Lista vazia\n");
                }
                else
                {
                    printf("Chassi que quer excluir:");
                    scanf("%d",&exclui);
                    for(i = 0;i < qtdCarro;i++)
                    {
                        if(carro[i].chassi == exclui)
                        {
                            for(j = i;j < qtdCarro-1;j++)
                            {
                                carro[j].ano = carro[j+1].ano;
                                carro[j].chassi = carro[j+1].chassi;
                            }
                            qtdCarro--;
                            printf("Carro excluido\n");
                        }
                        else if(i + 1 == qtdCarro)
                        {
                            printf("Chassi inexistente\n");
                        }
                    }
                }
                break;
            }
            default:
            {
                printf("Opcao invalida\n");
                break;
            }
        }
    }
}