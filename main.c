/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/08 13:17:16 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		g_opt_r_caps = 0;
int		g_opt_a = 0;
int		g_opt_l = 0;
int		g_opt_r = 0;
int		g_opt_t = 0;

void		disp_if_needed(t_filelist *f_list)
{
	t_info nb_spaces;

	nb_spaces = init_info_to_zero(nb_spaces);
	nb_spaces = how_many_spaces(f_list, nb_spaces);
	while (f_list)
	{
		if (show_or_not_file(f_list->name, f_list->dir_name) == 1)
		{
			if (g_opt_l == 1)
				do_opt_l(f_list, nb_spaces);
			else
				ft_putendl(f_list->name);
		}
		f_list = f_list->next;
	}
}

t_filelist	*readdir_and_sort_files(DIR *p_dir, char *dir_name)
{
	t_dirent	*s_dir;
	t_filelist	**begin_list;
	t_filelist	*list;
	char		*path1;
	char		*path2;

	begin_list = (t_filelist **)malloc_me(sizeof(t_filelist *));
	if ((s_dir = readdir(p_dir)) != NULL)
		*begin_list = f_lstnew(s_dir->d_name, dir_name);
	while ((s_dir = readdir(p_dir)) != NULL)
	{
		list = *begin_list;
		path1 = get_path(dir_name, s_dir->d_name);
		path2 = get_path(dir_name, list->name);
		if (cmp_args(path1, path2) < 0)
			f_lst_creat_begin(begin_list, s_dir->d_name, dir_name);
		else
		{
			if (list->next)
			{
				free(path2);
				path2 = get_path(dir_name, list->next->name);
			}
			while (list->next && cmp_args(path1, path2) > 0)
				list = list->next;
			f_lst_creat_after(list, s_dir->d_name, dir_name);
		}
		free(path1);
		free(path2);
	}
	list = *begin_list;
	return (list);
}

void		do_opt_r_caps(t_filelist *f_list)
{
	while (f_list)
	{
		if (S_ISDIR(f_list->st->st_mode) != 0
			&& ft_strequ(f_list->name, ".") == 0
			&& ft_strequ(f_list->name, "..") == 0)
		{
			if (show_or_not_dir(f_list->path) == 1)
				ft_putchar('\n');
			opendir_and_list(f_list->path, NAME);
		}
		f_list = f_list->next;
	}
}

int			opendir_and_list(char *dir_name, int disp_name)
{
	DIR			*p_dir;
	t_filelist	*f_list;

	if ((p_dir = opendir(dir_name)) == NULL)
	{
		if (disp_name == NAME)
		{
			ft_putstr_fd(dir_name, 2);
			ft_putstr_fd(":\n", 2);
		}
		ft_putstr_fd("ft_ls: ", 2);
		if (strrchr(dir_name, '/'))
			perror(strrchr(dir_name, '/') + 1);
		else
			perror(dir_name);
		return (0);
	}
	if (disp_name == NAME)
	{
		if (show_or_not_dir(dir_name) == 1)
		{
			ft_putstr(dir_name);
			ft_putstr(":\n");
		}
	}
	f_list = (t_filelist *)malloc_me(sizeof(t_filelist));
	f_list = readdir_and_sort_files(p_dir, dir_name);
	disp_if_needed(f_list);
	if (g_opt_r_caps == 1)
		do_opt_r_caps(f_list);
	closedir(p_dir);
	f_lstdel(&f_list);
	return (1);
}

int			main(int argc, char **argv)
{
	int			i;
	t_dirlist	*list;

	i = 1;
	if (argc > 1)
		i = check_options(argv);
	list = sort_args(argv);
	if (argc == i)
		opendir_and_list(".", NO_NAME);
	else if (argc == i + 1 && list)
			opendir_and_list(list->name, NO_NAME);
	else if (argc > i + 1)
	{
		while (list)
		{
			opendir_and_list(list->name, NAME);
			if ((list = list->next))
				ft_putchar('\n');
		}
	}
	d_lstdel(&list);
	return (0);
}
