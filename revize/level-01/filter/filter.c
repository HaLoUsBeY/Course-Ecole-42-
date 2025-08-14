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
    char *ret  = malloc(100000);
    int j = 0;
    if (!(ret))
    {
        perror("Error: ");
        return NULL;
    }
    if (fd < 0 || BUFFER_SIZE <= 0 )
        return NULL;
    while (1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER_SIZE);
            if (r <= 0)
            {
                if (r < 0)
                    perror("Error :");
                break;
            }
        }
        ret[j++] = b[i++];
        if (ret[j - 1] == '\n')
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


int check(char *line, char *arr, int s)
{
    if (!line || !arr)
        return -0;
    int i = 0;
    while(i < s && line[i] == arr[i])
        i++;

    if (i < s)
        return 0;
    return 1;
}


void filter(char *line, char *arr)
{
    int i,j,s;
    s = 0;

    while(arr[s])
        s++;
    
    i = 0;
    while(line[i])
    {
        if (check(line + i, arr, s))
        {
            j = 0;
            while(j < s)
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
    if (ac != 2)
        return 1;
    char *t;

    while(1)
    {
        t = get_next_line(0);
        if (!t)
            break;
        filter(t, av[1]);
        free(t);
    }
    return 0;
}