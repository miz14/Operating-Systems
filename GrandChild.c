#include <stdio.h>
#include <windows.h>
#include <locale.h>


int main(int argn, char* args[]) {
	setlocale(LC_ALL, "Rus");

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Sleep(1000);

	for (int i = 1; i < 9; i++) {
		printf("Внук 1. Мое имя %s %s. (%d)\n", args[1], args[2], i);
		fflush(stdout);
		Sleep(1000);
	}

	return 0;
}
