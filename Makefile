# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/19 16:01:28 by ncolliau          #+#    #+#              #
#    Updated: 2014/12/02 17:05:50 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC =	main.c check_options.c sort_args.c handle_list.c stat.c \
		how_many_spaces.c handle_list_2.c bis_opt_l.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
			make -C libft/ re
			make -C libft/ clean
			gcc -Wall -Wextra -Werror -o $(NAME) \
			-I ./ -I ./libft/includes $(SRC) libft/libft.a

clean :
			rm -f $(OBJ)

fclean : clean
			rm -f $(NAME)

re : fclean all

norme :
			norminette $(SRC) ft_ls.h