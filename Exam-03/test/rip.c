#include <stdio.h>

int dam(char *str)
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





void rip(char *str, int fic, int fix , int index)
{
    if (fic = fix && !dam(str))
    {
        puts(str);
        return;
    }

    for (int i = index; str[i]; i++)
    {
        if (str[i] == '(' || str[i] == ')')
        {
            int c = str[i];
            str[i] = ' ';
            rip(str,fic , fix +1, i);
            str[i] = c;
        }
    }
}