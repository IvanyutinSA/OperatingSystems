#include <stdio.h>
#include <unistd.h>

int main()
{
    int rc, k;
    printf("Parent Process\n");
    rc = fork();
    if (!rc)
    {
        execl("child1.out", 0);
    }
    printf("For Child Process;\n");
    printf("PID=%d)\n", k);

    for (k=0; k<10; k++)
    {
        printf("I am Parent (My K=%d)\n", k);
        usleep(2000000);
    }
    printf("Parent ended\n");
    return 0;
}
