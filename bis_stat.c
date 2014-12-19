/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bis_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 16:56:48 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 10:44:37 by ncolliau         ###   ########.fr       */
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
	char	*id;

	if (getpwuid(file->st.st_uid))
	{
		id = getpwuid(file->st.st_uid)->pw_name;
		ft_putstr(id);
		put_spaces(nb_spaces.uid + 2, ft_strlen(id));
	}
	else
	{
		ft_putnbr(file->st.st_uid);
		put_spaces(nb_spaces.uid + 2, ft_nbrlen(file->st.st_uid));
	}
	if (getgrgid(file->st.st_gid))
	{
		id = getgrgid(file->st.st_gid)->gr_name;
		ft_putstr(id);
		put_spaces(nb_spaces.gid, ft_strlen(id));
	}
	else
	{
		ft_putnbr(file->st.st_gid);
		put_spaces(nb_spaces.gid, ft_nbrlen(file->st.st_gid));
	}
}

void	disp_maj_min_size(t_flist *file, t_info nb_spaces)
{
	if (nb_spaces.dev != 0)
	{
		if (S_ISCHR(file->st.st_mode) || S_ISBLK(file->st.st_mode))
		{
			put_spaces(5, ft_nbrlen(major(file->st.st_rdev)));
			ft_putnbr(major(file->st.st_rdev));
			ft_putstr(",");
			put_spaces(4, ft_nbrlen(minor(file->st.st_rdev)));
			ft_putnbr(minor(file->st.st_rdev));
		}
		else
		{
			put_spaces(10, ft_nbrlen(file->st.st_size));
			ft_putlonglong(file->st.st_size);
		}
	}
	else
	{
		put_spaces(nb_spaces.size + 2, ft_nbrlen(file->st.st_size));
		ft_putlonglong(file->st.st_size);
	}
}

void	disp_date_name_link(t_flist *file, t_info nb_spaces)
{
	char	*date;
	time_t	modif_time;
	char	*link;

	modif_time = file->st.st_mtime;
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
	if (S_ISLNK(file->st.st_mode) != 0)
	{
		if (nb_spaces.dev != 0)
			file->st.st_size = 4;
		link = xreadlink(file->path, file->st.st_size);
		ft_putstr(" -> ");
		ft_putstr(link);
		free(link);
	}
	ft_putchar('\n');
}
