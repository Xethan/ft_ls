/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 11:08:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 17:23:38 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_r_caps;
extern int g_opt_a;
extern int g_opt_l;
extern int g_opt_r;
extern int g_opt_t;

int		verif_dir(char *dir_name)
{
	if (ft_strequ(dir_name, ".")
		|| ft_strequ(dir_name, "./")
		|| ft_strequ(dir_name, "..")
		|| ft_strequ(dir_name, "../")
		|| dir_name[0] != '.')
		return (1);
	return (0);
}

int		show_or_not_files(t_flist **begin_list)
{
	t_flist		*f_list;
	int			verif;

	verif = 0;
	f_list = *begin_list;
	if ((g_opt_r_caps == 0 || g_opt_a == 1) && f_list)
		return (1);
	while (f_list)
	{
		if (f_list->name[0] != '.')
			verif = 1;
		f_list = f_list->next;
	}
	f_list = *begin_list;
	if (verif == 0)
		return (0);
	if (!ft_strrchr(f_list->dir_name, '/') && verif_dir(f_list->dir_name) == 0)
		return (0);
	if (ft_strrchr(f_list->dir_name, '/')
		&& *(ft_strrchr(f_list->dir_name, '/') + 1) == '.'
		&& verif_dir(ft_strrchr(f_list->dir_name, '/') + 1) == 0)
		return (0);
	return (1);
}

int		show_or_not_dir(char *dir_name)
{
	if (g_opt_a == 1 || g_opt_r_caps == 0)
		return (1);
	if (dir_name[0] != '.' && !ft_strrchr(dir_name, '/'))
		return (1);
	if (ft_strrchr(dir_name, '/') && *(ft_strrchr(dir_name, '/') + 1) != '.')
		return (1);
	return (0);
}

void	get_options(char c)
{
	if (c == 'R')
		g_opt_r_caps = 1;
	else if (c == 'a')
		g_opt_a = 1;
	else if (c == 'l')
		g_opt_l = 1;
	else if (c == 'r')
		g_opt_r = 1;
	else if (c == 't')
		g_opt_t = 1;
	else if (c != '1')
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("\nusage: ./ft_ls [-Ralrt] [file ...]\n", 2);
		exit(EXIT_FAILURE);
	}
}

int		check_options(char **arg)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		if (arg[i][1] == '-' && arg[i][2] == '\0')
			return (i + 1);
		while (arg[i][j])
		{
			get_options(arg[i][j]);
			j++;
		}
		i++;
		j = 1;
	}
	return (i);
}
