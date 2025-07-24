#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE] = "";
    static int i= 0;
    static int r = 0;
    char *line = NULL;
    //char *tmp = ft_strchar(b, '\n');
    int j = 0;

    if (fd < 0 || BUFFER_SIZE <= 0 || !(line = malloc(10000)))
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

    if(j)
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

#include <fcntl.h>
#include <stdio.h>
int main (void)
{

    int fd = open("abc.txt", O_RDONLY);

    while(1)
    {
        char *t = get_next_line(fd);
        if (!t)
            return 1;
        printf("%s",t);
        getchar();
    }
    return 0;
}