/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 11:08:05 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/20 15:11:10 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_options	*init_options_to_zero(t_options *is_option)
{
	is_option->r_caps = 0;
	is_option->a = 0;
	is_option->l = 0;
	is_option->r = 0;
	is_option->t = 0;
	return (is_option);
}

t_options	*get_options(t_options *is_option, char c)
{
	if (c == 'R')
		is_option->r_caps = 1;
	if (c == 'a')
		is_option->a = 1;
	if (c == 'l')
		is_option->l = 1;
	if (c == 'r')
		is_option->r = 1;
	if (c == 't')
		is_option->t = 1;
	return (is_option);
}

int			check_options(char **arg, t_options *is_option)
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
			is_option = get_options(is_option, arg[i][j]);
			j++;
		}
		i++;
		j = 1;
	}
	return (i);
}
