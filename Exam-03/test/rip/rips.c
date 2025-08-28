#include <stdio.h>


int tas(char *str)
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


void rip (char *str, int fic, int fix, int index)
{
    if (fic == fix && !tas(str))
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
            rip(str, fic, fix+1, i)
            
        }
    }

}

int main(int ac, char **ag)
{
    (void) ac;
    int m_fix = is_val(ag[1]);
    rip(ag[1], m_fix, 0, 0);
}