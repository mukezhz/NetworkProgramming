#include <stdio.h>
#include <stdlib.h>
#include "assignment.h"

void error_handle(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}