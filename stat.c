/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/29 15:50:49 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		disp_if_file(char *arg_name)
{
	t_stat	*p_stat;

	p_stat = (t_stat *)malloc(sizeof(t_stat));
	if (stat(arg_name, p_stat) == -1 || S_ISREG(p_stat->st_mode) == 0)
		return (0);
	ft_putendl(arg_name);
	free(p_stat);
	return (1);
}

char	*get_path(char *file_name, char *dir_name)
{
	t_stat	*p_stat;

	p_stat = (t_stat *)malloc(sizeof(t_stat));
	if (stat(dir_name, p_stat) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	dir_name = ft_strjoin(ft_strjoin(dir_name, "/"), file_name);
	free(p_stat);
	return (dir_name);
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

void	right_number_of_spaces(int nb_spaces, char *info)
{
	size_t	i;

	i = 0;
	while (i != 2 + nb_spaces - ft_strlen(info))
	{
		ft_putchar(' ');
		i++;
	}
}

void	do_opt_l(char *file_name, char *dir_name, t_info nb_spaces)
{
	t_stat	*p_stat;
	char	*date;

	p_stat = (t_stat *)malloc(sizeof(t_stat));
	if (stat(get_path(file_name, dir_name), p_stat) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	if ((p_stat->st_mode & 0100000) != 0)
		ft_putstr("-");
	else
		ft_putstr("d");
	disp_all_rights(p_stat->st_mode);
	right_number_of_spaces(nb_spaces.nlink, ft_itoa(p_stat->st_nlink));
	ft_putnbr(p_stat->st_nlink);
	ft_putstr(" ");
	ft_putstr(getpwuid(p_stat->st_uid)->pw_name);
	right_number_of_spaces(nb_spaces.uid, getpwuid(p_stat->st_uid)->pw_name);
	ft_putstr(getgrgid(p_stat->st_gid)->gr_name);
	right_number_of_spaces(nb_spaces.gid - 2, getgrgid(p_stat->st_gid)->gr_name);
	right_number_of_spaces(nb_spaces.size, ft_itoa(p_stat->st_size));
	ft_putnbr(p_stat->st_size);
	ft_putstr(" ");
	date = ctime(&(p_stat->st_mtimespec.tv_sec)) + 4;
	date[12] = '\0';
	ft_putstr(date);
	ft_putstr(" ");
	ft_putendl(file_name);
	free(p_stat);
}
