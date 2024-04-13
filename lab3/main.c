#include <stdio.h>
#include "/usr/x86_64-w64-mingw32/include/windows.h"
#include <windows.h>

void display(HANDLE h, char *text, int len, WORD attr);

int main()
{
    HANDLE hout, hin, h;
    COORD pos;
    DWORD actlen, readed, err_code, len;
    char buffer[300], err_msg[300], err_msg_to_print[300];
    BOOL rc;
    actlen = strlen(buffer);

    hin = GetStdHandle(STD_INPUT_HANDLE);
    if (hin == INVALID_HANDLE_VALUE) 
        return 1;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hout == INVALID_HANDLE_VALUE) 
        return 1;

    h = CreateFile("file", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (h == INVALID_HANDLE_VALUE)
    {
        display(hout, "Cannot open file", 16, FOREGROUND_RED);
        err_code = GetLastError();
        len = FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            err_code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            err_msg,
            sizeof(err_msg),
            NULL
        );
        CharToOem(err_msg, err_msg_to_print);

        switch (err_code)
        {
            case 2:
                display(hout, "error: file doesn\'t exist", 24, FOREGROUND_RED);
                getchar();
                return 1;
            case 32:
                display(hout, "error: file already open", 24, FOREGROUND_RED);
                while (h == INVALID_HANDLE_VALUE)
                {
                    h = CreateFile("file", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                }
                break;
            default:
                display(hout, err_msg_to_print, len, FOREGROUND_RED);
                break;
        }
    }

    display(hout, "File was openned successfully", 29, FOREGROUND_GREEN);
    ReadFile(h, buffer, 300, &actlen, NULL);
    display(hout, buffer, actlen-1, FOREGROUND_BLUE);
    CloseHandle(h);

    getchar();
}

static COORD pos;

void display(HANDLE h, char *text, int len, WORD attr)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT rect;
    int rows, cols, roffset, coffset;
    roffset = 5;
    coffset = 15;

    GetConsoleScreenBufferInfo(h, &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int row = rows/2 - roffset;  
    int col = cols/2 - coffset;  
    int row_length = coffset*2; 

    if (pos.X == 0)
        pos.X = col;
    if (pos.Y == 0)
        pos.Y = row;

    while (len > 0)
    {
        int cur_len;
        DWORD actlen;
        if (len < row_length)
        {
            cur_len = len;
        }
        else 
        {
            cur_len = row_length;
        }
        len -= row_length;
        WriteConsoleOutputCharacter(h, text, cur_len, pos, &actlen);
        FillConsoleOutputAttribute(h, attr, cur_len, pos, &actlen);
        text += cur_len;
        pos.Y += 1;
    }
}

