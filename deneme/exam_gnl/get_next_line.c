#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>


char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE];
    static int i = 0, r = 0;
    char *line = NULL;
    int j = 0;

    if ( fd < 0 || BUFFER_SIZE <= 0 || !(line = malloc(100000)))
        return NULL;
    while (1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER_SIZE);
            if (r <= 0)
                break;
        }
        line[j++] = b[i++]; 
        if (line[j - 1] == '\n')
            break;
    }
    if (j)
    {
        line[j] = '\0';
        return line;
    }
    else
    {
        free(line);
        return NULL;
    }
}
#include <stdio.h>
#include <fcntl.h>
int main (void)
{
    char *t;
    int fd = open("abc.txt", O_RDONLY);

    while (1)
    {
        t = get_next_line(fd);
        if (!t)
            break;
        printf("%s", t);
        getchar();
    }
    return 0;
}