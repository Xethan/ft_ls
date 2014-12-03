/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/03 12:39:48 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_r;

t_arglist	*put_arg_into_list(t_arglist **begin_list, char *arg)
{
	t_arglist	*list;
	//t_arglist	*cpy; Pas d'erreur de free avec :o !

	list = *begin_list;
	if (list == NULL)
	{
		//cpy = *begin_list;
		*begin_list = lst_str_new(arg);
		//free(cpy);
	}
	else
	{
		if (ft_strcmp(arg, list->arg_name) < 0)
			lst_creat_begin(begin_list, arg);
		else
		{
			while (list->next && ft_strcmp(arg, list->next->arg_name) > 0)
				list = list->next;
			lst_creat_after(list, arg);
		}
	}
	return (*begin_list);
}

t_arglist	*reverse_and_disp_files(t_arglist *file, t_arglist *dir)
{
	if (file)
		if (g_opt_r == 1)
			file = reverse_list(&file);
	if (dir)
		if (g_opt_r == 1)
			dir = reverse_list(&dir);
	disp_if_needed(file, "./");
	return (dir);
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
		//test malloc
		if (stat(arg[i], p_stat) == -1)
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
	dir_list = reverse_and_disp_files(file_list, dir_list);
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
