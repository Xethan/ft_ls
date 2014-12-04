/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/04 17:35:23 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_r;
extern int g_opt_t;

int			cmp_args(char *arg1, char *arg2)
{
	t_stat	*p_stat1;
	t_stat	*p_stat2;

	if (g_opt_t == 1)
	{
		p_stat1 = (t_stat *)malloc(sizeof(t_stat));
		p_stat2 = (t_stat *)malloc(sizeof(t_stat));
		if (lstat(arg1, p_stat1) == -1 || lstat(arg2, p_stat2) == -1)
		{
			perror("stat");
			exit(EXIT_FAILURE);
		}
		if (p_stat1->st_mtimespec.tv_sec > p_stat2->st_mtimespec.tv_sec)
		{
			free(p_stat1);
			free(p_stat2);
			return (1);
		}
		if (p_stat1->st_mtimespec.tv_sec < p_stat2->st_mtimespec.tv_sec)
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

t_arglist	*put_arg_into_list(t_arglist **begin_list, char *arg)
{
	t_arglist	*list;

	list = *begin_list;
	if (list == NULL)
		*begin_list = lst_str_new(arg);
	else
	{
		if (cmp_args(arg, list->arg_name) < 0)
			lst_creat_begin(begin_list, arg);
		else
		{
			while (list->next && cmp_args(arg, list->next->arg_name) > 0)
				list = list->next;
			lst_creat_after(list, arg);
		}
	}
	return (*begin_list);
}

t_arglist	*create_list_from_argv(char **arg, int i)
{
	t_stat		*p_stat;
	t_arglist	*dir_list;
	t_arglist	*file_list;

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
			file_list = put_arg_into_list(&file_list, arg[i]);
		i++;
		free(p_stat);
	}
	disp_if_needed(file_list, "./");
	if (file_list && dir_list)
		ft_putchar('\n');
	return (dir_list);
}

t_arglist	*sort_args(char **arg)
{
	t_arglist	*p_list;
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
