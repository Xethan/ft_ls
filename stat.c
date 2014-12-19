/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 15:29:47 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/19 10:49:32 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "prototype.h"

extern int g_opt_l;

void	disp_rights(mode_t rights, int test, char to_disp)
{
	if ((rights & test) != 0)
		ft_putchar(to_disp);
	else
		ft_putchar('-');
}

void	disp_x_s_t(mode_t rights, char special, int test_x, int test_special)
{
	if ((rights & test_x) != 0)
	{
		if ((rights & test_special) != 0)
			ft_putchar(special);
		else
			ft_putchar('x');
	}
	else
	{
		if ((rights & test_special) != 0)
			ft_putchar(special - 32);
		else
			ft_putchar('-');
	}
}

void	disp_all_rights(mode_t rights)
{
	disp_rights(rights, 0400, 'r');
	disp_rights(rights, 0200, 'w');
	disp_x_s_t(rights, 's', 0100, S_ISUID);
	disp_rights(rights, 040, 'r');
	disp_rights(rights, 020, 'w');
	disp_x_s_t(rights, 's', 010, S_ISGID);
	disp_rights(rights, 04, 'r');
	disp_rights(rights, 02, 'w');
	disp_x_s_t(rights, 't', 01, S_ISVTX);
}

void	do_opt_l(t_flist *f_list, t_info nb_spaces)
{
	disp_type_of_file(f_list->st.st_mode);
	disp_all_rights(f_list->st.st_mode);
	put_spaces(nb_spaces.nlink + 2, ft_nbrlen(f_list->st.st_nlink));
	ft_putnbr(f_list->st.st_nlink);
	ft_putstr(" ");
	disp_uid_gid(f_list, nb_spaces);
	disp_maj_min_size(f_list, nb_spaces);
	ft_putstr(" ");
	disp_date_name_link(f_list, nb_spaces);
}
