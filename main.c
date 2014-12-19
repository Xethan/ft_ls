/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 11:05:44 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

int		g_opt_r_caps = 0;
int		g_opt_a = 0;
int		g_opt_l = 0;
int		g_opt_r = -1;
int		g_opt_t = 0;

t_info	into_list(t_flist **b_list, DIR *p_dir, char *dir_name, t_info spaces)
{
	t_flist		*list;
	t_flist		*new;
	t_dirent	*s_dir;

	while ((s_dir = readdir(p_dir)) != NULL)
	{
		list = *b_list;
		new = f_lstnew(s_dir->d_name, dir_name);
		if (cmp_args(new->path, list->path) < 0)
			f_lstadd(b_list, new);
		else
		{
			while (list->next && cmp_args(new->path, list->next->path) > 0)
				list = list->next;
			new->next = list->next;
			list->next = new;
		}
		if (g_opt_a == 1 || new->name[0] != '.')
			spaces = how_many_spaces(new, spaces);
	}
	return (spaces);
}

t_flist	*readdir_and_sort_files(DIR *p_dir, char *dir_name)
{
	t_dirent	*s_dir;
	t_flist		*list;
	t_info		nb_spaces;

	nb_spaces = init_info_to_zero(nb_spaces);
	if ((s_dir = readdir(p_dir)) != NULL)
	{
		list = f_lstnew(s_dir->d_name, dir_name);
		if (g_opt_a == 1 || list->name[0] != '.')
			nb_spaces = how_many_spaces(list, nb_spaces);
	}
	nb_spaces = into_list(&list, p_dir, dir_name, nb_spaces);
	if (show_or_not_files(&list))
	{
		if (g_opt_l == 1)
		{
			ft_putstr("total ");
			ft_putnbr(nb_spaces.total);
			ft_putchar('\n');
		}
		disp_filelist(list, nb_spaces);
	}
	return (list);
}

void	do_recursivity(t_flist *f_list)
{
	while (f_list)
	{
		if (S_ISDIR(f_list->st.st_mode) != 0
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

void	opendir_and_list(char *dir_name, int disp_name)
{
	DIR			*p_dir;
	t_flist		*f_list;

	if (disp_name == NAME && show_or_not_dir(dir_name) == 1)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	if ((p_dir = opendir(dir_name)) == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (strrchr(dir_name, '/'))
			perror(strrchr(dir_name, '/') + 1);
		else
			perror(dir_name);
		return ;
	}
	f_list = (t_flist *)malloc_me(sizeof(t_flist));
	f_list = readdir_and_sort_files(p_dir, dir_name);
	if (g_opt_r_caps == 1)
		do_recursivity(f_list);
	closedir(p_dir);
	f_lstdel(&f_list);
}

int		main(int argc, char **argv)
{
	int			i;
	t_dlist		*list;

	i = 1;
	if (argc > 1)
		i = check_options(argv);
	list = create_list_from_argv(argv, i - 1);
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
