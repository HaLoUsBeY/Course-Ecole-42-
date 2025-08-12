#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


char *gnl(int fd)
{
    static char b[BUFFER_SIZE];
    static int i = 0, r = 0;
    char *line;
    int j = 0;

    if ( fd < 0 || BUFFER_SIZE <= 0 || !(line = malloc(10000)))
        return NULL;
    while(1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER_SIZE);
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


int check(char *line, char *av, int s)
{
    if (!line || !av)
        return -1;
    int i = 0;
    while (i < s && (line[i]) == av[i])
        i++;
    
    if (i < s)
        return 0;
    return 1;
}


void solve(char *line, char *av)
{
    int i, j, s;
    s = 0;
    while (av[s])
        s++;
    i = 0;
    while (line[i])
    {
        if (check(line + i, av, s))
        {
            j = 0;
            while (j < s)
            {
                line[i + j] = '*';
                j++;
            }
        }
        write(1,&line[i],1);
        i++;
    }
}



int main (int ac, char **av)
{
    (void) ac;
    char *t;

    while (1)
    {
        t = gnl(0);
        if (!t)
            break;
        solve(t, av[1]);
    }
    return 0;
}