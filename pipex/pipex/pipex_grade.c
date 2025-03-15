#include "pipex.h"



void o_file(char *av, int a)
{
    int result;

    if (!a)
    {
        result = open(av, O_RDONLY, 0777);
    }
    if (a == 1)
    {
        result = open(av, O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0777);
    }
    if (a == -1)
    {
        exit(0);
    }
}