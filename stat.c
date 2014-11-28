/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 15:14:56 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_path(char *file_name, char *dir_name)
{
	struct stat	*p_stat;

	p_stat = (struct stat *)malloc(sizeof(struct stat));
	if (stat(dir_name, p_stat) == -1)
	{
		perror("ft_ls: stat");
		exit(EXIT_FAILURE);
	}
	dir_name = ft_strjoin(dir_name, "/");
	dir_name = ft_strjoin(dir_name, file_name);
	file_name = dir_name;
	free(p_stat);
	return (file_name);
}

void	disp_rights(mode_t rights, int test, char to_disp)
{
	if ((rights & test) != 0)
		ft_putchar(to_disp);
	else
		ft_putchar('-');
}

void	disp_all_rights(mode_t rights)
{
	disp_rights(rights, 0400, 'r');
	disp_rights(rights, 0200, 'w');
	disp_rights(rights, 0100, 'x');
	disp_rights(rights, 040, 'r');
	disp_rights(rights, 020, 'w');
	disp_rights(rights, 010, 'x');
	disp_rights(rights, 04, 'r');
	disp_rights(rights, 02, 'w');
	disp_rights(rights, 01, 'x');
}

void	right_number_of_spaces(int max_length, int nbr)
{
	size_t	i;

	i = 0;
	while (i != 2 + max_length - ft_strlen(ft_itoa(nbr)))
	{
		ft_putchar(' ');
		i++;
	}
}

void	do_opt_l(char *file_name, char *dir_name, t_spaces spaces)
{
	struct stat		*p_stat;
	char			*date;

	p_stat = (struct stat *)malloc(sizeof(struct stat));
	if (stat(get_path(file_name, dir_name), p_stat) == -1)
	{
		perror("ft_ls: stat");
		exit(EXIT_FAILURE);
	}
	if ((p_stat->st_mode & 0100000) != 0)
		ft_putstr("-");
	else
		ft_putstr("d");
	disp_all_rights(p_stat->st_mode);
	right_number_of_spaces(spaces.links, p_stat->st_nlink);
	ft_putnbr(p_stat->st_nlink);
	ft_putstr(" ");
	ft_putstr(getpwuid(p_stat->st_uid)->pw_name);
	ft_putstr("  ");
	ft_putstr(getgrgid(p_stat->st_gid)->gr_name);
	right_number_of_spaces(spaces.size, p_stat->st_size);
	ft_putnbr(p_stat->st_size);
	ft_putstr(" ");
	date = ctime(&(p_stat->st_mtimespec.tv_sec)) + 4;
	date[12] = '\0';
	ft_putstr(date);
	ft_putstr(" ");
	ft_putendl(file_name);
	free(p_stat);
}
