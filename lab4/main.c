#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void display(int h, char *text, int len, char *color);

int main()
{
    int fd;
    fd = open("file", O_RDONLY);

    if (fd == -1)
    {
        display(1, "Can't open file", 15, "\033[037m");
    }
}

static int rows;
static int cols;

void display(int h, char *text, int len, char *color)
{
    char buffer[100] = "", temp[32];
    if (rows+cols == 0)
    {
        char b;
        int h_vcsa = open("/dev/vcsa", O_RDONLY);
        read(h_vcsa, &b, 1);
        rows = b;
        read(h_vcsa, &b, 1);
        cols = b;
    }

    printf("rows %d\ncols %d\n", rows, cols);
}

