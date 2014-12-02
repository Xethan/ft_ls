/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 11:17:15 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/02 17:10:06 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

# include "ft_ls.h"

/*
**      MAIN.C :
*/

void		disp_if_needed(char *file_name, char *dir_name, t_info nb_spaces);
t_arglist	*readdir_and_sort_files(DIR *p_dir);
int			opendir_and_list(char *dir_name, int disp_name_dir);
void		ft_ls(int argc, char **argv);

/*
**       CHECK_OPTIONS.C :
*/

void		get_options(char c);
int			check_options(char **arg);

/*
**       HANDLE_LIST.C :
*/

void		lst_str_add(t_arglist **begin_list, t_arglist *new);
void		lst_creat_begin(t_arglist **begin_list, char *arg_name);
void		lst_creat_after(t_arglist *list, char *arg_name);
t_arglist	*lst_str_new(char *arg_name);

/*
**       HANDLE_LIST_2.C :
*/

t_arglist	*reverse_list(t_arglist **begin_list);
t_arglist	*lstjoin(t_arglist *lst1, t_arglist *lst2);

/*
**       SORT_ARGS.C :
*/

t_arglist	*sort_args(char **arg);
t_arglist	*reverse_and_join(t_arglist *error, t_arglist *file, t_arglist *dir);
t_arglist	*create_list_from_argv(char **arg, int i);
t_arglist	*put_arg_into_list(t_arglist **begin_list, char *arg);

/*
**       STAT.C :
*/

int			disp_if_file(char *arg_name);
char		*get_path(char *file_name, char *dir_name);
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