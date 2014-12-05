/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 15:25:16 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/05 17:38:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		f_lstadd(t_filelist **begin_list, t_filelist *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

t_filelist	*f_lstnew(char *name, char *dir_name)
{
	t_filelist	*new_list;

	new_list = (t_filelist *)malloc_me(sizeof(t_filelist));
	new_list->name = (char *)malloc_me((ft_strlen(name) + 1) * sizeof(char));
	new_list->dir_name = (char *)malloc_me((ft_strlen(dir_name) + 1) * sizeof (char));
	new_list->path = get_path(dir_name, name);
	new_list->st = (t_stat *)malloc_me(sizeof(t_stat));
	if (lstat(new_list->path, new_list->st) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	if (!name || !dir_name)
		exit(EXIT_FAILURE);
	else
	{
		ft_memmove(new_list->name, name, ft_strlen(name) + 1);
		ft_memmove(new_list->dir_name, dir_name, ft_strlen(dir_name) + 1);
	}
	new_list->next = NULL;
	return (new_list);
}

void		f_lst_creat_after(t_filelist *list, char *name, char *dir_name)
{
	t_filelist	*new;

	new = f_lstnew(name, dir_name);
	new->next = list->next;
	list->next = new;
}

void		f_lstdel(t_filelist **begin_list)
{
	t_filelist	*p_list;
	t_filelist	*cpy;

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

void		f_lst_creat_begin(t_filelist **begin_list, char *name, char *dir_name)
{
	t_filelist	*new;

	new = f_lstnew(name, dir_name);
	f_lstadd(begin_list, new);
}
