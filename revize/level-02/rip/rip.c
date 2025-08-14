#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

int check(char *str)
{
    int open = 0, close = 0;
    for (int i = 0; str[i] ; i++)
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

void rip(char *str, int fic, int fix, int index)
{
    if (fic == fix && !check(str))
    {
        puts(str);
        return;
    }
    for(int i = index; str[i] ; i++)
        if (str[i] == '(' || str[i] == ')')
        {
            int c = str[i];
            str[i] = ' ';
            rip (str, fic, fix + 1, i);
            str[i] = c;
        }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    
    int fic = check(av[1]);
    rip(av[1], fic, 0, 0);
    return 0;
}
