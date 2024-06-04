#include <stdio.h>
#include <unistd.h>

int main()
{
    int k;
    printf("Demonstration processes, Child Process");
    for (k=0; k<30; k++)
    {
        printf("-----I am Child .. (child=%d)\n", k);
        sleep(1);
    }
    printf("Child ended\n");
    return 0;
}
