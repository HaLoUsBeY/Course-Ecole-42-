#include "tlist.h"
#include <stdio.h>
#include <stdlib.h>

int main (int ac, char **av)
{
    int i = 0;
    t_stack *a_stac;
    t_stack *temp;

    a_stac = malloc(sizeof(t_stack));
    temp = a_stac;
    while (++i < ac)
    {
        a_stac ->data = atoi(av[i]);
        a_stac ->next = malloc(sizeof(t_stack));
        a_stac = a_stac ->next;
    }
     a_stac->next = NULL; // Son elemanın next'ini NULL yap


    while (temp != NULL)
    {
        printf("%d\n",temp ->data);
        temp = temp -> next;
    }
    while (temp != NULL)
    {
        t_stack *next = temp->next;
        free(temp);
        temp = next;
    }
    while (a_stac != NULL)
    {
        t_stack *next = a_stac->next;
        free(a_stac);
        a_stac = next;
    }


    return (0);

}