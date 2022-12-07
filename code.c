#include <windows.h>
#include <stdio.h>
#include <winerror.h.>
#include <locale.h>
void main() {
	setlocale(LC_ALL, "Rus");

	char buffer[100] = "";

	HANDLE hstdout, fhandle;
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD len;
	TCHAR fname[] = TEXT("text.txt");
	COORD coord;
	coord.X = 55;
	coord.Y = 12;
	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY | FOREGROUND_RED);
	SetConsoleCursorPosition(hstdout, coord);

	fhandle = CreateFile(fname, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (fhandle == INVALID_HANDLE_VALUE) {
		int lastErr = GetLastError();
		if (lastErr == 2) printf("File not found");
		else if (lastErr == 32) printf("File is already in use");

		while (1) {
			fhandle = CreateFile(fname, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if (fhandle != INVALID_HANDLE_VALUE) break;
			Sleep(1000);
		}

	}

	system("cls");
	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	SetConsoleCursorPosition(hstdout, coord);
	ReadFile(fhandle, buffer, 100, &len, 0);
	WriteFile(hstdout,buffer, len, &len, 0);

	getch();
	CloseHandle(fhandle);
}