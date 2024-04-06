#include <stdio.h>
#include <unistd.h>


int main()
{
    char buffer[100];
    FILE *tty;
    int c;

    if (isatty(0)) {
        tty = fopen("/dev/tty", "w");
        fprintf(tty, "Enter the text\n");
        fflush(tty);
        fclose(tty);
    }
    
    c = read(0, buffer, 100);
    write(1, "This text was entered: ", 23);
    write(1, buffer, c);
}
