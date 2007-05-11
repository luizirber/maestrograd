#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int *shm_buffer; /* buffer a ser compartilhado. Representa a matriz, cada
                  * processo filho escrevera na linha que lhe for designada. */

int main(int argc, char **argv) {
    int tam_linha, tam_coluna, *matriz1, *matriz2;
    int shmid, status;
    struct shmid_ds shmds;
    int x, y, pos;
    pid_t pid;

    printf("Entre com tamanho da linha e da coluna: ");
    scanf("%d %d", &tam_linha, &tam_coluna);

    /* Um detalhe sobre a forma de acesso a memoria compartilhada:
     * aloquei um buffer de int do tamanho da matriz, mas acesso ele como
     * se fosse um vetor. Mais facil que usar [][], na minha opiniao. */
    if ((shmid=shmget(IPC_PRIVATE,sizeof(int)*tam_linha*tam_coluna,0700))>-1){
        shm_buffer = (int *)shmat(shmid, 0, 0);
        for (y=0; y<tam_coluna; y++)
            for (x=0; x<tam_linha; x++)
                shm_buffer[y*tam_linha + x] = 0;
    }
    else {
        printf("erro na criacao da memoria compartilhada");
        exit(0);
    }

    /* gera matriz 1 */
    matriz1 = malloc(sizeof(int)*tam_linha*tam_coluna);
    for (y=0; y<tam_coluna; y++)
        for (x=0; x<tam_linha; x++)
            matriz1[y*tam_linha + x] = rand() % 90;

    /* imprime matriz 1 */
    printf("\nmatriz 1\n");
    for (y=0; y<tam_coluna; y++) {
        printf("| ");
        for (x=0; x<tam_linha; x++)
            printf("%3d ", matriz1[y*tam_linha + x]);
        printf(" |\n");
    }

    /* gera matriz 2 */
    matriz2 = malloc(sizeof(int)*tam_linha*tam_coluna);
    for (y=0; y<tam_coluna; y++)
        for (x=0; x<tam_linha; x++)
            matriz2[y*tam_linha + x] = rand() % 90;

    /* imprime matriz 2 */
    printf("\nmatriz 2\n");
    for (y=0; y<tam_coluna; y++) {
        printf("| ");
        for (x=0; x<tam_linha; x++)
            printf("%3d ", matriz2[y*tam_linha + x]);
        printf(" |\n");
    }

    /* faz o fork e designa a linha correta para os filhos */
    y = 0;
    while ( y < tam_coluna ) {
        if ( (pid=fork()) > -1 ) {
            if (!pid) {
                for ( x=0; x < tam_linha; x++) {
                    pos = y*tam_linha + x;
                    shm_buffer[pos] = matriz1[pos] + matriz2[pos];
                }
                exit(0);
            }
            else {
                waitpid(pid, &status, 0);
                y++;
            }
        }
        else {
            printf("erro na criacao do filho\n");
            return -1;
        }
    }

    /* imprime matriz resultado */
    printf("\nmatriz resultado\n");
    for (y = 0; y < tam_coluna; y++) {
        printf("| ");
        for (x=0; x<tam_linha; x++)
            printf("%3d ", shm_buffer[y*tam_linha + x]);
        printf(" |\n");
    }

    free(matriz1);
    free(matriz2);
    status = shmdt((int *)shm_buffer);
    status = shmctl(shmid,IPC_RMID,&shmds);

    return 0;

}

