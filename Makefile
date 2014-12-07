# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/19 16:01:28 by ncolliau          #+#    #+#              #
#    Updated: 2014/12/06 13:28:29 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_ls

SRC =	main.c check_options.c sort_args.c handle_dir_list.c stat.c \
		how_many_spaces.c bis_opt_l.c handle_file_list.c

OBJ = $(SRC:.c=.o)

PATH_INCLUDES = ./libft/includes

FLAGS = -Wall -Wextra -Werror

.PHONY: make, all, make_libft, clean, fclean, re, norme

.SUFFIXES:

all : make_libft $(NAME)

$(NAME) : $(SRC)
			gcc $(FLAGS) -I $(PATH_INCLUDES) -c $(SRC)
			gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a

make_libft :
			make -C libft/
			make -C libft/ clean

clean :
			@rm -f $(OBJ)
			@echo "clean done"

fclean : clean
			rm -f $(NAME)

re : fclean all

norme :
			norminette $(SRC) ft_ls.h