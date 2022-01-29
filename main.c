#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct param {
    char *text;
    int *nbThread;
    int indice;
} Param;

void delay(int ms) {
    long pause;
    clock_t now, then;

    pause = ms * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while((now - then) < pause)
        now = clock();
}

char *input() {
    char *choice = malloc(sizeof(char) * 10);

    while (strlen(choice) == 0) {
        printf("Entrer un text : ");
        scanf("%s", choice);
    }

    return choice;
}

void *callback(void* arg) {
    Param *param = (Param*) arg;
    char *texte = param->text;
    int *nb = param->nbThread;
    
    for (int i = 0; i < 5; i++) {
        printf("msg : %s, nbThread : %d, i : %d\n", texte, *nb, i);
        delay(1000);
    }

    (*nb)--;
    free(texte);
    pthread_exit(0);
}

int main(int argc, char **argv) {
    char *text;
    pthread_t thread[10];
    int nbThread = 0;
    bool ok = true;
    Param param[10];

    while (ok) {
        text = input();
        if (strcmp(text, "non") != 0) {
            printf("appel de pthread, msg : %s, nbThread : %d\n", text, nbThread);

            param[nbThread].nbThread = &nbThread;
            param[nbThread].indice = nbThread;
            param[nbThread].text = malloc(sizeof(char) * 10);
            strcpy(param[nbThread].text, text);

            pthread_create(&thread[nbThread], NULL, callback, &param[nbThread]);

            nbThread++;
        }
        else
            ok = false;
    }
    free(text);

    return 0;
}
