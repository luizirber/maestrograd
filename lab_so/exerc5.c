#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#define TAM_BUFFER 12

char buffer[TAM_BUFFER];
char input_string[TAM_BUFFER];

sem_t s_item,   /* quantidade de itens no buffer */
      s_mutex,  /* apenas um thread pode acessar o buffer por vez */
      s_espaco; /* espaco disponivel no buffer */

int running = 1;
int disponivel;

void * produtor(void *thread_num) {
    int i;
    while(running) {
        sem_wait(&s_espaco);
        sem_wait(&s_mutex);

        printf("Digite! ");
        scanf("%s", &input_string);
        fflush(stdin);
        if (!strncmp(input_string, "fim", 3)) {
            running = 0;
            sem_post(&s_item);
            sem_post(&s_mutex);
            break;
        }
        else {
              for(i=0; i<strlen(input_string) && i<TAM_BUFFER; i++) {
                  sem_getvalue(&s_item, &disponivel);
                  buffer[disponivel] = input_string[i];
                  sem_trywait(&s_espaco);
                  sem_post(&s_item);
              }
        }
        sem_post(&s_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void * consumidor(void* thread_num) {
    while(running) {
        int i;
        sem_wait(&s_item);
        sem_wait(&s_mutex);
        sem_getvalue(&s_item, &disponivel);
        printf("\nconsumiu:");
        for (i=0; i<=disponivel; i++) {
            printf("%c", buffer[i]);
            sem_trywait(&s_item);
            sem_post(&s_espaco);
        }
        printf("\n");
        sem_post(&s_mutex);
        sleep(7);
    }
    pthread_exit(NULL);
}

int main (int argc, char** argv) {

    pthread_t th_prod, th_cons;
    char err_msg[128];

    if (sem_init(&s_mutex, 0, 1) < 0) {
        strerror_r(errno, err_msg, 128);
        printf("Erro em sem_init: %s\n", err_msg);
        exit(1);
    }

    if (sem_init(&s_espaco, 0, 12) < 0) {
        strerror_r(errno, err_msg, 128);
        printf("Erro em sem_init: %s\n", err_msg);
        exit(1);
    }

    if (sem_init(&s_item, 0, 0) < 0) {
        strerror_r(errno, err_msg, 128);
        printf("Erro em sem_init: %s\n", err_msg);
        exit(1);
    }

    if (pthread_create(&th_cons, NULL, consumidor, NULL) != 0) {
        strerror_r(errno, err_msg, 128);
        printf("Erro em pthread_create: %s\n", err_msg);
        exit(1);
    }

    if (pthread_create(&th_prod, NULL, produtor, NULL) != 0) {
        strerror_r(errno, err_msg, 128);
        printf("Erro em pthread_create: %s\n", err_msg);
        exit(1);
    }

    pthread_join(th_prod, NULL);
    pthread_join(th_cons, NULL);

    sem_destroy(&s_espaco);
    sem_destroy(&s_mutex);
    sem_destroy(&s_item);

    return 0;

}

