NAME		= intern

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS		= main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp \
			  RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp
HDRS		= Bureaucrat.hpp AForm.hpp ShrubberyCreationForm.hpp \
			  RobotomyRequestForm.hpp PresidentialPardonForm.hpp Intern.hpp
OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
