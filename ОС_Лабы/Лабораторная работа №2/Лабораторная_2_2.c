#include <windows.h>
#include <stdio.h>
#include <winerror.h>

void main()
{
	DWORD cb, cbw1;
    HANDLE hstdout, fhandle, twofhandle, threefhandle;
	BOOL rc;

	char buffer[100]="";
    int len;
    char fname[ ]="Test.txt";
    len = strlen(buffer);
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hstdout == INVALID_HANDLE_VALUE) return;
    fhandle=CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (fhandle== INVALID_HANDLE_VALUE) return;
    DuplicateHandle(GetCurrentProcess(),fhandle,GetCurrentProcess(),&twofhandle,0, FALSE, DUPLICATE_SAME_ACCESS);
    threefhandle=CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (threefhandle== INVALID_HANDLE_VALUE) return;
    printf("fhandle: %d\ntwofhandle: %d\nthreefhandle: %d\n ",fhandle, twofhandle, threefhandle);
    fflush(stdout);
    
    rc=SetFilePointer(fhandle, 10, 0, FILE_BEGIN);
    rc=ReadFile(fhandle, buffer+len, 7, &cb, NULL);
    if (!rc) return;
    cb += len;
	WriteFile(hstdout, buffer, cb, &cbw1, NULL);
	
    rc=ReadFile(twofhandle, buffer+len, 7, &cb, NULL);
    if (!rc) return;
    cb += len;
    WriteFile(hstdout, buffer, cb, &cbw1, NULL);
    rc=TRUE;
	
    ReadFile(threefhandle, buffer+len, 7, &cb, NULL);
    if (!rc) return;
    cb += len;
    WriteFile(hstdout, buffer, cb, &cbw1, NULL);
    CloseHandle(fhandle);
    getchar();
    return; 
}