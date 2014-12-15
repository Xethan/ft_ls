/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bis_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 16:56:48 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 15:59:25 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

void	disp_type_of_file(mode_t mode)
{
	if (S_ISLNK(mode) != 0)
		ft_putchar('l');
	else if (S_ISREG(mode) != 0)
		ft_putchar('-');
	else if (S_ISFIFO(mode) != 0)
		ft_putchar('p');
	else if (S_ISDIR(mode) != 0)
		ft_putchar('d');
	else if (S_ISCHR(mode) != 0)
		ft_putchar('c');
	else if (S_ISBLK(mode) != 0)
		ft_putchar('b');
	else
		ft_putchar('s');
}

void	disp_uid_gid(t_flist *file, t_info nb_spaces)
{
	if (getpwuid(file->st->st_uid))
	{
		ft_putstr(getpwuid(file->st->st_uid)->pw_name);
		put_spaces(nb_spaces.uid + 2, getpwuid(file->st->st_uid)->pw_name);
	}
	else
	{
		ft_putnbr(file->st->st_uid);
		itoa_free_space(nb_spaces.uid + 2, file->st->st_uid);
	}
	if (getgrgid(file->st->st_gid))
	{
		ft_putstr(getgrgid(file->st->st_gid)->gr_name);
		put_spaces(nb_spaces.gid, getgrgid(file->st->st_gid)->gr_name);
	}
	else
	{
		ft_putnbr(file->st->st_gid);
		itoa_free_space(nb_spaces.gid, file->st->st_gid);
	}
}

void	disp_maj_min_size(t_flist *file, t_info nb_spaces)
{
	if (nb_spaces.dev != 0)
	{
		if (S_ISCHR(file->st->st_mode) || S_ISBLK(file->st->st_mode))
		{
			itoa_free_space(5, major(file->st->st_rdev));
			ft_putnbr(major(file->st->st_rdev));
			ft_putstr(",");
			itoa_free_space(4, minor(file->st->st_rdev));
			ft_putnbr(minor(file->st->st_rdev));
		}
		else
		{
			itoa_free_space(10, file->st->st_size);
			ft_putnbr(file->st->st_size);
		}
	}
	else
	{
		itoa_free_space(nb_spaces.size + 2, file->st->st_size);
		ft_putnbr(file->st->st_size);
	}
}

void	disp_date_name_link(t_flist *file)
{
	char	*date;
	time_t	modif_time;
	char	*link;

	modif_time = file->st->st_mtime;
	date = ctime(&(modif_time));
	if (modif_time < time(NULL) - 15778800 || modif_time > time(NULL))
	{
		write(1, date + 4, 7);
		write(1, date + 19, 5);
	}
	else
		write(1, date + 4, 12);
	ft_putstr(" ");
	ft_putstr(file->name);
	if (S_ISLNK(file->st->st_mode) != 0)
	{
		link = (char *)malloc((file->st->st_size + 1) * sizeof(char));
		readlink(file->path, link, file->st->st_size);
		link[file->st->st_size] = '\0';
		ft_putstr(" -> ");
		ft_putstr(link);
		free(link);
	}
	ft_putchar('\n');
}
