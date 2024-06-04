#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char lbuk[]="abcdefghijklmnoprstvuwxy";
pthread_t tid1, tid2, tid3;

void procthread1(void *arg)
{
    int k, j;
    for (k=0; k<24; k++)
    {
        for (j=0; j<(int)arg; j++)
        {
            printf("\033[%d;20H\033[1;34m%c\n", k+1, lbuk[k]);
            usleep(1000000);
        }
    }
}

void procthread2(void *arg)
{
    int k, j;
    for (k=0; k<24; k++)
    {
        for (j=0; j<(int)arg; j++)
        {
            printf("\033[%d;40H\033[1;32m%c\n", k+1, lbuk[k]);
            usleep(1000000);
        }
    }
}

void procthread3(void *arg)
{
    int k, j;
    for (k=0; k<24; k++)
    {
        for (j=0; j<(int)arg; j++)
        {
            printf("\033[%d;60H\033[31m%c\n", k+1, lbuk[k]);
            usleep(1000000);
        }
    }
}

int main()
{
    int k;
    int rc;
    printf("\033[2J\n");
    rc = pthread_create(&tid1, NULL, (void*)procthread1, (void*)2);
    rc = pthread_create(&tid2, NULL, (void*)procthread2, (void*)3);
    rc = pthread_create(&tid3, NULL, (void*)procthread3, (void*)4);
    for (k=0; k<24; k++)
    {
        printf("\033[%d;1H\033[37m", k+1);
        printf("%c++\n", lbuk[k]);
        usleep(1500000);
    }
    return 0;
}
