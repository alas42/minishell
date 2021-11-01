# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yassharm <yassharm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/31 15:44:59 by avogt             #+#    #+#              #
#    Updated: 2021/11/01 03:35:50 by yassharm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

NAME = minishell
FILES = minishell.c \
	error.c

BUILTINS_FILES = mini_env.c \
	mini_cd.c \
	mini_echo.c \
	mini_exit.c \
	mini_export.c \
	mini_pwd.c \
	mini_unset.c \
	solo_builtin.c \
	utils_export.c

EXEC_FILES = exec_cmds.c \
	child_fds.c \
	parent_fds.c

PARSING_FILES = parsing_init.c \
	parsing.c \
	lexer.c \
	libft_utils.c \
	parsing_utils.c \
	quotes_handler.c \
	quotes_utils.c \
	dollar_parser.c \
	dollar_handler.c \
	dollar_helper.c \
	dollar_expander.c \
	files_parser.c \
	commands_init.c \
	token_to_cmd.c \
	token_to_cmd_utils.c \
	redirections.c \
	redirections_utils.c \
	here_doc.c \
	here_doc_utils.c

UTILS_FILES = utils_cmds.c \
	utils_env.c \
	utils_paths.c \
	utils_env_getters.c \
	utils_infos.c \
	utils_builtins.c \
	free.c \
	free_commands.c \
	utils_error.c \
	utils_files.c

SIGNALS_FILES = sigint.c \
	sigquit.c \
	signals.c

PARSING_FOLDER = parsing
UTILS_FOLDER = utils
BUILTINS_FOLDER = builtins
EXEC_FOLDER = exec
FOLDER_SOURCES = srcs
SIGNALS_SOURCES = signals

SOURCES_FILES = $(addprefix $(FOLDER_SOURCES)/,$(FILES)) \
	$(addprefix $(FOLDER_SOURCES)/,$(addprefix $(BUILTINS_FOLDER)/,$(BUILTINS_FILES))) \
	$(addprefix $(FOLDER_SOURCES)/, $(addprefix $(EXEC_FOLDER)/, $(EXEC_FILES))) \
	$(addprefix $(FOLDER_SOURCES)/, $(addprefix $(UTILS_FOLDER)/, $(UTILS_FILES))) \
	$(addprefix $(FOLDER_SOURCES)/, $(addprefix $(PARSING_FOLDER)/, $(PARSING_FILES))) \
	$(addprefix $(FOLDER_SOURCES)/, $(addprefix $(SIGNALS_SOURCES)/, $(SIGNALS_FILES)))

OBJS = $(SOURCES_FILES:.c=.o)

IFLAGS = -I ./includes
LIBFT = libft

CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME)
	@printf "Makefile starts\n"

$(NAME): $(OBJS)
	@touch heredoc
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
	@rm -f heredoc

re: fclean all

.PHONY: all clean fclean re
