NAME = philo

SRCS = philo.c \
       utilities.c \
       ft_check.c \
       ft_philo_init.c \
       monitor.c \
       ft_run.c \
       ft_run_utils.c


OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
