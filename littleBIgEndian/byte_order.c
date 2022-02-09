#include <stdio.h>

int main(int argc, char const *argv[])
{
    union Guru
    {
        short s;   // 2Bytes
        char c[2]; // 2*1Bytes = 2Bytes  1char size = 1Bytes
    };  // s and c will use same memory address
    union Guru un; // sizeof(un) == 2
    un.s = 0x0103; // hex is 2Byte, it will divide exactly
    printf("The size of short is, %ld\n",sizeof(un.s));
    printf("%d\n", un.s);
    printf("Size of short = %ldBytes\n",sizeof(short));
    if (sizeof(short) == 2)
    {
        if (un.c[0] == 1 && un.c[1] == 3)
            printf("Big Indian\n");
        else if (un.c[0] == 3 && un.c[1] == 1)
            printf("Little Indian\n");
        else
            printf("unknown\n");
    }
    else
        printf("sizeof(short) %ld\n", sizeof(short));

    return 0;
}
