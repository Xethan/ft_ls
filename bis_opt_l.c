/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bis_opt_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 16:56:48 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/05 16:58:47 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	put_spaces(int nb_spaces, char *info)
{
	size_t	i;

	i = 0;
	while (i != 2 + nb_spaces - ft_strlen(info))
	{
		ft_putchar(' ');
		i++;
	}
}

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

void	disp_link(t_filelist *f_list)
{
	char	*link;

	link = (char *)malloc(f_list->st->st_size * sizeof(char));
	readlink(f_list->path, link, f_list->st->st_size);
	ft_putstr(" -> ");
	ft_putstr(link);
	free(link);
}
