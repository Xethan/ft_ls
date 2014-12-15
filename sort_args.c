/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 15:19:57 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 17:39:46 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_l;

t_dlist	*arg_into_list(t_dlist **begin_list, char *arg)
{
	t_dlist		*list;

	list = *begin_list;
	if (list == NULL)
		*begin_list = d_lstnew(arg);
	else
	{
		if (cmp_args(arg, list->name) < 0)
			d_lst_creat_begin(begin_list, arg);
		else
		{
			while (list->next && cmp_args(arg, list->next->name) > 0)
				list = list->next;
			d_lst_creat_after(list, arg);
		}
	}
	return (*begin_list);
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
	t_stat		*p_stat;
	char		*dir_link;

	p_stat = (t_stat *)malloc_me(sizeof(t_stat));
	if (lstat(symlink, p_stat) == 1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	dir_link = (char *)malloc((p_stat->st_size + 1) * sizeof(char));
	readlink(symlink, dir_link, p_stat->st_size);
	dir_link[p_stat->st_size] = '\0';
	// Recuperer le path du dossier linke
	*begin_list = arg_into_list(begin_list, dir_link);
	free(dir_link);
	return (*begin_list);
}

int		is_link_fold(char *link)
{
	t_stat	*p_stat;

	p_stat = (t_stat *)malloc_me(sizeof(t_stat));
	if (stat(link, p_stat) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(p_stat->st_mode) != 0 && g_opt_l == 0)
		return (0); // 1 en vrai mais la fonction est pas prete
	free(p_stat);
	return (0);
}

t_dlist	*create_list_from_argv(char **arg, int i)
{
	t_stat		*p_stat;
	t_dlist		*dir_list;
	t_flist		*file_list;
	t_info		nb_spaces;

	file_list = NULL;
	dir_list = NULL;
	nb_spaces = init_info_to_zero(nb_spaces);
	while (arg[i])
	{
		p_stat = (t_stat *)malloc_me(sizeof(t_stat));
		if (lstat(arg[i], p_stat) == -1)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (S_ISDIR(p_stat->st_mode) != 0)
			dir_list = arg_into_list(&dir_list, arg[i]);
		else if (S_ISLNK(p_stat->st_mode) != 0 && is_link_fold(arg[i]) == 1)
			dir_list = linkdir_into_list(&dir_list, arg[i]);
		else
			nb_spaces = file_into_list(&file_list, arg[i], nb_spaces);
		i++;
		free(p_stat);
	}
	if (file_list)
		disp_filelist(file_list, nb_spaces);
	if (file_list && dir_list)
		ft_putchar('\n');
	f_lstdel(&file_list);
	return (dir_list);
}
