#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
void program1(char* filename)
{
    char buffer[100] = "It was readed: ";
    int len;
    int fhandle;
    fhandle = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
    write(1, "Vvedite: ", 9);
    len = read(0, buffer + 15, 80);
    write(fhandle, buffer, 15 + len);
    close(fhandle);
}