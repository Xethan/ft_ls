/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 15:56:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/01 17:48:30 by ncolliau         ###   ########.fr       */
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

typedef struct			s_arglist
{
	char				*arg_name;
	struct s_arglist	*next;
	struct s_arglist	*previous;
}						t_arglist;

typedef struct			s_info
{
	size_t				nlink;
	size_t				size;
	size_t				uid;
	size_t				gid;
}						t_info;

/*
**       MAIN.C :
*/

void					disp_if_needed \
						(char *file_name, char *dir_name, t_info nb_spaces);
int						opendir_and_list \
						(char *dir_name, int disp_name_dir);
void					ft_ls(int argc, char **argv);

/*
**       TRACK_ERROR.C :
*/

int						is_option(char c);
int						check_error_options(char *arg);
/*
**       CHECK_OPTIONS.C :
*/

void					get_options(char c);
int						check_options(char **arg);

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
**       HANDLE_LIST_2.C :
*/

t_arglist				*reverse_list(t_arglist **begin_list);
t_arglist				*lstjoin(t_arglist *lst1, t_arglist *lst2);

/*
**       SORT_ARGS.C :
*/

t_arglist				*sort_args(char **arg);
t_arglist				*create_list_from_argv(char **arg, int i);
t_arglist				*put_arg_into_list(t_arglist **begin_list, char *arg);

/*
**       STAT.C :
*/

int						disp_if_file(char *arg_name);
char					*get_path(char *file_name, char *dir_name);
void					disp_rights(mode_t rights, int test, char to_disp);
void					disp_all_rights(mode_t rights);
void					do_opt_l(char *file_name, char *dir_name, t_info nb_spaces);

/*
**       HOW_MANY_SPACES.C :
*/

t_info					init_info_to_zero(t_info p_info);
t_info					how_many_spaces(t_arglist *file_list, char *dir_name, t_info nb_spaces);

#endif
