#include <fcntl.h>
#include <unistd.h>


int main()
{
    int f_handler, input_length;
    char buffer[100];

    f_handler = open("output", O_WRONLY | O_CREAT, 0600);
    input_length = read(0, buffer, 100);
    write(f_handler, buffer, input_length);
    close(f_handler);
}

