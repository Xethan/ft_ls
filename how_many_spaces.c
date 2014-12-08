/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:21:34 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/08 13:17:19 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_l;

t_info	init_info_to_zero(t_info length)
{
	length.size = 0;
	length.nlink = 0;
	length.uid = 0;
	length.gid = 0;
	return (length);
}

int		count_spaces(int info, size_t max_length)
{
	char	*str;

	str = ft_itoa(info);
	if (ft_strlen(str) > max_length)
		max_length = ft_strlen(str);
	free(str);
	return (max_length);
}

t_info	how_many_spaces(t_filelist *f_list, t_info length)
{
	int		total;
	char	*dir_name;

	total = 0;
	dir_name = f_list->dir_name;
	while (f_list)
	{
		length.nlink = count_spaces(f_list->st->st_nlink, length.nlink);
		length.size = count_spaces(f_list->st->st_size, length.size);
		if (getgrgid(f_list->st->st_gid))
		{
			if (ft_strlen(getgrgid(f_list->st->st_gid)->gr_name) > length.gid)
				length.gid = ft_strlen(getgrgid(f_list->st->st_gid)->gr_name);
		}
		else
			length.gid = count_spaces(f_list->st->st_gid, length.gid);
		if (getpwuid(f_list->st->st_uid))
		{
			if (ft_strlen(getpwuid(f_list->st->st_uid)->pw_name) > length.uid)
				length.uid = ft_strlen(getpwuid(f_list->st->st_uid)->pw_name);
		}
		else
			length.uid = count_spaces(f_list->st->st_uid, length.uid);
		if (show_or_not_file(f_list->name, dir_name) == 1)
			total += f_list->st->st_blocks;
		f_list = f_list->next;
		if (!f_list && g_opt_l == 1 && show_or_not_dir(dir_name) == 1)
		{
			ft_putstr("total ");
			ft_putnbr(total);
			ft_putchar('\n');
		}
	}
	return (length);
}
