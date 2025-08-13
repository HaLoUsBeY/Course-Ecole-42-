#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE];
    static int i = 0, r = 0;
    int j = 0;
    char *ret = malloc(100000);
    if (!ret)
    {
        perror("Error: ");
        return NULL;
    }

    while (1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER_SIZE);
            if (r <= 0)
            {
                if (r < 0)
                {
                    perror("Error: ");
                    return NULL;
                }
                break;
            }
        }
        ret[j++] = b[i++];
        if (ret[j - 1]  == '\n')
            break;
    }
    if (j)
    {
        ret[j] = '\0';
        return ret;
    }
    else
    {
        free(ret);
        return NULL;
    }
}

#include <fcntl.h>
int main (void)
{
    char *t;
    int fd = open("abc.txt",O_RDONLY);

    while(1)
    {
        t = get_next_line(fd);
        if (!t)
            break;
        printf("%s", t);
        free(t);
        getchar();
    }
    return 0;
}