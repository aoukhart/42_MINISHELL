# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 00:38:49 by aoukhart          #+#    #+#              #
#    Updated: 2021/12/01 03:36:02 by aoukhart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_isalpha.c ft_memset.c ft_strlcpy.c ft_strrchr.c \
ft_atoi.c ft_isascii.c ft_memchr.c ft_strchr.c ft_strlen.c \
ft_bzero.c ft_isdigit.c	ft_memcmp.c	ft_strdup.c	ft_substr.c \
ft_calloc.c	ft_isprint.c ft_memcpy.c ft_strjoin.c ft_strncmp.c ft_tolower.c \
ft_isalnum.c ft_memmove.c ft_strlcat.c ft_strnstr.c ft_toupper.c \
ft_strtrim.c ft_strmapi.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_split.c \

OBJECT = $(SRC:.c=.o)

NAME = libft.a

all : $(NAME)

$(NAME) :
	@gcc -Wall -Wextra -Werror -c $(SRC)
	@ar rc $(NAME) $(OBJECT)

clean :
	@rm -rf $(OBJECT)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
