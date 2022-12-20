#include <stdio.h>
#include <windows.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Rus");
	STARTUPINFO startupInfo1, startupInfo2;
	PROCESS_INFORMATION processInfo1, processInfo2;
	HANDLE handle1, handle2;
	TCHAR child1[] = TEXT("child1.exe Павел Сергеевич"), child2[] = TEXT("child2.exe Александр Сергеевич");

	memset(&startupInfo1, 0, sizeof(STARTUPINFO));
	startupInfo1.cb = sizeof(startupInfo1);
	memset(&startupInfo2, 0, sizeof(STARTUPINFO));
	startupInfo2.cb = sizeof(startupInfo2);

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	printf("Мое имя Сергей. Нажмите Enter для продолжения.");
	getchar();
	fflush(stdout);

	Sleep(1000);


	if (!CreateProcess(NULL, child1, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo1, &processInfo1)) {
		SetConsoleTextAttribute(console, 12);
		printf("Error CreateProcess child1.exe: %d\n", GetLastError());
		fflush(stdout);
	}

	Sleep(1000);

	if (!CreateProcess(NULL, child2, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo2, &processInfo2)) {
		SetConsoleTextAttribute(console, 12);
		printf("Error CreateProcess child2.exe: %d\n", GetLastError());
		fflush(stdout);
		SetConsoleTextAttribute(console, 7);
	}


	handle1 = CreateJobObject(NULL, NULL);
	AssignProcessToJobObject(handle1, processInfo1.hProcess);
	handle2 = CreateJobObject(NULL, NULL);
	AssignProcessToJobObject(handle2, processInfo2.hProcess);

	

	for (int i = 1; i < 13; i++) {
		SetConsoleTextAttribute(console, 3);
		printf("Родительский цикл: %d\n", i);
		SetConsoleTextAttribute(console, 7);
		fflush(stdout);

		if (i == 7) {
			fflush(stdout);
			TerminateJobObject(handle1, 0);
			SetConsoleTextAttribute(console, 12);
			printf("Процесс child1 отсновлен.\n");
			SetConsoleTextAttribute(console, 7);
		}

		if (i == 11) {
			fflush(stdout);
			TerminateJobObject(handle2, 0);
			SetConsoleTextAttribute(console, 12);
			printf("Процесс child2 отсновлен.\n");
			SetConsoleTextAttribute(console, 7);
		}

		Sleep(2000);
	}

	CloseHandle(processInfo1.hProcess);
	CloseHandle(processInfo1.hThread);
	CloseHandle(processInfo2.hProcess);
	CloseHandle(processInfo2.hThread);
	getchar();
	return 0;
}