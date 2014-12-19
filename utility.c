/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 17:23:08 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 11:15:48 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_t;
extern int g_opt_r;
extern int g_opt_a;
extern int g_opt_l;

char	*xreadlink(char *path, size_t bufsize)
{
	char	*link;

	link = (char *)malloc_me((bufsize + 1) * sizeof(char));
	if ((readlink(path, link, bufsize)) == -1)
	{
		perror("ft_ls: readlink:");
		exit(EXIT_FAILURE);
	}
	link[bufsize] = '\0';
	return (link);
}

void	disp_filelist(t_flist *f_list, t_info nb_spaces)
{
	while (f_list)
	{
		if (g_opt_a == 1 || f_list->name[0] != '.')
		{
			if (g_opt_l == 1)
				do_opt_l(f_list, nb_spaces);
			else
				ft_putendl(f_list->name);
		}
		f_list = f_list->next;
	}
}

void	*malloc_me(size_t size)
{
	void	*content;

	content = malloc(size);
	if (content == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (content);
}

int		cmp_args(const char *arg1, const char *arg2)
{
	t_stat	p_stat1;
	t_stat	p_stat2;

	if (g_opt_t == 1)
	{
		if (lstat(arg1, &p_stat1) == -1 || lstat(arg2, &p_stat2) == -1)
		{
			perror("stat");
			exit(EXIT_FAILURE);
		}
		if (p_stat1.st_mtime != p_stat2.st_mtime)
			return ((p_stat1.st_mtime - p_stat2.st_mtime) * g_opt_r);
	}
	if (g_opt_r == 1)
		return (-1 * ft_strcmp(arg1, arg2));
	return (ft_strcmp(arg1, arg2));
}

char	*get_path(char *dir_name, char *file_name)
{
	char	*cpy;

	dir_name = ft_strjoin(dir_name, "/");
	cpy = dir_name;
	dir_name = ft_strjoin(dir_name, file_name);
	free(cpy);
	return (dir_name);
}
