/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/08 14:39:56 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_r;
extern int g_opt_t;

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

t_dirlist	*put_arg_into_list(t_dirlist **begin_list, char *arg)
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

t_filelist	*put_file_into_list(t_filelist **begin_list, char *name)
{
	t_filelist	*list;

	list = *begin_list;
	if (list == NULL)
		*begin_list = f_lstnew(name, "./");
	else
	{
		if (cmp_args(name, list->name) < 0)
			f_lst_creat_begin(begin_list, name, "./");
		else
		{
			while (list->next && cmp_args(name, list->next->name) > 0)
				list = list->next;
			f_lst_creat_after(list, name, "./");
		}
	}
	return (*begin_list);
}

t_dirlist	*create_list_from_argv(char **arg, int i)
{
	t_stat		*p_stat;
	t_dirlist	*dir_list;
	t_filelist	*file_list;

	file_list = NULL;
	dir_list = NULL;
	while (arg[i])
	{
		p_stat = (t_stat *)malloc(sizeof(t_stat));
		if (p_stat == NULL)
			exit(EXIT_FAILURE);
		if (lstat(arg[i], p_stat) == -1)
		{
			ft_putstr_fd("./ft_ls: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (S_ISDIR(p_stat->st_mode) != 0)
			dir_list = put_arg_into_list(&dir_list, arg[i]);
		else
			file_list = put_file_into_list(&file_list, arg[i]);
		i++;
		free(p_stat);
	}
	if (file_list)
		disp_if_needed(file_list);
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
