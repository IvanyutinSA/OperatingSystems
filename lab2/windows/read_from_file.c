#include <stdio.h>
#include "/usr/x86_64-w64-mingw32/include/windows.h"
#include <windows.h>

int main()
{
    DWORD len;
    HANDLE f1, f2, f3, hout;
    char buffer[100];
    char *b = buffer;

    f1 = CreateFile(
            "output", GENERIC_READ, FILE_SHARE_READ, 0,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
            ); 
    DuplicateHandle(
            GetCurrentProcess(), f1, GetCurrentProcess(), &f2,
            0, FALSE, DUPLICATE_SAME_ACCESS
    );
    f3 = CreateFile(
            "output", GENERIC_READ, FILE_SHARE_READ, 0,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
            ); 


    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetFilePointer(f1, 10, 0, FILE_BEGIN);

    printf("f1: ");
    fflush(stdout);
    ReadFile(f1, buffer, 7, &len, NULL);
    WriteFile(hout, buffer, 7, NULL, NULL);
    putchar('\n');

    printf("f2: ");
    fflush(stdout);
    ReadFile(f2, buffer+7, 7, &len, NULL);
    WriteFile(hout, buffer+7, 7, NULL, NULL);
    putchar('\n');

    printf("f3: ");
    fflush(stdout);
    ReadFile(f3, buffer+14, 7, &len, NULL);
    WriteFile(hout, buffer+14, 7, NULL, NULL);
    putchar('\n');
}

