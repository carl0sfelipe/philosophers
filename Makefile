NAME =		philo

SRCS =		main.c think.c eat.c sleep.c utils.c init.c simulation.c ft_atoi.c \
			has_only_int.c is_out_of_bounds.c

CFLAGS =	-Wall -Wextra -Werror

CC =		cc

$(NAME): $(SRCS) philo.h
	$(CC) $(CFLAGS) $(SRCS) -pthread -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(SRCS:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
