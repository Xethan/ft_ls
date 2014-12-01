/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 11:08:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/01 10:55:44 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern int g_opt_r_caps;
extern int g_opt_a;
extern int g_opt_l;
extern int g_opt_r;
extern int g_opt_t;

void	get_options(char c)
{
	if (c == 'R')
		g_opt_r_caps = 1;
	if (c == 'a')
		g_opt_a = 1;
	if (c == 'l')
		g_opt_l = 1;
	if (c == 'r')
		g_opt_r = 1;
	if (c == 't')
		g_opt_t = 1;
}

int		check_options(char **arg)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		if (arg[i][1] == '-' && arg[i][2] == '\0')
			return (i + 1);
		check_error_options(arg[i]);
		while (arg[i][j])
		{
			get_options(arg[i][j]);
			j++;
		}
		i++;
		j = 1;
	}
	return (i);
}
