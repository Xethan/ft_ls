/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 15:25:16 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 17:32:41 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

void	f_lstadd(t_flist **begin_list, t_flist *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

t_flist	*f_lstnew(char *name, char *folder)
{
	t_flist		*new;

	new = (t_flist *)malloc_me(sizeof(t_flist));
	new->name = (char *)malloc_me((ft_strlen(name) + 1) * sizeof(char));
	new->dir_name = (char *)malloc_me((ft_strlen(folder) + 1) * sizeof(char));
	if (folder && folder[0])
		new->path = get_path(folder, name);
	else if ((new->path = ft_strdup(name)) == NULL)
		exit(EXIT_FAILURE);
	new->st = (t_stat *)malloc_me(sizeof(t_stat));
	if (lstat(new->path, new->st) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_memmove(new->name, name, ft_strlen(name) + 1);
		if (strrchr(folder, '/'))
			folder = ft_strrchr(folder, '/') + 1;
		ft_memmove(new->dir_name, folder, ft_strlen(folder) + 1);
	}
	new->next = NULL;
	return (new);
}

void	f_lstdel(t_flist **begin_list)
{
	t_flist		*p_list;
	t_flist		*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		free(p_list->name);
		free(p_list->path);
		free(p_list->dir_name);
		free(p_list->st);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}
