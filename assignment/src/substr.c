#include <stdlib.h>

#include "assignment.h"

char *substr(char *str, int position, int length)
{
    char *p;
    p = malloc(length + 1);
    if (p == NULL)
        error_handle("Unable to allocate memory.\n");
    int i;
    for (i = 0; i < length; i++)
    {
        *(p + i) = *(str + position - 1);
        str++;
    }

    *(p + i) = '\0';
    return p;
}