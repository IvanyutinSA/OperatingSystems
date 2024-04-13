#include <stdio.h>
#include "/usr/x86_64-w64-mingw32/include/windows.h"
#include <windows.h>

int main()
{
    HANDLE hout, hin;
    DWORD actlen, readed;

    char buffer[100];
    BOOL rc;
    actlen = strlen(buffer);

    hin = GetStdHandle(STD_INPUT_HANDLE);
    if (hin == INVALID_HANDLE_VALUE) 
        return 1;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hout == INVALID_HANDLE_VALUE) 
        return 1;

    printf("standard input: %d\n", (int) STD_INPUT_HANDLE);
    printf("standard output: %d\n", (int) STD_OUTPUT_HANDLE);
    fflush(stdout);

    WriteFile(hout, "Enter the text\n", 15, NULL, NULL);
    rc = ReadFile(hin, buffer + actlen, 100, &readed, NULL);
    if (!rc)
        return 1;

    actlen += readed;
    WriteFile(hout, "This text was entered: ", 23, NULL, NULL);
    WriteFile(hout, buffer, actlen, NULL, NULL);
    getchar();
}
