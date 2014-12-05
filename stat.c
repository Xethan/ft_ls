/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/05 15:03:31 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_l;

char	*get_path(char *dir_name, char *file_name)
{
	char	*cpy;

	dir_name = ft_strjoin(dir_name, "/");
	cpy = dir_name;
	dir_name = ft_strjoin(dir_name, file_name);
	free(cpy);
	return (dir_name);
}

void	itoa_free_space(int length, int info)
{
	char	*cpy;

	cpy = ft_itoa(info);
	put_spaces(length, cpy);
	free(cpy);
}

void	do_opt_l(char *file_name, char *dir_name, t_info nb_spaces)
{
	t_stat	*p_stat;
	char	*path;
	char	*date;

	path = get_path(dir_name, file_name);
	p_stat = (t_stat *)malloc(sizeof(t_stat));
	if (lstat(path, p_stat) == -1)
	{
		perror("stat");
		return ;
	}
	disp_type_of_file(p_stat->st_mode);
	disp_all_rights(p_stat->st_mode);
	itoa_free_space(nb_spaces.nlink, p_stat->st_nlink);
	ft_putnbr(p_stat->st_nlink);
	ft_putstr(" ");
	if (getpwuid(p_stat->st_uid))
	{
		ft_putstr(getpwuid(p_stat->st_uid)->pw_name);
		put_spaces(nb_spaces.uid, getpwuid(p_stat->st_uid)->pw_name);
	}
	else
	{
		ft_putnbr(p_stat->st_uid);
		itoa_free_space(nb_spaces.uid, p_stat->st_uid);
	}
	if (getgrgid(p_stat->st_gid))
	{
		ft_putstr(getgrgid(p_stat->st_gid)->gr_name);
		put_spaces(nb_spaces.gid - 2, getgrgid(p_stat->st_gid)->gr_name);
	}
	else
	{
		ft_putnbr(p_stat->st_gid);
		itoa_free_space(nb_spaces.gid - 2, p_stat->st_gid);
	}
	itoa_free_space(nb_spaces.size, p_stat->st_size);
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
	free(path);
	free(p_stat);
}
