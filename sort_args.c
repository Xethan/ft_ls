/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 16:14:05 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_arglist	*reverse_list(t_arglist **begin_list)
{
	t_arglist	*new_list;
	t_arglist	*p_list;

	p_list = *begin_list;
	new_list = lst_str_new(p_list->arg_name);
	p_list = p_list->next;
	while (p_list)
	{
		lst_creat_begin(&new_list, p_list->arg_name);
		p_list = p_list->next;
	}
	//ft_lstdel(begin_list);
	return (new_list);
}

t_arglist	*put_arg_into_list(char **arg, int i)
{
	t_arglist	**begin_list;
	t_arglist	*list;

	begin_list = (t_arglist **)malloc(sizeof(t_arglist *));
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

t_arglist	*sort_args(char **arg, t_options *is_opt)
{
	t_arglist	*list;
	int			i;

	i = 1;
	while (arg[i] && arg[i][0] == '-')
		i++;
	if (!arg[i])
		return (NULL);
	list = put_arg_into_list(arg, i);
	if (is_opt->r == 1)
		list = reverse_list(&list);
	return (list);
}
