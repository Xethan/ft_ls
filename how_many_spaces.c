/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:21:34 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/04 17:32:49 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_l;

t_info	init_info_to_zero(t_info nb_spaces)
{
	nb_spaces.size = 0;
	nb_spaces.nlink = 0;
	nb_spaces.uid = 0;
	nb_spaces.gid = 0;
	return (nb_spaces);
}

t_info	how_many_spaces(t_arglist *file_list, char *dir_name, t_info nb_spaces)
{
	struct stat	*p_stat;
	int			total;

	total = 0;
	while (file_list)
	{
		p_stat = (struct stat *)malloc(sizeof(struct stat));
		if (lstat(get_path(dir_name, file_list->arg_name), p_stat) == -1)
		{
			perror("ft_ls: stat");
			return (nb_spaces);
		}
		if (ft_strlen(ft_itoa(p_stat->st_nlink)) > nb_spaces.nlink)
			nb_spaces.nlink = ft_strlen(ft_itoa(p_stat->st_nlink));
		if (ft_strlen(ft_itoa(p_stat->st_size)) > nb_spaces.size)
			nb_spaces.size = ft_strlen(ft_itoa(p_stat->st_size));
		if (getgrgid(p_stat->st_gid))
			if (ft_strlen(getgrgid(p_stat->st_gid)->gr_name) > nb_spaces.gid)
				nb_spaces.gid = ft_strlen(getgrgid(p_stat->st_gid)->gr_name);
		if (getpwuid(p_stat->st_uid))
			if (ft_strlen(getpwuid(p_stat->st_uid)->pw_name) > nb_spaces.uid)
				nb_spaces.uid = ft_strlen(getpwuid(p_stat->st_uid)->pw_name);
		if (show_or_not_file(file_list->arg_name, dir_name) == 1)
			total += p_stat->st_blocks;
		file_list = file_list->next;
		if (!file_list && g_opt_l == 1 && show_or_not_dir(dir_name) == 1)
		{
			ft_putstr("total ");
			ft_putnbr(total);
			ft_putchar('\n');
		}
		free(p_stat);
	}
	return (nb_spaces);
}
