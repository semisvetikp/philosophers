HEADER = philo_two.h
SRCS	=  main.c utils.c philo_two.c

GCC		= gcc
FLAGS	= -Wall -Wextra -Werror

OBJ = $(SRCS:.c=.o)

NAME = philo_two

RM   =  rm -f

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) 
		$(GCC) $(FLAGS) $(OBJ) -o $(NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re