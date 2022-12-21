#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "Rus");
	char buffer[100]="";
	char buffer2[] = "Файл занят или используется";
	int len;
	int fhandle;
	char fname[ ]="text.txt";

	
	fhandle=open(fname, O_WRONLY, 0600);
	printf("\033[9;25H%s", buffer2);
	sleep(100);
	if (fhandle == -1) {
		system("clear");
		while(1) {
			fhandle=open(fname, O_WRONLY, 0600);
			if (fhandle != -1) break;
			sleep(1);
		}
	}
	
system("clear");
struct flock lock={F_WRLCK, SEEK_SET, 0, 0};
fcntl(fhandle, F_SETLKW, &lock);
FILE* file;
file = fopen(fname, "r");
fread(buffer, sizeof(buffer), 1,  file);
printf("\033[9;30H%s\n", buffer);
fcntl(fhandle, F_SETLKW, &lock);
getchar();
//sleep(1);
lock.l_type=F_UNLCK;
fcntl(fhandle, F_SETLK, &lock);
close(fhandle);
}
// #include <windows.h>
// #include <stdio.h>
// #include <winerror.h.>
// #include <locale.h>
// void main() {
// 	setlocale(LC_ALL, "Rus");

// 	char buffer[100] = "";

// 	HANDLE hstdout, fhandle;
// 	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

// 	DWORD len;
// 	TCHAR fname[] = TEXT("text.txt");
// 	COORD coord;
// 	coord.X = 55;
// 	coord.Y = 12;
// 	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY | FOREGROUND_RED);
// 	SetConsoleCursorPosition(hstdout, coord);

// 	fhandle = CreateFile(fname, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

// 	if (fhandle == INVALID_HANDLE_VALUE) {
// 		int lastErr = GetLastError();
// 		if (lastErr == 2) printf("File not found");
// 		else if (lastErr == 32) printf("File is already in use");

// 		while (1) {
// 			fhandle = CreateFile(fname, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
// 			if (fhandle != INVALID_HANDLE_VALUE) break;
// 			Sleep(1000);
// 		}

// 	}

// 	system("cls");
// 	SetConsoleTextAttribute(hstdout, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
// 	SetConsoleCursorPosition(hstdout, coord);
// 	ReadFile(fhandle, buffer, 100, &len, 0);
// 	WriteFile(hstdout,buffer, len, &len, 0);

// 	getch();
// 	CloseHandle(fhandle);
// }