# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/07 15:24:29 by ncolliau          #+#    #+#              #
#    Updated: 2014/12/16 14:51:57 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c ft_lstadd.c \
		ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
		ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
		ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
		ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
		ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c	\
		ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
		ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
		ft_toupper.c ft_putlonglong.c ft_nbrlen.c

OBJ =	$(SRC:.c=.o)

PATH_INCLUDE = ./includes

FLAGS = -Wall -Wextra -Werror

.PHONY: make, all, $(NAME), clean, fclean, re, norme

all : $(NAME)

$(NAME) : $(SRC)
		@gcc $(FLAGS) -I $(PATH_INCLUDE) -c $(SRC)
		@ar rc $(NAME) $(OBJ)
		@echo "libft compiled"
		ranlib $(NAME)

clean :
		@rm -f $(OBJ)
		@echo "clean done"

fclean : clean
		rm -f $(NAME)

re : fclean all

norme :
		norminette $(SRC) includes/libft.h
