#include <windows.h>

#include <wincon.h>

#include <stdio.h>

void main()

{
	printf("task 1\n");
	char text1[] = "It was readed: ";
	char text2[] = " File overwritten";
	char buffer[100]="";

	DWORD actlen, actlen1;
	HANDLE hstdin, hstdout;
	BOOL hCheck;

	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hstdout == INVALID_HANDLE_VALUE) ExitProcess(0);
	else printf("STD_OUTPUT_HANDLE: %d\n", hstdout);

	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hstdin == INVALID_HANDLE_VALUE) ExitProcess(0);
	else printf("STD_INPUT_HANDLE: %d\n", hstdin);

	printf("input: ");

	hCheck = ReadFile(hstdin, buffer, 80, &actlen, NULL);
	if (!hCheck)ExitProcess(0);
	WriteFile(hstdout, text1, strlen(text1), 0, 0);
	WriteFile(hstdout, buffer, actlen, &actlen, 0);
	
	getchar();

	TCHAR fname[30] = TEXT("text.txt");
	HANDLE fileHandle = CreateFile(fname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	hCheck = ReadFile(fileHandle, buffer, 80, &actlen, NULL);
	if (!hCheck)ExitProcess(0);
	else {
		printf("Text in file: %s\n", buffer);
		WriteFile(fileHandle, text2, strlen(text2), 0, NULL);
		printf("%s\n", text2);
	}
	CloseHandle(fileHandle);
	getchar();
	ExitProcess(0);
}