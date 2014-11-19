/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:03 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/19 16:41:55 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_error_options(char **arg)
{
	(void)arg;
	return (1);
}

int		check_directory_name(char *arg)
{
	(void)arg;
	return (1);
}
/*
int		check_error_arguments(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (check_error_options(argv[i]) != 1)
				return (0);
		}
		else if (check_directory_name(argv[i]) != 1)
			return (0);
	}
	return (1);
}*/