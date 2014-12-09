/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/09 17:09:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

int		g_opt_r_caps = 0;
int		g_opt_a = 0;
int		g_opt_l = 0;
int		g_opt_r = 0;
int		g_opt_t = 0;

void		disp_filelist(t_filelist *f_list, t_info nb_spaces)
{
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
	t_filelist	*new;
	t_info		nb_spaces;

	begin_list = (t_filelist **)malloc_me(sizeof(t_filelist *));
	nb_spaces = init_info_to_zero(nb_spaces);
	if ((s_dir = readdir(p_dir)) != NULL)
	{
		*begin_list = f_lstnew(s_dir->d_name, dir_name);
		nb_spaces = how_many_spaces(*begin_list, nb_spaces);
	}
	while ((s_dir = readdir(p_dir)) != NULL)
	{
		list = *begin_list;
		new = f_lstnew(s_dir->d_name, dir_name);
		if (cmp_args(new->path, list->path) < 0)
			f_lstadd(begin_list, new);
		else
		{
			while (list->next && cmp_args(new->path, list->next->path) > 0)
				list = list->next;
			new->next = list->next;
			list->next = new;
			if (g_opt_a == 1 || new->name[0] != '.')
				nb_spaces = how_many_spaces(new, nb_spaces);
		}
	}
	list = *begin_list;
	free(begin_list);
	if (g_opt_l == 1)
	{
		ft_putstr("total ");
		ft_putnbr(nb_spaces.total);
		ft_putchar('\n');
	}
	disp_filelist(list, nb_spaces);
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
	if (disp_name == NAME && show_or_not_dir(dir_name) == 1)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	f_list = (t_filelist *)malloc_me(sizeof(t_filelist));
	f_list = readdir_and_sort_files(p_dir, dir_name);
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
