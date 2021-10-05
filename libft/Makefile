# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avogt <avogt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 13:56:55 by avogt             #+#    #+#              #
#    Updated: 2021/10/05 13:57:14 by avogt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_putchar.c \
	ft_putstr.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_atof.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isspace.c \
	ft_lst.c \
	ft_memset.c \
	ft_putstr_fd.c \
	ft_split_char.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strsub.c \
	ft_strlen.c \
	get_next_line.c \
	ft_strcat.c

OBJS = $(FILES:.c=.o)
FLAGS = -Wall -Werror -Wextra
IFLAGS = -I ../includes
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
