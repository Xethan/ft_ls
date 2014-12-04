/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/04 17:21:44 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		g_opt_r_caps = 0;
int		g_opt_a = 0;
int		g_opt_l = 0;
int		g_opt_r = 0;
int		g_opt_t = 0;

void		disp_if_needed(t_arglist *file_list, char *dir_name)
{
	t_info nb_spaces;

	nb_spaces = init_info_to_zero(nb_spaces);
	nb_spaces = how_many_spaces(file_list, dir_name, nb_spaces);
	while (file_list)
	{
		if (show_or_not_file(file_list->arg_name, dir_name) == 1)
		{
			if (g_opt_l == 1)
				do_opt_l(file_list->arg_name, dir_name, nb_spaces);
			else
				ft_putendl(file_list->arg_name);
		}
		file_list = file_list->next;
	}
}

t_arglist	*readdir_and_sort_files(DIR *p_dir, char *dir_name)
{
	t_dirent	*s_dir;
	t_arglist	**begin_list;
	t_arglist	*list;

	begin_list = (t_arglist **)malloc(sizeof(t_arglist *));
	if (begin_list == NULL)
		exit(EXIT_FAILURE);
	if ((s_dir = readdir(p_dir)) != NULL)
		*begin_list = lst_str_new(s_dir->d_name);
	while ((s_dir = readdir(p_dir)) != NULL)
	{
		list = *begin_list;
		if (cmp_args(get_path(dir_name, s_dir->d_name), get_path(dir_name, list->arg_name)) < 0)
			lst_creat_begin(begin_list, s_dir->d_name);
		else
		{
			while (list->next && cmp_args(get_path(dir_name, s_dir->d_name), get_path(dir_name, list->next->arg_name)) > 0)
				list = list->next;
			lst_creat_after(list, s_dir->d_name);
		}
	}
	list = *begin_list;
	return (list);
}

void		do_opt_r_caps(t_arglist *file_list, char *dir_name)
{
	t_stat		*p_stat;

	while (file_list)
	{
		p_stat = (t_stat *)malloc(sizeof(t_stat));
		if (lstat(get_path(dir_name, file_list->arg_name), p_stat) == -1)
		{
			perror("stat");
			return ;
		}
		if (S_ISDIR(p_stat->st_mode) != 0
			&& ft_strequ(file_list->arg_name, ".") == 0
			&& ft_strequ(file_list->arg_name, "..") == 0)
		{
			if (show_or_not_dir(get_path(dir_name, file_list->arg_name)) == 1)
				ft_putchar('\n');
			opendir_and_list(get_path(dir_name, file_list->arg_name), NAME);
		}
		file_list = file_list->next;
		free(p_stat);
	}
}

int			opendir_and_list(char *dir_name, int disp_name)
{
	DIR			*p_dir;
	t_arglist	*file_list;

	if ((p_dir = opendir(dir_name)) == NULL)
	{
		if (disp_name == NAME)
		{
			ft_putstr_fd(dir_name, 2);
			ft_putstr_fd(":\n", 2);
		}
		ft_putstr_fd("ft_ls: ", 2);
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
	file_list = (t_arglist *)malloc(sizeof(t_arglist));
	file_list = readdir_and_sort_files(p_dir, dir_name);
	disp_if_needed(file_list, dir_name);
	if (g_opt_r_caps == 1)
		do_opt_r_caps(file_list, dir_name);
	closedir(p_dir);
	return (1);
}

int			main(int argc, char **argv)
{
	int			i;
	t_arglist	*list;

	i = 1;
	if (argc > 1)
		i = check_options(argv);
	list = sort_args(argv);
	if (argc == i)
		opendir_and_list(".", NO_NAME);
	else if (argc == i + 1 && list)
			opendir_and_list(list->arg_name, NO_NAME);
	else if (argc > i + 1)
	{
		while (list)
		{
			opendir_and_list(list->arg_name, NAME);
			if ((list = list->next))
				ft_putchar('\n');
		}
	}
	//ft_lstdel(&list);
	return (0);
}
