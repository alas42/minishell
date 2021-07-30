NAME = minishell
FILES = minishell.c \
	free.c

LIBFT = libft
FOLDER_SOURCES = srcs
SOURCES_FILES = $(addprefix $(FOLDER_SOURCES)/,$(FILES))
OBJS = $(SOURCES_FILES:.c=.o)

IFLAGS = -I ./includes
CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C $(LIBFT)
	@$(CC) $(SOURCES_FILES) -o $(NAME) -lreadline -L ./libft -lft

%.o: %.c
	@$(CC) $(IFLAGS) -o $@ -c $<

clean:
	@make -s -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	@make -s -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
