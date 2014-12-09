/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 11:17:15 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/09 14:50:51 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

/*
**      MAIN.C :
*/

void		disp_filelist(t_filelist *f_list, t_info nb_spaces);
t_filelist	*readdir_and_sort_files(DIR *p_dir, char *dir_name);
void		do_opt_r_caps(t_filelist *f_list);
int			opendir_and_list(char *dir_name, int disp_name_dir);

/*
**       CHECK_OPTIONS.C :
*/

void		*malloc_me(size_t size);
int			show_or_not_file(char *file_name, char *dir_name);
int			show_or_not_dir(char *dir_name);
void		get_options(char c);
int			check_options(char **arg);

/*
**       HANDLE_LIST_DIR.C :
*/

void		d_lstadd(t_dirlist **begin_list, t_dirlist *new);
void		d_lst_creat_begin(t_dirlist **begin_list, char *arg_name);
void		d_lst_creat_after(t_dirlist *list, char *arg_name);
void		d_lstdel(t_dirlist **begin_list);
t_dirlist	*d_lstnew(char *arg_name);

/*
**       SORT_ARGS.C :
*/

t_dirlist	*sort_args(char **arg);
t_dirlist	*create_list_from_argv(char **arg, int i);
t_dirlist	*put_arg_into_list(t_dirlist **begin_list, char *arg);
int			cmp_args(char *arg1, char *arg2);

/*
**       STAT.C :
*/

char		*get_path(char *dir_name, char *file_name);
void		do_opt_l(t_filelist *file, t_info nb_spaces);

/*
**       BIS_OPT_L.C :
*/

void		put_spaces(int nb_spaces, char *info);
void		disp_rights(mode_t rights, int test, char to_disp);
void		disp_all_rights(mode_t rights);
void		disp_type_of_file(mode_t mode);
void		disp_link(t_filelist *f_list);

/*
**       HOW_MANY_SPACES.C :
*/

t_info		init_info_to_zero(t_info p_info);
t_info		how_many_spaces(t_filelist *filelist, t_info length);


void		f_lstadd(t_filelist **begin_list, t_filelist *new);
t_filelist	*f_lstnew(char *name, char *dir_name);
void		f_lstdel(t_filelist **begin_list);

#endif