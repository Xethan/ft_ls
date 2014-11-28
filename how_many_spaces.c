/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:21:34 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 16:18:25 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_spaces	how_many_spaces(t_arglist *file_list, char *dir_name, t_spaces spaces)
{
	struct stat	*p_stat;

	while (file_list)
	{
		p_stat = (struct stat *)malloc(sizeof(struct stat));
		if (stat(get_path(file_list->arg_name, dir_name), p_stat) == -1)
		{
			perror("ft_ls: stat");
			exit(EXIT_FAILURE);
		}
		if (ft_strlen(ft_itoa(p_stat->st_nlink)) > spaces.links)
			spaces.links = ft_strlen(ft_itoa(p_stat->st_nlink));
		if (ft_strlen(ft_itoa(p_stat->st_size)) > spaces.size)
			spaces.size = ft_strlen(ft_itoa(p_stat->st_size));
		file_list = file_list->next;
	}
	return (spaces);
}
