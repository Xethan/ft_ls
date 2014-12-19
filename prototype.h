/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 11:17:15 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 10:49:08 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

/*
**      MAIN.C :
*/

t_info	into_list(t_flist **b_list, DIR *p_dir, char *dir_name, t_info spaces);
t_flist	*readdir_and_sort_files(DIR *p_dir, char *dir_name);
void	do_recursivity(t_flist *f_list);
void	opendir_and_list(char *dir_name, int disp_name_dir);

/*
**       CHECK_OPTIONS.C :
*/

int		verif_dir(char *dir_name);
int		show_or_not_files(t_flist **begin_list);
int		show_or_not_dir(char *dir_name);
void	get_options(char c);
int		check_options(char **arg);

/*
**       HANDLE_DIR_LIST.C :
*/

void	d_lstadd(t_dlist **begin_list, t_dlist *new);
void	d_lst_creat_begin(t_dlist **begin_list, char *arg_name);
void	d_lst_creat_after(t_dlist *list, char *arg_name);
void	d_lstdel(t_dlist **begin_list);
t_dlist	*d_lstnew(char *arg_name);

/*
**       HANDLE_FILE_LIST.C :
*/

void	disp_lists (t_dlist *error_list, \
		t_dlist *dir_list, t_flist *file_list, t_info nb_spaces);
void	f_lstadd(t_flist **begin_list, t_flist *new);
t_flist	*f_lstnew(char *name, char *dir_name);
void	f_lstdel(t_flist **begin_list);

/*
**       SORT_ARGS.C :
*/

t_dlist	*arg_into_list
		(t_dlist **b_list, char *arg, int (*comp)(const char *, const char *));
t_info	file_into_list(t_flist **begin_list, char *name, t_info spaces);
t_dlist	*create_list_from_argv(char **arg, int i);

/*
**       STAT.C :
*/

void	disp_rights(mode_t rights, int test, char to_disp);
void	disp_all_rights(mode_t rights);
void	do_opt_l(t_flist *f_list, t_info nb_spaces);

/*
**       BIS_STAT.C :
*/

void	disp_type_of_file(mode_t mode);
void	disp_uid_gid(t_flist *file, t_info nb_spaces);
void	disp_maj_min_size(t_flist *file, t_info nb_spaces);
void	disp_date_name_link(t_flist *file, t_info nb_spaces);

/*
**       HOW_MANY_SPACES.C :
*/

void	put_spaces(size_t nb_spaces, size_t length);
t_info	init_info_to_zero(t_info p_info);
int		count_spaces(long long info, size_t maxlength);
t_info	how_many_spaces(t_flist *filelist, t_info length);

/*
**       UTILITY.C :
*/

char	*xreadlink(char *path, size_t bufsize);
void	*malloc_me(size_t size);
int		cmp_args(const char *arg1, const char *arg2);
void	disp_filelist(t_flist *f_list, t_info nb_spaces);
char	*get_path(char *dir_name, char *file_name);

#endif