#include <stdio.h>
#include <string.h>

int main() {

    char* s;
    s = (char*) malloc(sizeof(char) * 10);
    strcpy(s, "123456789");

    puts(s);
}
