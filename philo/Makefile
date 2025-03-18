NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =  philo.c init.c msgs.c utils.c time.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re