
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

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

int check(char *line, char *ar, int s)
{
    if (!line || !ar)
        return 0;
    
    int i = 0;
    while (i < s && line[i] == ar[i])
        i++;


    if (i < s)
        return 0;
    return 1;
}




void solve(char *line, char *ar)
{
    int i, j, s;
    s = 0;

    while (ar[s])
        s++;
    i = 0;
    while(line[i])
    {
        if (check(line + i, ar, s))
        {
            j = 0;
            while (j < s)
            {
                line [i + j] = '*';
                j++;
            }
        }
        write(1,&line[i],1);
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    
    char *t;
    while (1)
    {
        t = get_next_line(0);
        if (!t)
            break;
        solve(t, av[1]);
        free(t);
    }
    return 0;
}