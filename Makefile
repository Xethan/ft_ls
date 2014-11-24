# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/19 16:01:28 by ncolliau          #+#    #+#              #
#    Updated: 2014/11/24 12:32:54 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c track_error.c check_options.c bis.c handle_list.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
			gcc -Wall -Wextra -Werror -o $(NAME) \
			-I ./ -I ./libft/includes $(SRC) libft/libft.a

clean :
			rm -f $(OBJ)

fclean : clean
			rm -f $(NAME)

re : fclean all

norme :
			norminette $(SRC) ft_ls.h