#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int	stack_size(t_stack *stack)
{
	int	counter;

	counter = 0;
	while (stack != NULL)
	{
		counter++;
		stack = stack->next;
	}
	return (counter);
}
t_stack	*create_node(int value)
{
	t_stack	*node;

	node = (t_stack *)malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->data = value;
	node->next = NULL;
	return (node);
}


int main (int ac, char **av)
{
    t_stack *a;
    t_stack *temp;
    int i = 2;

    if (ac > 2)
        a = create_node(atoi(av[1]));
    if (!a)
        return 1;
    temp = a;
    while (i < ac)
    {
        a->next = create_node(atoi(av[i]));
        if (!a ->next)
            return 1;
        a = a -> next;
        i++;
    }
    printf("%d",stack_size(temp));
    return (0);
}