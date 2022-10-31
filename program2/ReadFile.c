#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
void program2(char* filename)
{
    char buffer1[7] = ""; char buffer2[7]; char buffer3[7];
    int fhandle1; int fhandle2; int fhandle3;

    fhandle1 = open(filename, O_RDONLY, 0600);
    fhandle2 = dup2(fhandle1, 22);
    fhandle3 = open(filename, O_RDONLY, 0600);
    
    printf("fhandle: %d\n", fhandle1);
    printf("fhandle2: %d\n", fhandle2);
    printf("fhandle3: %d\n", fhandle3);

    //изменяем позицию для fhandle (следовательно и для fhandle2)
    lseek(fhandle1, 10, SEEK_SET);
    read(fhandle1, buffer1, 7);
    lseek(fhandle1, 10, SEEK_SET);
    read(fhandle2, buffer2, 7);
    read(fhandle3, buffer3, 7);
    printf("read from fhandle1: %.*s\n", 7, buffer1);
    printf("read from fhandle2: %.*s\n", 7, buffer2);
    printf("read from fhandle3: %.*s\n", 7, buffer3);
    close(fhandle1);
    close(fhandle2);
    close(fhandle3);
}