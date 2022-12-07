#include <windows.h>
#include <stdio.h>
#include <wincon.h>

void main() {
	HANDLE fhandle, handleIn, handleOut;
	DWORD symbolBuffer, cbRead;
	COORD writePos, mousePos;
	COORD symbolPos, symbolNumPos;

	symbolPos.X = 0;
	symbolPos.Y = 29;
	symbolNumPos.X = 2;
	symbolNumPos.Y = 29;

	char buffer1[100], buffer2[10];
	char charSelect;

	handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	handleIn = GetStdHandle(STD_INPUT_HANDLE);

	TCHAR fname[] = TEXT("text.txt");
	fhandle = CreateFile(fname, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (fhandle == INVALID_HANDLE_VALUE) {
		printf("File not found!\n");
		getch();
		return;
	}
	ReadFile(fhandle, buffer1, 100, &cbRead, 0);
	WriteFile(handleOut, buffer1, cbRead, &cbRead, NULL);


	SetConsoleMode(handleIn, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

	INPUT_RECORD inputRec;
	inputRec.EventType = MOUSE_EVENT;

	while (1) {
		if (ReadConsoleInput(handleIn, &inputRec, 1, &symbolBuffer, 0)) {
			if (inputRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { 
				return;
			}

			if (inputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {  

				mousePos.X = inputRec.Event.MouseEvent.dwMousePosition.X;
				mousePos.Y = inputRec.Event.MouseEvent.dwMousePosition.Y;

				ReadConsoleOutputCharacter(handleOut, &charSelect, 1, mousePos, &symbolBuffer);

				if (charSelect != ' ') {
					FillConsoleOutputAttribute(handleOut, 0x00, 100, symbolNumPos, &symbolBuffer);

					for (int i = 0; i < symbolBuffer; i++) {
						buffer2[i] = ' '; 
					}


					WriteConsoleOutputCharacter(handleOut, charSelect, 1, symbolPos, &symbolBuffer);

					SetConsoleCursorPosition(handleOut, symbolNumPos);

					SetConsoleCursorPosition(handleOut, symbolNumPos);
					printf("(%d, %d)", mousePos.X, mousePos.Y);

					if (charSelect <= 'Z' && charSelect >= 'A') {
						charSelect += 32;
						SetConsoleCursorPosition(handleOut, mousePos);
						printf("%c", charSelect);
					}
					else if (charSelect <= 'z' && charSelect >= 'a') {
						charSelect -= 32;
						SetConsoleCursorPosition(handleOut, mousePos);
						printf("%c", charSelect);
					}

					FillConsoleOutputAttribute(handleOut, BACKGROUND_RED, 1, mousePos, &symbolBuffer);
					ReadConsoleOutputCharacter(handleOut, &charSelect, 1, mousePos, &symbolBuffer);

					ReadConsoleOutputCharacter(handleOut, buffer2, symbolBuffer, mousePos, &symbolBuffer);
					WriteConsoleOutputCharacter(handleOut, buffer2, symbolBuffer, symbolPos, &symbolBuffer);

					FillConsoleOutputAttribute(handleOut, BACKGROUND_GREEN, symbolBuffer, symbolPos, &symbolBuffer);
				}
			}
		}
	}
}

