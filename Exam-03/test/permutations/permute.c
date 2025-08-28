#include <unistd.h>

int ft_strlen(char *str){int i = 0; while (str[i]) i++; return i;}


void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}


void sort(char *str)
{
    for (int i = 0; str[i] ; i++)
        for (int j = i + 1 ; str[j]; j++)
            if (str[i] > str[j])
                swap(&str[i], &str[j]);
}

void permute(char *str, int start)
{
    if (!str[start])
    {
        write(1,str,ft_strlen(str));
        write(1,"\n",1);
        return;
    }

    for (int i = start ; str[i]; i++)
    {
        swap(&str[i], &str[start]);
        permute(str, start + 1);
        swap(&str[i], &str[start]);

    }
}


int main (int ac, char **av)
{
    (void) ac;

    permute(av[1], 0);
    return 0;
}