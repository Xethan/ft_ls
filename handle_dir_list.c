/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 15:56:18 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

void	d_lstadd(t_dlist **begin_list, t_dlist *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

t_dlist	*d_lstnew(char *name)
{
	t_dlist		*new_list;

	new_list = (t_dlist *)malloc_me(sizeof(t_dlist));
	new_list->name = (char *)malloc_me((ft_strlen(name) + 1) * sizeof(char));
	if (name == NULL)
		new_list->name = NULL;
	else
		ft_memmove(new_list->name, name, ft_strlen(name) + 1);
	new_list->next = NULL;
	return (new_list);
}

void	d_lst_creat_after(t_dlist *list, char *name)
{
	t_dlist		*new;

	new = d_lstnew(name);
	new->next = list->next;
	list->next = new;
}

void	d_lstdel(t_dlist **begin_list)
{
	t_dlist		*p_list;
	t_dlist		*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		free(p_list->name);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}

void	d_lst_creat_begin(t_dlist **begin_list, char *name)
{
	t_dlist		*new;

	new = d_lstnew(name);
	d_lstadd(begin_list, new);
}
