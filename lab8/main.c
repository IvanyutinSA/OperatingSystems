#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char buffer[12] = "Started...";
int n = 0;
sem_t s, w;


void reader(void *args)
{
    int id, column, color;

    id = (int)args;
    column = id*20;
    color = 33+id;

    for (int line = 0; line < 20; line++)
    {
        sem_wait(&s);
        n += 1;
        if (n == 1)
        {
            sem_wait(&w);
        }
        sem_post(&s);

        printf("\033[%d;%dH\033[%dm%s", line+1, column+1, color, buffer);
        fflush(stdout);
        
        sem_wait(&s);
        n -= 1;
        if (n == 0)
        {
            sem_post(&w);
        }
        sem_post(&s);
        usleep(300000);
    }
}

void writer(void *args)
{
    int id;

    id = (int)args;
    
    while (1)
    {
        sem_wait(&w);
        fflush(stdout);
        switch (id)
        {
            case 0:
                sprintf(buffer, "Novos");
                usleep(1000000);
                sprintf(buffer+5, "ibirsk");
                break;
            case 1:
                sprintf(buffer, "Semipalatink");
                usleep(1000000);
                sprintf(buffer+5, "alatink");
                break;
            case 2:
                sprintf(buffer, "Ekaterinburg");
                usleep(1000000);
                sprintf(buffer+5, "rinburg");
                break;
            default:
                sprintf(buffer, "nothing");
                break;
        }
        usleep(1000000);
        sem_post(&w);
        usleep(2500000);
    }
}


int main()
{
    pthread_t rtid[3], wtid[3];
    int rc;

    sem_init(&s, 0, 1);
    sem_init(&w, 0, 1);

    printf("\033[2J\n");
    rc = pthread_create(&rtid[0], NULL, (void *)reader, (void *)0);
    rc = pthread_create(&rtid[1], NULL, (void *)reader, (void *)1);
    rc = pthread_create(&rtid[2], NULL, (void *)reader, (void *)2);

    rc = pthread_create(&wtid[0], NULL, (void *)writer, (void *)0);
    rc = pthread_create(&wtid[1], NULL, (void *)writer, (void *)1);
    rc = pthread_create(&wtid[2], NULL, (void *)writer, (void *)2);

    pthread_join(rtid[0], 0);
    pthread_join(rtid[1], 0);
    pthread_join(rtid[2], 0);
    sem_destroy(&s);
    sem_destroy(&w);
    putchar('\n');
}
