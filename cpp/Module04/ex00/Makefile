SRCS = main.cpp Animal.cpp Dog.cpp Cat.cpp

NAME = polymorphism
CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
OBJS = $(SRCS:.cpp=.o)
RM = rm -rf

W_SRCS = WrongMain.cpp WrongAnimal.cpp WrongCat.cpp
W_OBJS = $(W_SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

wrong: fclean $(W_OBJS)
	$(CPP) $(FLAGS) -o $(NAME) $(W_OBJS)

wclean:
	$(RM) $(W_OBJS) $(NAME)

re : fclean all

.PHONY : all clean fclean re