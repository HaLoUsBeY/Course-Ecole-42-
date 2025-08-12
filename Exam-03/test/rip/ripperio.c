#include <stdio.h>

int is_val (char *str)
{
    int open = 0, close = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close++;
        }
    }
    return open + close;
}


void rip (char *str, int n, int fix, int hala)
{
    if (n == fix && !is_val(str))
    {  
        puts(str);
        return;
    }


    for (int i = hala ; str[i] ; i++)
    {
        if (str[i] == '(' || str[i] == ')')
        {
            int c = str[i];
            str[i] = ' ';
            rip(str, n, fix + 1, i);
            str[i] = c;
        }
    }
}


int main(int ac, char **ag)
{
    (void) ac;
    int m_fix = is_val(ag[1]);
    rip(ag[1], m_fix, 0, 0);
}