#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int f1, f2, f3;
    char buffer[100];
    f1 = open("output", O_RDONLY);
    f2 = dup(f1);
    f3 = open("output", O_RDONLY);

    lseek(f1, 10, SEEK_SET);

    printf("f1: %d\nf2: %d\nf3: %d\n", f1, f2, f3);
    fflush(stdout);
    
    printf("f1: ");
    fflush(stdout);
    read(f1, buffer, 7);
    write(1, buffer, 7);
    putchar('\n');
    
    printf("f2: ");
    fflush(stdout);
    read(f2, buffer, 7);
    write(1, buffer, 7);
    putchar('\n');
    
    printf("f3: ");
    fflush(stdout);
    read(f3, buffer, 7);
    write(1, buffer, 7);
    putchar('\n');

    close(f1);
    close(f3);
}
