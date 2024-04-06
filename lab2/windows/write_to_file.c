#include <stdio.h>
#include "/usr/x86_64-w64-mingw32/include/windows.h"
#include <windows.h>


int main()
{
    char buffer[100];
    DWORD actlen;
    HANDLE hin, f_handle;
    BOOL rc;

    hin = GetStdHandle(STD_INPUT_HANDLE);
    if (hin == INVALID_HANDLE_VALUE)
        return 1;
    f_handle = CreateFile(
            "output", GENERIC_WRITE, 0, 0,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
            );

    if (f_handle == INVALID_HANDLE_VALUE)
        return 1;

    rc = ReadFile(hin, buffer, 100, &actlen, NULL);

    if (!rc)
        return 1;

    WriteFile(f_handle, buffer, actlen, NULL, NULL);

    CloseHandle(f_handle);
}
