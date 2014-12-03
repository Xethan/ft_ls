/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/03 16:41:43 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		exit(EXIT_FAILURE);
	if ((new_list->arg_name = malloc(ft_strlen(arg_name) + 1)) == NULL)
		exit(EXIT_FAILURE);
	if (arg_name == NULL)
		new_list->arg_name = NULL;
	else
		ft_memmove(new_list->arg_name, arg_name, ft_strlen(arg_name) + 1);
	new_list->next = NULL;
	new_list->previous = NULL;
	return (new_list);
}

void		lst_creat_after(t_arglist *list, char *arg_name)
{
	t_arglist	*new;

	if ((new = lst_str_new(arg_name)) == NULL)
		return ;
	new->next = list->next;
	new->previous = list;
	if (list->next)
		list->next->previous = new;
	list->next = new;
}

/*void		lstdel
{

}*/

void		lst_creat_begin(t_arglist **begin_list, char *arg_name)
{
	t_arglist	*new;

	if ((new = lst_str_new(arg_name)) == NULL)
		return ;
	lst_str_add(begin_list, new);
}
