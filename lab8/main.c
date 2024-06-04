#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char buffer[13] = "here we go";

void reader(void *args)
{
    int id, column, color;

    id = (int)args;
    column = id*20;
    color = 33+id;

    for (int line = 0; line < 20; line++)
    {
        printf("\033[%d;%dH\033[%dm%s", line+1, column+1, color, buffer);
        fflush(stdout);
        usleep(300000);
    }
}

void writer(void *args)
{
    int id;

    id = (int)args;
    
    while (1)
    {
        switch (id)
        {
            case 0:
                sprintf(buffer, "Novosibirsk");
                usleep(2000000);
                break;
            case 1:
                sprintf(buffer, "Semipalatink");
                usleep(1000000);
                break;
            case 2:
                sprintf(buffer, "Ekaterinburg");
                usleep(3000000);
                break;
            default:
                sprintf(buffer, "nothing");
                break;
        }
    }
}


int main()
{
    pthread_t rtid[3], wtid[3];
    int rc;

    printf("\033[2J\n");
    rc = pthread_create(&rtid[0], NULL, (void *)reader, (void *)0);
    rc = pthread_create(&rtid[1], NULL, (void *)reader, (void *)1);
    rc = pthread_create(&rtid[2], NULL, (void *)reader, (void *)2);

    rc = pthread_create(&wtid[0], NULL, (void *)writer, (void *)0);
    rc = pthread_create(&wtid[1], NULL, (void *)writer, (void *)1);
    rc = pthread_create(&wtid[2], NULL, (void *)writer, (void *)2);

    pthread_join(rtid[0], NULL);
    pthread_join(rtid[1], NULL);
    pthread_join(rtid[2], NULL);
}
