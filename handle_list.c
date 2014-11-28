/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 15:15:00 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		lst_str_add(t_arglist **begin_list, t_arglist *new)
{
	new->next = *begin_list;
	new->previous = NULL;
	(*begin_list)->previous = new;
	*begin_list = new;
}

t_arglist	*lst_str_new(char *arg_name)
{
	t_arglist	*new_list;

	new_list = (t_arglist *)malloc(sizeof(t_arglist));
	if (new_list == NULL)
		return (NULL);
	if ((new_list->arg_name = malloc(ft_strlen(arg_name) + 1)) == NULL)
		return (NULL);
	if (arg_name == NULL)
		new_list->arg_name = NULL;
	else
		ft_memmove(new_list->arg_name, arg_name, ft_strlen(arg_name) + 1);
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}

void		lst_creat_after(t_arglist *list, void *arg_name)
{
	t_arglist	*new;

	if ((new = lst_str_new(arg_name)) == NULL)
		return ;
	new->next = list->next;
	new->previous = list;
	list->next = new;
}

void		lst_creat_before(t_arglist *list, void *arg_name)
{
	t_arglist	*new;

	if ((new = lst_str_new(arg_name)) == NULL)
		return ;
	new->next = list;
	new->previous = list->previous;
	list->previous = new;
}

void		lst_creat_begin(t_arglist **begin_list, void *arg_name)
{
	t_arglist	*new;

	if ((new = lst_str_new(arg_name)) == NULL)
		return ;
	lst_str_add(begin_list, new);
}
