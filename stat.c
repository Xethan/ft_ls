/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/15 17:24:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_l;

void	itoa_free_space(int length, int info)
{
	char	*cpy;

	cpy = ft_itoa(info);
	put_spaces(length, cpy);
	free(cpy);
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

void	do_opt_l(t_flist *file, t_info nb_spaces)
{
	disp_type_of_file(file->st->st_mode);
	disp_all_rights(file->st->st_mode);
	itoa_free_space(nb_spaces.nlink + 2, file->st->st_nlink);
	ft_putnbr(file->st->st_nlink);
	ft_putstr(" ");
	disp_uid_gid(file, nb_spaces);
	disp_maj_min_size(file, nb_spaces);
	ft_putstr(" ");
	disp_date_name_link(file);
}
