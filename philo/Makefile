NAME = philo

CC = gcc

SRC = ft_atoi.c  live.c  main.c time.c

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread -g3

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make

.phony: all clean fclean re norm