/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 17:45:25 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/01 17:46:23 by ncolliau         ###   ########.fr       */
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

t_arglist	*lstjoin(t_arglist *lst1, t_arglist *lst2)
{
	t_arglist	*p_list;

	p_list = lst1;
	while (p_list->next)
		p_list = p_list->next;
	p_list->next = lst2;
	p_list->next->previous = p_list;
	return (lst1);
}
