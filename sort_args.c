/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 11:21:38 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_l;

t_dlist	*arg_into_list \
	(t_dlist **b_list, char *arg, int (*comp)(const char *, const char *))
{
	t_dlist		*list;

	list = *b_list;
	if (list == NULL)
		*b_list = d_lstnew(arg);
	else
	{
		if (comp(arg, list->name) < 0)
			d_lst_creat_begin(b_list, arg);
		else
		{
			while (list->next && comp(arg, list->next->name) > 0)
				list = list->next;
			d_lst_creat_after(list, arg);
		}
	}
	return (*b_list);
}

t_info	file_into_list(t_flist **begin_list, char *name, t_info spaces)
{
	t_flist		*list;
	t_flist		*new;

	list = *begin_list;
	if (list == NULL)
	{
		*begin_list = f_lstnew(name, "");
		spaces = how_many_spaces(*begin_list, spaces);
	}
	else
	{
		new = f_lstnew(name, "");
		if (cmp_args(name, list->name) < 0)
			f_lstadd(begin_list, new);
		else
		{
			while (list->next && cmp_args(name, list->next->name) > 0)
				list = list->next;
			new->next = list->next;
			list->next = new;
		}
		spaces = how_many_spaces(new, spaces);
	}
	return (spaces);
}

t_dlist	*linkdir_into_list(t_dlist **begin_list, char *symlink)
{
	t_stat		p_stat;
	char		*dir_link;
	char		*path_link;
	char		*cpy;
	size_t		length;

	if (lstat(symlink, &p_stat) == 1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	dir_link = xreadlink(symlink, p_stat.st_size);
	if (ft_strrchr(symlink, '/'))
	{
		length = ft_strlen(symlink) - ft_strlen(ft_strrchr(symlink, '/'));
		path_link = ft_strsub(symlink, 0, length);
		cpy = dir_link;
		dir_link = get_path(path_link, dir_link);
		free(cpy);
		free(path_link);
	}
	*begin_list = arg_into_list(begin_list, dir_link, &cmp_args);
	free(dir_link);
	return (*begin_list);
}

int		is_link_fold(char *link)
{
	t_stat	p_stat;

	if (stat(link, &p_stat) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(p_stat.st_mode) != 0 && g_opt_l == 0)
		return (1);
	return (0);
}

t_dlist	*create_list_from_argv(char **arg, int i)
{
	t_stat		p_stat;
	t_dlist		*dir_list;
	t_flist		*file_list;
	t_dlist		*error_list;
	t_info		nb_spaces;

	file_list = NULL;
	dir_list = NULL;
	error_list = NULL;
	nb_spaces = init_info_to_zero(nb_spaces);
	while (arg[++i])
	{
		if (lstat(arg[i], &p_stat) == -1)
			error_list = arg_into_list(&error_list, arg[i], &ft_strcmp);
		else if (S_ISDIR(p_stat.st_mode) != 0)
			dir_list = arg_into_list(&dir_list, arg[i], &cmp_args);
		else if (S_ISLNK(p_stat.st_mode) != 0 && is_link_fold(arg[i]) == 1)
			dir_list = linkdir_into_list(&dir_list, arg[i]);
		else
			nb_spaces = file_into_list(&file_list, arg[i], nb_spaces);
	}
	disp_lists(error_list, dir_list, file_list, nb_spaces);
	return (dir_list);
}
