#include "program1/WriteFile.c"
#include "program2/ReadFile.c"

int main() 
{
    program1("hello.txt");

    program2("hello.txt");
}