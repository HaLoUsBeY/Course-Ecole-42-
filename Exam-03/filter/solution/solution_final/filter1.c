#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 42

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE] = "";
    static int i = 0;
    static int r = 0;
    char *line = NULL;
    int j = 0;

    if (fd < 0 || BUFFER_SIZE <= 0 || !(line = malloc(10000)))
        return NULL;

    while(1)
    {
        if (i >= r)
        {
            i = 0;
            r = read(fd, b, BUFFER_SIZE);
            if (r <= 0)
            {
                break;
            }
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

int ft_check(char *t, char *ar, int s)
{
    int i;

    if (!t || !ar)
        return -1;
    i = 0;
    while (i < s && t[i] == ar[i])
        i++;

    if (i < s)
        return -1;
    return 1;
}

void ft_printf(char *t, char *ar)
{
    int i,j,s;
    s = 0;
    while (ar[s])
        s++;
    
    i= 0;
    while (t[i])
    {
        if(ft_check(t + i, ar, s) == 1)
        {
            j = 0;
            while (ar[j])
            {
                write(1, &ar[j], 1);
                j++;
            }
            i += s;
        }
        else
        {
            write(1, &t[i], 1);
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    char *line;
    
    if (ac != 2)
        return 1;
    
    while(1)
    {
        t = get_next_line(0);
        if (!t)
            break;
        ft_printf(t, argv[1]);
        free(t);
    }
    return 0;
}