/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 11:08:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 15:15:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_options	*init_options_to_zero(t_options *is_opt)
{
	is_opt->r_caps = 0;
	is_opt->a = 0;
	is_opt->l = 0;
	is_opt->r = 0;
	is_opt->t = 0;
	return (is_opt);
}

t_options	*get_options(t_options *is_opt, char c)
{
	if (c == 'R')
		is_opt->r_caps = 1;
	if (c == 'a')
		is_opt->a = 1;
	if (c == 'l')
		is_opt->l = 1;
	if (c == 'r')
		is_opt->r = 1;
	if (c == 't')
		is_opt->t = 1;
	return (is_opt);
}

int			check_options(char **arg, t_options *is_opt)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		check_error_options(arg[i]);
		while (arg[i][j])
		{
			is_opt = get_options(is_opt, arg[i][j]);
			j++;
		}
		i++;
		j = 1;
	}
	return (i);
}
