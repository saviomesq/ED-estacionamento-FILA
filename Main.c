
#include <stdio.h>

#define MAX 10

typedef struct{
    int dados[10];
    int movimentos[10];
    int inicio;
    int fim;
}Fila;

void iniciar_fila(Fila *f){
    f->inicio=0;
    f->fim=0;
    for(int i=0; i<MAX; i++){
        f->dados[i]=0;
        f->movimentos[i]=0;
    }
}

int push(Fila *f, Fila *p, int n){
    if(f->fim==MAX){
        if(p->fim==MAX){
            return 0;
        }else{
            p->dados[p->fim++]=n;
            return 2;
        }
    }else{
        f->dados[f->fim++]=n;
        f->movimentos[(f->fim)-1]=0;
        return 1;
    }
}

int pop(Fila *f, Fila *p, Fila *aux, int *num){
    if(f->inicio==f->fim){
        return 0;
    }else{
        int flag=0, i=0, id=0;
        while(flag == 0 && i < f->fim){
            if(f->dados[i]==(*num)){
                flag=-1;
                id=i;
            }else{
                aux->dados[i]=f->dados[i];
                aux->movimentos[i]=f->movimentos[i];
                aux->fim++;
            }
            i++;
        }
        if(flag==0){
            printf("Nao possui nenhum carro %d estacionado!\n", (*num));
        }else{
            for(flag=i; flag<f->fim; flag++){
                aux->dados[flag-1]=f->dados[flag];
                aux->movimentos[flag-1]=f->movimentos[flag];
                aux->fim++;
            }
            for(i=0; i<aux->fim; i++){
                f->dados[i]=aux->dados[i];
                f->movimentos[i]=aux->movimentos[i]+1;
            }
            f->fim--;
            aux->fim=0;

            if(p->inicio!=p->fim){
                if(push(f, p, p->dados[0])){
                    printf("Veiculo %d retirado com %d movimentos. Veiculo %d que estava na fila foi adicionado.\n", (*num), f->movimentos[id]-1, p->dados[p->inicio]);
                    for(i=0; i<p->fim-1; i++){
                        p->dados[i]=p->dados[i+1];
                    }
                    p->fim--;
                }
            }else{
                printf("Veiculo %d retirado com %d movimentos. Nenhum veiculo na fila.\n", (*num), f->movimentos[id]-1);
            }
        }
        return 1;
    }
}




int main(){
    Fila estacionamento, aux, proximo;

    iniciar_fila(&estacionamento);
    iniciar_fila(&aux);
    iniciar_fila(&proximo);

    int o, num, cr;

    do{
        printf("1 - Adicionar veiculo\n");
        printf("2 - Remover veiculo\n");
        printf("3 - Listar carros\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &o);

        switch (o){
            case 1:
                printf("Digite o carro que deseja adicionar: ");
                scanf("%d", &num);
                int r = push(&estacionamento, &proximo, num);
                if(r==0){
                    printf("Estacionamento e fila estao cheios!\n");
                }else if(r==1){
                    printf("Carro %d estacionado!\n\n", num);
                }else{
                    printf("Estacionamento cheio! Carro %d esta na fila!\n", num);
                }
                break;
            case 2:
                printf("Digite o carro que deseja retirar: ");
                scanf("%d", &cr);
                if(pop(&estacionamento, &proximo, &aux, &cr)==0){
                    printf("O estacionamento esta vazio!\n\n");
                }
                printf("\n");
                break;
            case 3:
                if(estacionamento.fim==0){
                    printf("Estacionamento vazio!\n\n");
                }else{
                    for(int i=0; i<estacionamento.fim; i++){
                        printf("Carro estacionado na posicao %d com %d movimentos: %d.\n", i, estacionamento.movimentos[i], estacionamento.dados[i]);
                        
                    }
                    printf("\n");
                    if(proximo.fim!=0){
                        printf("================== PROXIMOS ==================\n");
                        for(int i=proximo.inicio; i<proximo.fim; i++){
                            printf("Carro na posicao %d da fila: %d.\n", i, proximo.dados[i]);
                        }
                        printf("\n");
                    }
                }
                break;
            case 4:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida! Digite uma das opcoes: \n\n");
                break;
        }

    }while(o!=4);
    return 0;
}
