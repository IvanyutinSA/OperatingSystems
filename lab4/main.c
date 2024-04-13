#include <errno.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CLEAR "\033[2J" 
#define RESET "\033[0;0H" 

void display(int h, char *text, int len, char *color);

int main()
{
    int fd, td, len;
    char buffer[300];
    struct flock check_lock, lock = {F_WRLCK, SEEK_SET, 0, 0};
    fd = open("file", O_RDWR);
    td = open("/dev/tty", O_WRONLY);
    write(td, CLEAR, strlen(CLEAR));

    if (td < 0)
    {
        display(td, "Cannot open terminal file", 25, RED);
        return 1;
    }

    if (fd < 0)
    {
        switch (errno)
        {
            case ENOENT:
                display(td, "File doesnt exist", 17, RED);
                break;
            default:
                display(td, "Error", 5, RED); 
                break;
        }
    }

    if (fd > 0)
    {
        fcntl(fd, F_GETLK, &check_lock);

        if (check_lock.l_type != F_UNLCK)
        {
            display(td, "File is locked", 14, RED);
        }

        fcntl(fd, F_SETLKW, &lock);
        len = read(fd, buffer, 300);
        display(td, "File contents:", 14, GREEN);
        display(td, buffer, len, BLUE);

        sleep(7);

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
    }
        
    write(td, CLEAR, strlen(CLEAR));
    write(td, RESET, strlen(RESET));
    close(td);
}

static int row, col;

void display(int fd, char *text, int len, char *color)
{
    int td, voffset, hoffset, row_len, actlen;
    char buffer[300];
    struct winsize ws;

    voffset = 5;
    hoffset = 10;

    if (row + col == 0)
    {
        td = open("/dev/tty", O_RDONLY);

        if (td < 0)
        {
            printf("Cannot open tty\n");
            fflush(stdout);
        }

        ioctl(td, TIOCGWINSZ, &ws);

        row = ws.ws_row/2-voffset; 
        col = ws.ws_col/2-hoffset;
    }
    row_len = 2*hoffset;

    sprintf(buffer, "\033[%d;%dH", row, col);
    write(fd, buffer, strlen(buffer));

    write(fd, color, strlen(color));

    while (len > 0)
    {
        if (len < row_len)
        {
            actlen = len;
        }
        else 
        {
            actlen = row_len;
        }
        len -= row_len;
        write(fd, text, actlen);
        text += actlen;
        row++;
        sprintf(buffer, "\033[%d;%dH", row, col);
        write(fd, buffer, strlen(buffer));
    }

    close(td);
}

