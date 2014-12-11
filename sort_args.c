/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/11 11:15:33 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_r;
extern int g_opt_t;
extern int g_opt_l;

int			cmp_args(char *arg1, char *arg2)
{
	t_stat	*p_stat1;
	t_stat	*p_stat2;
	time_t	tmp;

	if (g_opt_t == 1)
	{
		p_stat1 = (t_stat *)malloc(sizeof(t_stat));
		p_stat2 = (t_stat *)malloc(sizeof(t_stat));
		if (lstat(arg1, p_stat1) == -1 || lstat(arg2, p_stat2) == -1)
		{
			perror("stat");
			exit(EXIT_FAILURE);
		}
		if (g_opt_r == 1)
		{
			tmp = p_stat1->st_mtime;
			p_stat1->st_mtime = p_stat2->st_mtime;
			p_stat2->st_mtime = tmp;
		}
		if (p_stat1->st_mtime < p_stat2->st_mtime)
		{
			free(p_stat1);
			free(p_stat2);
			return (1);
		}
		if (p_stat1->st_mtime > p_stat2->st_mtime)
		{
			free(p_stat1);
			free(p_stat2);
			return (-1);
		}
		free(p_stat1);
		free(p_stat2);
	}
	if (g_opt_r == 1)
		return (-1 * ft_strcmp(arg1, arg2));
	return (ft_strcmp(arg1, arg2));
}

t_dirlist	*arg_into_list(t_dirlist **begin_list, char *arg)
{
	t_dirlist	*list;

	list = *begin_list;
	if (list == NULL)
		*begin_list = d_lstnew(arg);
	else
	{
		if (cmp_args(arg, list->name) < 0)
			d_lst_creat_begin(begin_list, arg);
		else
		{
			while (list->next && cmp_args(arg, list->next->name) > 0)
				list = list->next;
			d_lst_creat_after(list, arg);
		}
	}
	return (*begin_list);
}

t_info		file_into_list(t_filelist **begin_list, char *name, t_info spaces)
{
	t_filelist	*list;
	t_filelist	*new;

	list = *begin_list;
	if (list == NULL)
	{
		*begin_list = f_lstnew(name, "");
		spaces = how_many_spaces(*begin_list, spaces);
	}
	else
	{
		new = f_lstnew(name, "");
		if (cmp_args(name, list->name) < 0)
			f_lstadd(begin_list, new);
		else
		{
			while (list->next && cmp_args(name, list->next->name) > 0)
				list = list->next;
			new->next = list->next;
			list->next = new;
		}
		spaces = how_many_spaces(new, spaces);
	}
	return (spaces);
}

t_dirlist	*linkdir_into_list(t_dirlist **begin_list, char *symlink)
{
	t_stat		*p_stat;
	char		*dir_link;

	p_stat = (t_stat *)malloc_me(sizeof(t_stat));
	if (lstat(symlink, p_stat) == 1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	dir_link = (char *)malloc((p_stat->st_size + 1) * sizeof(char));
	readlink(symlink, dir_link, p_stat->st_size);
	dir_link[p_stat->st_size] = '\0';
	// Recuperer le path du dossier linke
	*begin_list = arg_into_list(begin_list, dir_link);
	free(dir_link);
	return (*begin_list);
}

t_dirlist	*create_list_from_argv(char **arg, int i)
{
	t_stat		*p_stat;
	t_dirlist	*dir_list;
	t_filelist	*file_list;
	t_info		nb_spaces;

	file_list = NULL;
	dir_list = NULL;
	nb_spaces = init_info_to_zero(nb_spaces);
	while (arg[i])
	{
		p_stat = (t_stat *)malloc(sizeof(t_stat));
		if (p_stat == NULL)
			exit(EXIT_FAILURE);
		if (lstat(arg[i], p_stat) == -1)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (S_ISDIR(p_stat->st_mode) != 0)
			dir_list = arg_into_list(&dir_list, arg[i]);
		else if (S_ISLNK(p_stat->st_mode) != 0) // && link un dossier
			dir_list = linkdir_into_list(&dir_list, arg[i]);
		else
			nb_spaces = file_into_list(&file_list, arg[i], nb_spaces);
		i++;
		free(p_stat);
	}
	if (file_list)
		disp_filelist(file_list, nb_spaces);
	if (file_list && dir_list)
		ft_putchar('\n');
	f_lstdel(&file_list);
	return (dir_list);
}

t_dirlist	*sort_args(char **arg)
{
	t_dirlist	*p_list;
	int			i;

	i = 1;
	while (arg[i] && arg[i][0] == '-' && arg[i][1] != '-')
		i++;
	if (arg[i] && arg[i][1] == '-')
		i++;
	if (!arg[i])
		return (NULL);
	p_list = create_list_from_argv(arg, i);
	return (p_list);
}
