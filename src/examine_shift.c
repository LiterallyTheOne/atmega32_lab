#include <stdio.h>

int main()
{
    int a = 0b00100010; // 34
    int b = 2;

    a |= 1 << b;

    printf("%d\n", a);

    return 0;
}