#include <stdio.h>
#include <windows.h>
#include "/usr/x86_64-w64-mingw32/include/windows.h"

void highlight_character(HANDLE h, char c, COORD pos);

int main()
{
    HANDLE hin, hout, fh;
    DWORD len, actlen, default_mode, mode;
    char buffer[300];
    INPUT_RECORD inpbuf;
    MOUSE_EVENT_RECORD mouse_record;
    int stop = 0;

    hin = GetStdHandle(STD_INPUT_HANDLE);
    if (hin == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hin == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    fh = CreateFile("file", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (fh == INVALID_HANDLE_VALUE)
    {
        return 1;
    }

    ReadFile(fh, buffer, 300, &actlen, NULL);
    CloseHandle(fh);
    WriteFile(hout, buffer, actlen, &actlen, NULL);

    GetConsoleMode(hin, &default_mode);
    mode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hin, mode);

    while (!stop)
    {
        ReadConsoleInputW(hin, &inpbuf, 1, &actlen);
        switch (inpbuf.EventType)
        {
            case MOUSE_EVENT:
                mouse_record = inpbuf.Event.MouseEvent;
                if (mouse_record.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
                {
                    stop = 1;
                }
                if (mouse_record.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    char c;
                    ReadConsoleOutputCharacter(hout, &c, 1, mouse_record.dwMousePosition, &actlen);
                    if (actlen && c != ' ')
                    {
                        highlight_character(hout, c, mouse_record.dwMousePosition);
                    }
                }
                break;
        }
    }

    SetConsoleMode(hin, default_mode);
}

void highlight_character(HANDLE h, char c, COORD pos)
{
    DWORD actlen;
    FillConsoleOutputAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY, 1, pos, &actlen);
    if (isalpha(c))
    {
        if (toupper(c) == c)
        {
            FillConsoleOutputCharacter(h, tolower(c), 1, pos, &actlen);
        }
        else 
        {
            FillConsoleOutputCharacter(h, toupper(c), 1, pos, &actlen);
        }
    }
}

