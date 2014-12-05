/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:21:34 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/05 15:06:43 by ncolliau         ###   ########.fr       */
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

t_info	how_many_spaces(t_arglist *file_list, char *dir_name, t_info length)
{
	t_stat	*p_stat;
	char	*path;
	int		total;

	total = 0;
	while (file_list)
	{
		path = get_path(dir_name, file_list->arg_name);
		p_stat = (struct stat *)malloc(sizeof(struct stat));
		if (lstat(path, p_stat) == -1)
		{
			perror("ft_ls: stat");
			return (length);
		}
		length.nlink = count_spaces(p_stat->st_nlink, length.nlink);
		length.size = count_spaces(p_stat->st_size, length.size);
		if (getgrgid(p_stat->st_gid))
		{
			if (ft_strlen(getgrgid(p_stat->st_gid)->gr_name) > length.gid)
				length.gid = ft_strlen(getgrgid(p_stat->st_gid)->gr_name);
		}
		else
			length.gid = count_spaces(p_stat->st_gid, length.gid);
		if (getpwuid(p_stat->st_uid))
		{
			if (ft_strlen(getpwuid(p_stat->st_uid)->pw_name) > length.uid)
				length.uid = ft_strlen(getpwuid(p_stat->st_uid)->pw_name);
		}
		else
			length.uid = count_spaces(p_stat->st_uid, length.uid);
		if (show_or_not_file(file_list->arg_name, dir_name) == 1)
			total += p_stat->st_blocks;
		file_list = file_list->next;
		if (!file_list && g_opt_l == 1 && show_or_not_dir(dir_name) == 1)
		{
			ft_putstr("total ");
			ft_putnbr(total);
			ft_putchar('\n');
		}
		free(path);
		free(p_stat);
	}
	return (length);
}
