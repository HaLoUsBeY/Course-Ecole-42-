#include "../../minishell.h"

static int	is_numeric(const char *str)
{
    int i = 0;

    if (!str || !str[0])
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int	builtin_exit(char **args)
{
    int	exit_code = 0;

    ft_putstr_fd("exit\n", 2);
    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            ms_error(ERR_NO_CMD, "exit: numeric argument required", 255);
            exit(255);
        }
        if (args[2])
        {
            ms_error(ERR_NO_CMD, "exit: too many arguments", 1);
            return (1);
        }
        exit_code = ft_atoi(args[1]);
    }
    exit(exit_code);
}
