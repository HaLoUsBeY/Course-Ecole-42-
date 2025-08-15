#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i= 0;
    while (str[i])
        i++;

    return i;
}

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void sort(char *str)
{
    for (int i = 0; str[i]; i++)
        for (int j = 0; str[j]; j++)
            if (str[i] < str[j])
                swap(&str[i], &str[j]);
}

void permute(char *str, int start)
{
    if (!str[start])
    {
        write(1,str,ft_strlen(str));
        write(1, "\n",1);
        return;
    }
    for (int c = 0; c <= 127; c++) {
        for (int i = start; str[i]; i++) {
            if (str[i] == c) {
                swap(&str[start], &str[i]);
                permute(str, start + 1);
                swap(&str[start], &str[i]);
            }
        }
    }
}

int main (int ac, char **av)
{
    if (ac != 2)
        return 1;
    sort(av[1]);
    permute(av[1], 0);
    return 0;
}