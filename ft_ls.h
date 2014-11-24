/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 15:56:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/24 12:32:53 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

# define NAME 1
# define NO_NAME 0

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_options
{
	int					l;
	int					r_caps;
	int					r;
	int					a;
	int					t;
}						t_options;

typedef struct			s_arglist
{
	char				*arg_name;
	struct s_arglist	*next;
	struct s_arglist	*previous;
}						t_arg_name;

/*
**       MAIN.C :
*/

void					disp_if_needed(t_dirent *sdir, t_options *is_opt);
int						opendir_and_list (char *dir_name, t_options *is_opt, int disp_name_dir);
void					do_ls(int argc, char **argv, t_options *is_opt);

/*
**       TRACK_ERROR.C :
*/

int						is_option(char c);
int						check_error_options(char *arg);
/*
**       CHECK_OPTIONS.C :
*/

t_options				*init_options_to_zero(t_options *is_option);
t_options				*get_options(t_options *is_option, char c);
int						check_options(char **arg, t_options *is_option);

/*
**       HANDLE_LIST.C :
*/

void					lst_str_add(t_arg_name **begin_list, t_arg_name *new);
void					lst_creat_begin(t_arg_name **begin_list, void *arg_name);
void					lst_creat_after(t_arg_name *list, void *arg_name);
void					lst_creat_before(t_arg_name *list, void *arg_name);
t_arg_name				*lst_str_new(char *arg_name);

/*
**       BIS.C :
*/

t_arg_name				*move_end_lst(t_arg_name *list);
t_arg_name				*sort_files(char **arg, t_options *is_opt);
t_arg_name				*put_arg_into_list(char **arg, int i);

#endif
