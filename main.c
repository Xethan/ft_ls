/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/29 15:50:34 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		g_opt_r_caps = 0;
int		g_opt_a = 0;
int		g_opt_l = 0;
int		g_opt_r = 0;
int		g_opt_t = 0;

void		disp_if_needed(char *file_name, char *dir_name, t_info nb_spaces)
{
	if (file_name[0] == '.' && g_opt_a == 0)
		return ;
	if (g_opt_l == 1)
		do_opt_l(file_name, dir_name, nb_spaces);
	else
		ft_putendl(file_name);
}

t_arglist	*readdir_and_sort_files(DIR *p_dir)
{
	t_dirent	*s_dir;
	t_arglist	**begin_list;
	t_arglist	*list;

	begin_list = (t_arglist **)malloc(sizeof(t_arglist *));
	if ((s_dir = readdir(p_dir)) != NULL)
		*begin_list = lst_str_new(s_dir->d_name);
	while ((s_dir = readdir(p_dir)) != NULL)
	{
		list = *begin_list;
		if (ft_strcmp(s_dir->d_name, list->arg_name) < 0)
			lst_creat_begin(begin_list, s_dir->d_name);
		else
		{
			while (list->next && ft_strcmp(s_dir->d_name, list->next->arg_name) > 0)
				list = list->next;
			lst_creat_after(list, s_dir->d_name);
		}
	}
	if (g_opt_r == 1)
		list = reverse_list(begin_list);
	else
		list = *begin_list;
	return (list);
}

int			opendir_and_list(char *dir_name, int disp_name)
{
	DIR			*p_dir;
	t_arglist	**begin_list;
	t_arglist	*file_list;
	t_info		nb_spaces;
	t_stat		*p_stat;

	if (disp_if_file(dir_name) == 1)
		return (1);
	if ((p_dir = opendir(dir_name)) == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(dir_name);
		exit(EXIT_FAILURE);
	}
	if (disp_name == NAME)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	begin_list = (t_arglist **)malloc(sizeof(t_arglist *));
	*begin_list = readdir_and_sort_files(p_dir);
	file_list = *begin_list;
	nb_spaces = init_info_to_zero(nb_spaces);
	nb_spaces = how_many_spaces(file_list, dir_name, nb_spaces);
	while (file_list)
	{
		disp_if_needed(file_list->arg_name, dir_name, nb_spaces);
		file_list = file_list->next;
	}
	if (g_opt_r_caps == 1)
	{
		file_list = *begin_list;
		while (file_list)
		{
			p_stat = (t_stat *)malloc(sizeof(t_stat));
			if (stat(get_path(file_list->arg_name, dir_name), p_stat) == -1)
			{
				perror("stat");
				exit(EXIT_FAILURE);
			}
			if ((p_stat->st_mode & 0040000) != 0
					&& ft_strequ(file_list->arg_name, ".") == 0
					&& ft_strequ(file_list->arg_name, "..") == 0)
				opendir_and_list(ft_strjoin(ft_strjoin(dir_name, "/"), file_list->arg_name), NAME);
			file_list = file_list->next;
			free(p_stat);
		}
	}
	closedir(p_dir);
	return (1);
}

void		do_ls(int argc, char **argv)
{
	int			i;
	t_arglist	*list;

	i = 1;
	if (argc > 1)
		i = check_options(argv);
	if (g_opt_r == 1)
		g_opt_r = 1;
	list = sort_args(argv);
	if (argc == i)
		opendir_and_list(".", NO_NAME);
	else if (argc == i + 1)
		opendir_and_list(list->arg_name, NO_NAME);
	else if (argc > i + 1)
	{
		while (list)
		{
			if (opendir_and_list(list->arg_name, NAME) == 1)
				if (list->next)
					ft_putstr("\n");
			list = list->next;
		}
	}
	//ft_lstdel(&list);
}

int			main(int argc, char **argv)
{
	do_ls(argc, argv);
	return (0);
}
