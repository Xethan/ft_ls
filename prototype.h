/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 11:17:15 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/04 17:28:51 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include "ft_ls.h"

/*
**      MAIN.C :
*/

void		disp_if_needed(t_arglist *file_list, char *dir_name);
t_arglist	*readdir_and_sort_files(DIR *p_dir, char *dir_name);
void		do_opt_r_caps(t_arglist *file_list, char *dir_name);
int			opendir_and_list(char *dir_name, int disp_name_dir);

/*
**       CHECK_OPTIONS.C :
*/

int			show_or_not_file(char *file_name, char *dir_name);
int			show_or_not_dir(char *dir_name);
void		get_options(char c);
int			check_options(char **arg);

/*
**       HANDLE_LIST.C :
*/

void		lst_str_add(t_arglist **begin_list, t_arglist *new);
void		lst_creat_begin(t_arglist **begin_list, char *arg_name);
void		lst_creat_after(t_arglist *list, char *arg_name);
void		lst_str_del(t_arglist **begin_list);
t_arglist	*lst_str_new(char *arg_name);

/*
**       SORT_ARGS.C :
*/

t_arglist	*sort_args(char **arg);
t_arglist	*create_list_from_argv(char **arg, int i);
t_arglist	*put_arg_into_list(t_arglist **begin_list, char *arg);
int			cmp_args(char *arg1, char *arg2);

/*
**       STAT.C :
*/

int			disp_if_file(char *arg_name);
char		*get_path(char *dir_name, char *file_name);
void		do_opt_l(char *file_name, char *dir_name, t_info nb_spaces);

/*
**       BIS_OPT_L.C :
*/

void		right_number_of_spaces(int nb_spaces, char *info);
void		disp_rights(mode_t rights, int test, char to_disp);
void		disp_all_rights(mode_t rights);
void		disp_type_of_file(mode_t mode);
void		disp_link(char *file_name, char *dir_name);

/*
**       HOW_MANY_SPACES.C :
*/

t_info		init_info_to_zero(t_info p_info);
t_info		how_many_spaces(t_arglist *file_list, char *dir_name, t_info nb_spaces);

#endif