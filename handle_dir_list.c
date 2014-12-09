/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/09 14:56:54 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

void		d_lstadd(t_dirlist **begin_list, t_dirlist *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

t_dirlist	*d_lstnew(char *name)
{
	t_dirlist	*new_list;

	new_list = (t_dirlist *)malloc_me(sizeof(t_dirlist));
	new_list->name = (char *)malloc_me((ft_strlen(name) + 1) * sizeof(char));
	if (name == NULL)
		new_list->name = NULL;
	else
		ft_memmove(new_list->name, name, ft_strlen(name) + 1);
	new_list->next = NULL;
	return (new_list);
}

void		d_lst_creat_after(t_dirlist *list, char *name)
{
	t_dirlist	*new;

	new = d_lstnew(name);
	new->next = list->next;
	list->next = new;
}

void		d_lstdel(t_dirlist **begin_list)
{
	t_dirlist	*p_list;
	t_dirlist	*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		free(p_list->name);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}

void		d_lst_creat_begin(t_dirlist **begin_list, char *name)
{
	t_dirlist	*new;

	new = d_lstnew(name);
	d_lstadd(begin_list, new);
}
