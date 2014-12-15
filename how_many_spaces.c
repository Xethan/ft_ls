/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:21:34 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 15:49:23 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

void	put_spaces(int nb_spaces, char *info)
{
	size_t	i;

	i = 0;
	while (i != nb_spaces - ft_strlen(info))
	{
		ft_putchar(' ');
		i++;
	}
}

t_info	init_info_to_zero(t_info max)
{
	max.size = 0;
	max.nlink = 0;
	max.uid = 0;
	max.gid = 0;
	max.dev = 0;
	max.total = 0;
	return (max);
}

int		count_spaces(int info, size_t maxlength)
{
	char	*str;

	str = ft_itoa(info);
	if (ft_strlen(str) > maxlength)
		maxlength = ft_strlen(str);
	free(str);
	return (maxlength);
}

t_info	how_many_spaces(t_flist *f_list, t_info max)
{
	max.nlink = count_spaces(f_list->st->st_nlink, max.nlink);
	if (S_ISCHR(f_list->st->st_mode) || S_ISBLK(f_list->st->st_mode))
	{
		max.dev = count_spaces(major(f_list->st->st_rdev), max.dev);
		max.size = count_spaces(minor(f_list->st->st_rdev), max.size);
	}
	else
		max.size = count_spaces(f_list->st->st_size, max.size);
	if (getgrgid(f_list->st->st_gid))
	{
		if (ft_strlen(getgrgid(f_list->st->st_gid)->gr_name) > max.gid)
			max.gid = ft_strlen(getgrgid(f_list->st->st_gid)->gr_name);
	}
	else
		max.gid = count_spaces(f_list->st->st_gid, max.gid);
	if (getpwuid(f_list->st->st_uid))
	{
		if (ft_strlen(getpwuid(f_list->st->st_uid)->pw_name) > max.uid)
			max.uid = ft_strlen(getpwuid(f_list->st->st_uid)->pw_name);
	}
	else
		max.uid = count_spaces(f_list->st->st_uid, max.uid);
	max.total += f_list->st->st_blocks;
	return (max);
}
