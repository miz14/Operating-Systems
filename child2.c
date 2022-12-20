#include <stdio.h>
#include <windows.h>
#include <locale.h>


int main(int argn, char* args[]) {
	setlocale(LC_ALL, "Rus");
	STARTUPINFO startupInfo1;
	PROCESS_INFORMATION processInfo1;
	HANDLE handle1;
	TCHAR child1[] = TEXT("grandChild2.exe Антон Александрович");

	memset(&startupInfo1, 0, sizeof(STARTUPINFO));
	startupInfo1.cb = sizeof(startupInfo1);

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Sleep(1000);

	if (!CreateProcess(NULL, child1, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo1, &processInfo1)) {
		SetConsoleTextAttribute(console, 12);
		printf("Ошибка создания процесса grandChild2.exe: %d\n", GetLastError());
		fflush(stdout);
		SetConsoleTextAttribute(console, 7);
	}

	handle1 = CreateJobObject(NULL, NULL);
	AssignProcessToJobObject(handle1, processInfo1.hProcess);

	for (int i = 1; i < 20; i++) {
		printf("Cын 2. Мое имя %s %s. (%d)\n", args[1], args[2], i);
		fflush(stdout);

		if (i == 3) {
			TerminateJobObject(handle1, 0);
			SetConsoleTextAttribute(console, 12);
			printf("Процесс grandChild2 отсновлен.\n");
			SetConsoleTextAttribute(console, 7);
		}

		Sleep(1700);
		
	}

	CloseHandle(processInfo1.hProcess);
	CloseHandle(processInfo1.hThread);
	getchar();
	return 0;
}
