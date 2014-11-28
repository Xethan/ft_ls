/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 15:56:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 15:34:14 by ncolliau         ###   ########.fr       */
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
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
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
}						t_arglist;

typedef struct			s_spaces
{
	size_t				links;
	size_t				size;
}						t_spaces;

/*
**       MAIN.C :
*/

void					disp_if_needed \
						(char *file_name, t_options *is_opt, char *dir_name, t_spaces spaces);
int						opendir_and_list \
						(char *dir_name, t_options *is_opt, int disp_name_dir);
void					do_ls(int argc, char **argv, t_options *is_opt);

/*
**       TRACK_ERROR.C :
*/

int						is_option(char c);
int						check_error_options(char *arg);
/*
**       CHECK_OPTIONS.C :
*/

t_options				*init_options_to_zero(t_options *is_opt);
t_options				*get_options(t_options *is_opt, char c);
int						check_options(char **arg, t_options *is_opt);

/*
**       HANDLE_LIST.C :
*/

void					lst_str_add(t_arglist **begin_list, t_arglist *new);
void					lst_creat_begin\
						(t_arglist **begin_list, void *arg_name);
void					lst_creat_after(t_arglist *list, void *arg_name);
void					lst_creat_before(t_arglist *list, void *arg_name);
t_arglist				*lst_str_new(char *arg_name);

/*
**       SORT_ARGS.C :
*/

t_arglist				*reverse_list(t_arglist **begin_list);
t_arglist				*sort_args(char **arg, t_options *is_opt);
t_arglist				*put_arg_into_list(char **arg, int i);

/*
**       STAT.C :
*/

char					*get_path(char *file_name, char *dir_name);
void					disp_rights(mode_t rights, int test, char to_disp);
void					disp_all_rights(mode_t rights);
void					do_opt_l(char *file_name, char *dir_name, t_spaces spaces);

/*
**       HOW_MANY_SPACES.C :
*/

t_spaces				how_many_spaces(t_arglist *file_list, char *dir_name, t_spaces spaces);

#endif
