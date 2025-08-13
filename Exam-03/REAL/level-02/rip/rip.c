#include <unistd.h>
#include <stdio.h>

int fak(char *str)
{
    int open = 0, close = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
        {
            if (open)
                open--;
            else
                close++;
        }
    }
    return open + close;
}

void solv(char *str, int fic, int fix, int index)
{
    if (!fak(str) && fic == fix)
    {
        puts(str);
        return;
    }
    for (int i = index ; str[i]; i++)
    {
        if (str[i] == '(' || str[i] == ')')
        {
            int c = str[i];
            str[i] = ' ';
            solv(str, fic , fix +1, i);
            str[i] = c;
        }
    }
}

int main (int ac, char **av)
{
    if (ac != 2)
        return 1;
    int fic = fak(av[1]);
    solv(av[1],fic, 0, 0);
    return 0;
}