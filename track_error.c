/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:03 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/21 16:48:05 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_option(char c)
{
	if (c == 'l' || c == 'a' || c == 'r' || c == 't' || c == 'R')
		return (1);
	return (0);
}

int		check_error_options(char *arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (is_option(arg[i]) == 0)
		{
			ft_putstr("ft_ls: illegal option --");
			ft_putchar(arg[i]);
			ft_putstr("\nusage: ./ft_ls [-Ralrt] [file ...]");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (1);
}
