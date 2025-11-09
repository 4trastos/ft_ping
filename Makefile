NAME = ft_ping
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -Iincl
RM = rm -f

SRC = src/main.c src/signal_handler.c src/statistics.c src/socket.c src/request.c \
	src/send_reply.c src/parser.c

OBJS = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re $(FT_PRINTF)
