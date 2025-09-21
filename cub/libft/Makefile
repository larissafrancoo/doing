# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfranco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 11:53:58 by lfranco           #+#    #+#              #
#    Updated: 2023/11/11 12:35:06 by lfranco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

SRCS = 	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isalpha.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putnbr_fd.c\
	ft_putendl_fd.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_toupper.c\
	ft_tolower.c\

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I . -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs libft.a $(OBJS)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
#	gcc -nostartfiles -shared -o libft.so $(OBJS)
.PHONY : all clean fclean re
