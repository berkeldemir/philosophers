NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
THREADFLAGS = -lpthread
SRCS = philo_bonus.c utils_bonus.c action_bonus.c threads_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(THREADFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re