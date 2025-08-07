# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 14:07:36 by akiiski           #+#    #+#              #
#    Updated: 2024/12/27 13:32:07 by akiiski          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -I .

BONUSSRCS =

SRCS = 	ascii/ft_isalpha.c ascii/ft_isascii.c ascii/ft_isdigit.c \
		ascii/ft_isprint.c ascii/ft_tolower.c ascii/ft_toupper.c \
		ascii/ft_isalnum.c ascii/ft_iswhitespace.c \
		string/ft_strlen.c string/ft_strlcpy.c string/ft_strlcat.c \
		string/ft_strchr.c string/ft_strrchr.c string/ft_strncmp.c \
		string/ft_strnstr.c string/ft_strdup.c string/ft_substr.c \
		string/ft_strjoin.c string/ft_strtrim.c \
		string/ft_split.c string/ft_itoa.c string/ft_strmapi.c \
		string/ft_striteri.c string/ft_atoi.c string/ft_strcmp.c \
		string/ft_multi_split.c \
		memory/ft_memset.c memory/ft_memcmp.c memory/ft_bzero.c \
		memory/ft_memchr.c memory/ft_memcpy.c memory/ft_memmove.c \
		memory/ft_calloc.c memory/free_arr.c \
		print/ft_putchar_fd.c print/ft_putstr_fd.c print/ft_putendl_fd.c \
		print/ft_printf.c print/ft_unbr_fd.c print/ft_pointer.c \
		print/ft_hexnbr.c print/ft_putnbr_fd.c \
		list/ft_lstnew.c list/ft_lstadd_front.c list/ft_lstsize.c \
		list/ft_lstlast.c list/ft_lstadd_back.c list/ft_lstdelone.c \
		list/ft_lstclear.c list/ft_lstiter.c list/ft_lstmap.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

NAME = libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) tests

re:	fclean all

tests: CFLAGS += -g -fsanitize=address -fsanitize=leak -fsanitize=undefined
tests: libfttests.c printftests.c gnltests.c $(NAME)
	cc -o $@ $(CFLAGS) $^ -lbsd
	./$@
