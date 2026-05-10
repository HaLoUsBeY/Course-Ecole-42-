NAME        = fixed
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
SRCS        = main.cpp Fixed.cpp
OBJS        = $(SRCS:.cpp=.o)
RM          = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re