#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER
#define BUFFER 42
#endif


char *gnl(int fd)
{
    static char b[BUFFER];
    static int i = 0, r = 0;
    char *line;
    int j = 0;

    if ( fd < 0 || BUFFER <= 0 || !(line = malloc(10000)))
        return NULL;
    while(1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER);
            if (r <= 0)
                break;
        }
        line[j++] = b[i++];
        if (line [j - 1] == '\n')
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


int check(char *line, char *ar, int s)
{
    if (!line || !ar)
        return -1;
    int i = 0;
    while (i < s && line[i] == ar[i])
        i++;

    if (i < s)
    {
        return 0;
    }
    else
        return 1;
}


void filter(char *str, char *ar)
{
    int i, j, s;
    s = 0;
    while (ar[s])
        s++;
    
    i = 0;
    while (str[i])
    {
        if (check(str + i, ar, s))
        {
            j = 0;
            while (j < s)
            {
                str[i + j] = '*';
                j++;
            }
        }
        write(1,&str[i],1);
        i++;
    }
}


int main (int ac, char **av)
{
    (void) ac;

    char *t;
    t = gnl(0);
    filter(t, av[1]);
    return 0;
}