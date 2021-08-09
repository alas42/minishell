NAME = minishell

FILES = minishell.c \
	free.c \
	paths.c \
	parsing.c \
	lexer.c \
	parsing_init.c \
	parsing_utils.c \
	print_temp.c \
	utils_cmds.c \
	utils_env.c \
	utils_list_env.c

BUILTINS_FILES = mini_env.c \
	mini_cd.c \
	mini_echo.c \
	mini_exit.c \
	mini_export.c \
	mini_pwd.c \
	mini_unset.c

EXEC_FILES = exec_cmds.c \
	child_fds.c \
	parent_fds.c

BUILTINS_FOLDER = builtins
EXEC_FOLDER = exec
FOLDER_SOURCES = srcs

SOURCES_FILES = $(addprefix $(FOLDER_SOURCES)/,$(FILES)) \
	$(addprefix $(FOLDER_SOURCES)/,$(addprefix $(BUILTINS_FOLDER)/,$(BUILTINS_FILES))) \
	$(addprefix $(FOLDER_SOURCES)/, $(addprefix $(EXEC_FOLDER)/, $(EXEC_FILES)))

OBJS = $(SOURCES_FILES:.c=.o)

IFLAGS = -I ./includes
LIBFT = libft

CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME)
	@printf "Makefile starts\n"
$(NAME): $(OBJS)
	@make -s -C $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $(SOURCES_FILES) -lreadline -lncurses -L ./libft -lft -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	@make -s -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	@make -s -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re
