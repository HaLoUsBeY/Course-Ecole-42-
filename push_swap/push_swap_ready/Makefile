NAME = push_swap

SRCS = push_swap.c utils/ft_error.c utils/space_utility.c utils/ft_arg.c \
		utils/extra_utility.c utils/ft_free.c sort/sort.c sort/runnersort_3_4_5.c \
		sort/sort_fonct_utils.c sort/quick_sort.c rules/push_stack.c rules/reverse_rot_stack.c \
		rules/rotate_stack.c rules/swap_stack.c

OBJS = $(SRCS:.c=.o)
LIBFT = library/libft/libft.a
FT_PRINTF = library/Ft_printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT) 
	@$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF) $(LIBFT) -o $(NAME)

$(LIBFT) $(FT_PRINTF):  
	@make -s -C library/libft
	@make -s -C library/Ft_printf

clean:
	@rm -f $(OBJS)
	@make clean -s -C library/libft
	@make clean -s -C library/Ft_printf

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C library/libft
	@make fclean -s -C library/Ft_printf

re: fclean all

.PHONY: all clean fclean re
