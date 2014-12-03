/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/03 16:41:56 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_l;

int		disp_if_file(char *arg_name)
{
	t_stat	*p_stat;
	char	*date;

	p_stat = (t_stat *)malloc(sizeof(t_stat));
	if (lstat(arg_name, p_stat) == -1 || S_ISDIR(p_stat->st_mode) != 0)
		return (0);
	if (g_opt_l == 1)
	{
		disp_type_of_file(p_stat->st_mode);
		disp_all_rights(p_stat->st_mode);
		ft_putstr("  ");
		ft_putnbr(p_stat->st_nlink);
		ft_putstr(" ");
		if (getpwuid(p_stat->st_uid))
			ft_putstr(getpwuid(p_stat->st_uid)->pw_name);
		ft_putstr("  ");
		if (getgrgid(p_stat->st_gid))
			ft_putstr(getgrgid(p_stat->st_gid)->gr_name);
		ft_putstr("  ");
		ft_putnbr(p_stat->st_size);
		ft_putstr(" ");
		date = ctime(&(p_stat->st_mtimespec.tv_sec)) + 4;
		date[12] = '\0';
		ft_putstr(date);
		ft_putstr(" ");
		ft_putendl(arg_name);
	}
	else
		ft_putendl(arg_name);
	free(p_stat);
	return (1);
}

char	*get_path(char *dir_name, char *file_name)
{
	dir_name = ft_strjoin(ft_strjoin(dir_name, "/"), file_name);
	return (dir_name);
}

void	do_opt_l(char *file_name, char *dir_name, t_info nb_spaces)
{
	t_stat	*p_stat;
	char	*date;

	p_stat = (t_stat *)malloc(sizeof(t_stat));
	if (lstat(get_path(dir_name, file_name), p_stat) == -1)
	{
		perror("stat");
		return ;
	}
	disp_type_of_file(p_stat->st_mode);
	disp_all_rights(p_stat->st_mode);
	right_number_of_spaces(nb_spaces.nlink, ft_itoa(p_stat->st_nlink));
	ft_putnbr(p_stat->st_nlink);
	ft_putstr(" ");
	if (getpwuid(p_stat->st_uid))
	{
		ft_putstr(getpwuid(p_stat->st_uid)->pw_name);
		right_number_of_spaces(nb_spaces.uid, getpwuid(p_stat->st_uid)->pw_name);
	}
	else
	{
		ft_putnbr(p_stat->st_uid);
		right_number_of_spaces(nb_spaces.uid, ft_itoa(p_stat->st_uid));
	}
	if (getgrgid(p_stat->st_gid))
	{
		ft_putstr(getgrgid(p_stat->st_gid)->gr_name);
		right_number_of_spaces(nb_spaces.gid - 2, getgrgid(p_stat->st_gid)->gr_name);
	}
	else
	{
		ft_putnbr(p_stat->st_gid);
		right_number_of_spaces(nb_spaces.gid - 2, ft_itoa(p_stat->st_gid));
	}
	right_number_of_spaces(nb_spaces.size, ft_itoa(p_stat->st_size));
	ft_putnbr(p_stat->st_size);
	ft_putstr(" ");
	date = ctime(&(p_stat->st_mtimespec.tv_sec));
	if (p_stat->st_mtimespec.tv_sec < time(NULL) - 15778800 || p_stat->st_mtimespec.tv_sec > time(NULL))
	{
		write(1, date + 4, 7);
		write(1, date + 19, 5);
	}
	else
		write(1, date + 4, 12);
	ft_putstr(" ");
	ft_putstr(file_name);
	if (S_ISLNK(p_stat->st_mode) != 0)
		disp_link(file_name, dir_name);
	ft_putchar('\n');
	free(p_stat);
}
