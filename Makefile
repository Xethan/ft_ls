# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/19 16:01:28 by ncolliau          #+#    #+#              #
#    Updated: 2014/11/19 16:09:17 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c track_error.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
			gcc -Wall -Wextra -Werror -o $(NAME) -I ./ -I ./libft/includes $(SRC) libft/libft.a

clean :
			rm -f $(OBJ)

fclean : clean
			rm -f $(NAME)

re : fclean all

norme : norminette $(SRC) ft_ls.h