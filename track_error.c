/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:03 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/19 16:10:52 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		track_options_error(char *arg)
{
	(void)arg;
	return (1);
}

int		check_directory_name(char *arg)
{
	(void)arg;
	return (1);
}

int		track_error(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (track_options_error(argv[i]) != 1)
				return (0);
		}
		else if (check_directory_name(argv[i]) != 1)
			return (0);
	}
	return (1);
}