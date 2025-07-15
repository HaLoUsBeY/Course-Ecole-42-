#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>  
#include <string.h>

char *ft_strchar(char *s, char c)
{
    int i = 0;
    while(s[i] && s[i] != c)
        i++;
    if (s[i] == c)
        return (s + i);
    else
        return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((const char *)src)[i];
        i++;
    }
    return dest;
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = *s1 ? ft_strlen(*s1) : 0;
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;
    if (*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
    return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    if (dest > src)
        return ft_memcpy(dest, src, n);
    else if (dest == src)
        return dest;
    size_t i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((const char *)src)[i];
        i++;
    }
    return dest;
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp = ft_strchar(b, '\n');

    while (!tmp)
    {
        if (!str_append_str(&ret, b))
            return NULL;
        int read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret == -1)
        {
            free(ret);
            return NULL;
        }
        if (read_ret == 0)
        {
            if (ret && ft_strlen(ret) > 0)
            {
                b[0] = '\0';
                return ret;
            }
            free(ret);
            return NULL;
        }
        b[read_ret] = '\0';
        tmp = ft_strchar(b, '\n');
    }
    if (!(str_append_mem(&ret, b, tmp - b + 1)))
    {
        free(ret);
        return NULL;
    }
    ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
    return ret;
}


int main (void)
{
    int fd = open("abc.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
        printf("Press Enter to continue...\n");
        while (getchar() != '\n');
    }

    close(fd);
    return 0;
}
