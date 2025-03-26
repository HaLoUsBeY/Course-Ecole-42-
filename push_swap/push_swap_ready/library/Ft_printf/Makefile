NAME = libftprintf.a
SRC = ft_printf.c ft_putnbr.c ft_putchar.c ft_puthexa.c ft_putstr.c ft_putunsigint.c ft_ptr.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	ar -cr $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re