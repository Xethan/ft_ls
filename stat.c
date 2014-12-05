/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/05 16:58:05 by ncolliau         ###   ########.fr       */
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

void	do_opt_l(t_filelist *file, t_info nb_spaces)
{
	char	*date;

	disp_type_of_file(file->st->st_mode);
	disp_all_rights(file->st->st_mode);
	itoa_free_space(nb_spaces.nlink, file->st->st_nlink);
	ft_putnbr(file->st->st_nlink);
	ft_putstr(" ");
	if (getpwuid(file->st->st_uid))
	{
		ft_putstr(getpwuid(file->st->st_uid)->pw_name);
		put_spaces(nb_spaces.uid, getpwuid(file->st->st_uid)->pw_name);
	}
	else
	{
		ft_putnbr(file->st->st_uid);
		itoa_free_space(nb_spaces.uid, file->st->st_uid);
	}
	if (getgrgid(file->st->st_gid))
	{
		ft_putstr(getgrgid(file->st->st_gid)->gr_name);
		put_spaces(nb_spaces.gid - 2, getgrgid(file->st->st_gid)->gr_name);
	}
	else
	{
		ft_putnbr(file->st->st_gid);
		itoa_free_space(nb_spaces.gid - 2, file->st->st_gid);
	}
	itoa_free_space(nb_spaces.size, file->st->st_size);
	ft_putnbr(file->st->st_size);
	ft_putstr(" ");
	date = ctime(&(file->st->st_mtimespec.tv_sec));
	if (file->st->st_mtimespec.tv_sec < time(NULL) - 15778800 || file->st->st_mtimespec.tv_sec > time(NULL))
	{
		write(1, date + 4, 7);
		write(1, date + 19, 5);
	}
	else
		write(1, date + 4, 12);
	ft_putstr(" ");
	ft_putstr(file->name);
	if (S_ISLNK(file->st->st_mode) != 0)
		disp_link(file);
	ft_putchar('\n');
}
