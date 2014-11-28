# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/19 16:01:28 by ncolliau          #+#    #+#              #
#    Updated: 2014/11/28 15:15:01 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC =	main.c track_error.c check_options.c sort_args.c handle_list.c stat.c \
		how_many_spaces.c

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