/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/24 12:32:50 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_arg_name	*move_end_lst(t_arg_name *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

t_arg_name	*put_arg_into_list(char **arg, int i)
{
	t_arg_name	**begin_list;
	t_arg_name	*list;

	begin_list = (t_arg_name **)malloc(sizeof(t_arg_name *));
	if (begin_list == NULL)
	{
		perror("./ft_ls: malloc:");
		exit(EXIT_FAILURE);
	}
	*begin_list = lst_str_new(arg[i]);
	i++;
	while (arg[i])
	{
		list = *begin_list;
		if (ft_strcmp(arg[i], list->arg_name) < 0)
			lst_creat_begin(begin_list, arg[i]);
		else
		{
			while (list->next && ft_strcmp(arg[i], list->next->arg_name) > 0)
				list = list->next;
			lst_creat_after(list, arg[i]);
		}
		//lst_creat_before(list, arg[i]);
		i++;
	}
	return (*begin_list);
}

t_arg_name	*sort_files(char **arg, t_options *is_opt)
{
	t_arg_name	*list;
	int			i;

	i = 1;
	while (arg[i] && arg[i][0] == '-')
		i++;
	if (!arg[i])
		return (NULL);
	list = put_arg_into_list(arg, i);
	if (is_opt->r == 1)
		list = move_end_lst(list);
	return (list);
}
