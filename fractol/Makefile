NAME = fractol

SRCS = main.c ft_run.c ft_init.c ft_fonct.c ft_button.c
OBJS = $(SRCS:.c=.o)

MINI = minilibx-linux/libmlx.a
LIBFT_DIR = library/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

# LIBFT'i bağımlılığa ekliyoruz
$(NAME): $(OBJS) $(LIBFT) $(MINI)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINI) -L/usr/lib -lGL -lXext -lX11 -lm -lbsd -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MINI):
	@make -C minilibx-linux

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C minilibx-linux

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C minilibx-linux

re: fclean all

.PHONY: all clean fclean re

