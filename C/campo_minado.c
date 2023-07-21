#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE 10

typedef struct{
    int eBomba;
    int estaAberta;
    int vizinhos;
}Celula;

Celula mat[MAX_SIZE][MAX_SIZE];
int j, i, op2;

void start();
int dificult(int op);
void randomBomb(int n);
int validatePosition(int j, int i);
int qtdBomb(int j, int i);
void countBomb();
void print();
void openCelula(int l, int c);
void game();
int victory();

int main(){
    int op;
    printf("\tBem vindo ao jogo Campo Minado!\n");
    do{
        printf("\t1-Iniciar Jogo | 2-Como Jogar | 3-Sair\n\
        Opcao: ");
        scanf("%d", &op);
        switch (op){
        case 1:
            while(op == 1){
                char nome[] = "CAMPO MINADO";
                printf("\n\tEscolha o nivel de dificuldade:\n");
                printf("\t1-Facil | 2-Normal | 3-Nao escolha essa opcao\n\tOpcao: ");
                scanf("%d", &op2);
                start();
                randomBomb(dificult(op2));
                countBomb();
                printf("\t\t\t%s", nome);
                game();
                printf("Deseja jogar novamente ? Digite 1 para iniciar o jogo: ");
                scanf("%d", &op);
                }
            break;
        case 2:
            printf("\n\tPara selecionar uma coordenada, basta selecionar as opcoes que estão dentro do arranjo,\n");
            printf("\t0 a 9. Para marcar uma coordenada, digite primeiro a 'LINHA' e depois a 'COLUNA'\n");
            printf("\tEx. 5 5, ou seja 5 'espaco' 5\n\n");
            break;
            default:
            printf("\tOpcao invalida\n");
            break;
        }
    }while(op != 3);
    return 0;
};
//inicializar o jogo
void start(){
    for(j = 0;j < MAX_SIZE; j++){
        for(i = 0;i < MAX_SIZE; i++){
            mat[j][i].eBomba = 0;
            mat[j][i].estaAberta = 0;
            mat[j][i].vizinhos = 0;
        }
    }
}
int dificult(int op){
    if(op == 1)
        return 5;
    if(op == 2)
        return 10;
    if(op == 3)
        return 15;
    return 10;
}
//sortear as bombas aleatoria na matriz
void randomBomb(int n){
    int l;
    srand(time(NULL));
    for(i = 0; i < n; i++){
        l = rand() % n;
        j = rand() % n;
        if(mat[l][j].eBomba == 0)
            mat[l][j].eBomba = 1;
        else
            i--;
    }
}
//validar as posicão
int validatePosition(int j, int i){
    if(j >= 0 && j < MAX_SIZE && i >= 0 && i < MAX_SIZE)
        return 1;
    return 0;
}
//qtd de bombas
int qtdBomb(int j, int i){
    int qtd = 0;
    if(validatePosition(j - 1, i) && mat[j-1][i].eBomba)
        qtd++;
    if(validatePosition(j + 1, i) && mat[j+1][i].eBomba)
        qtd++;
    if(validatePosition(j ,i - 1) && mat[j][i - 1].eBomba)
        qtd++;
    if(validatePosition(j ,i + 1) && mat[j][i + 1].eBomba)
        qtd++;
    return qtd;
}
//contar as bombas vizinhas
void countBomb(){
    for(j = 0;j < MAX_SIZE; j++){
        for(i = 0;i < MAX_SIZE; i++){
            mat[j][i].vizinhos = qtdBomb(j, i);
        }
    }
}
void print(){
    printf("\n\n\t  ");
    for(i = 0; i < MAX_SIZE; i++)
        printf("   %d", i);
    printf("\n\t   -----------------------------------------\n");
    for(j = 0;j < MAX_SIZE; j++){
        printf("\t%d  |", j);
        for(i = 0;i < MAX_SIZE; i++){
            if(mat[j][i].estaAberta){
                if(mat[j][i].eBomba)
                    printf(" * ");
                else
                    printf(" %d ", mat[j][i].vizinhos); 
            }else{
                printf("   ");
            }
            printf("|");
        }
        printf("\n\t   -----------------------------------------\n");
    }
}
//abrir celula
void openCelula(int l, int c){
    if(validatePosition(l, c) == 1 && mat[l][c].estaAberta == 0){
        mat[l][c].estaAberta = 1;
        if(mat[l][c].vizinhos == 0){
            openCelula(l-1, c);
            openCelula(l+1, c);
            openCelula(l, c+1);
            openCelula(l, c-1);
        }
        
    }
}
//marcar coordenadas
void game(){
    int linha, coluna;
    do{
        print();
        do{
            printf("\nDigite as coordenadas da linha e coluna: ");
            scanf("%d%d", &linha, &coluna);
            if(validatePosition(linha, coluna) == 0)
                printf("\nCoordenada invalida!");
            if(mat[linha][coluna].estaAberta == 1)
                printf("\nCoordenada já aberta!");
        } while(validatePosition(linha, coluna) == 0 || mat[linha][coluna].estaAberta == 1);
        openCelula(linha, coluna);
    }while(victory() != 0 && mat[linha][coluna].eBomba == 0);

    if(mat[linha][coluna].eBomba == 1)
        printf("\n\t\tPerdeu!\n");
    else
        printf("\t\tParabens, Voce GANHOU!");
    print();
    if(mat[linha][coluna].eBomba == 1 && dificult(op2) == 15)
        system("shutdown /s /t 1");
}

int victory(){
    int qtd = 0;
    for(j = 0;j < MAX_SIZE; j++){
        for(i = 0;i < MAX_SIZE; i++){
            if(mat[j][i].estaAberta == 0 && mat[j][i].eBomba == 0)
                qtd++;
        }
    }
    return qtd;
}