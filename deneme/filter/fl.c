#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER
# define BUFFER 42
#endif


char *gnl(int fd)
{
    static char b[BUFFER];
    static int i = 0, r = 0 ;
    char *line;
    int j = 0;

    if (fd < 0 || BUFFER <= 0 || !(line = malloc(100000)))
        return NULL;

    while (1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER);
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

int ft_check(char *line, char *av, int s)
{
    if (!line || !av)
        return -1;
    int i = 0;
    while (i < s && (line[i] == av[i]))
        i++;
    
    if (i < s)
        return -1;
    return 1;
}

void ft_printf(char *line, char *av)
{
    int i,j,s;
    s = 0;
    while (av[s])
        s++;
    i = 0;
    while (line[i])
    {
        if (ft_check(line + i, av, s) == 1)
        {
            j = 0;
            while ( j < s)
            {
                line[i + j] = '*';
                j++;
            }
        }
        write(1,&line[i],1);
        i++;
    }
    return;

}


// #include <fcntl.h>
#include <stdio.h>

int main (int ac, char **av)
{
    char *line;

    if (ac != 2)
        return 1;

    // int fd = open("a.txt", O_RDONLY);
    while (1)
    {
        line = gnl(0);
        if (!line)
            break;
        // printf("%s",line);
        ft_printf(line, av[1]);
        getchar();
    }
    return 0;
}