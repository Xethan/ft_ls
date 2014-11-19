/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/19 16:41:54 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

typedef struct dirent t_dirent;
typedef struct stat t_stat;

int		main(int argc, char **argv)
{
	DIR			*ptr_dir;
	t_dirent	*sdir;
	//t_stat		*sstat;
	int		i;

	i = 0;
	if (check_error_options(argv) != 1)
	{
		ft_putendl("Arguments are invalid");
		return (0);
	}
	// i = check_options(argv);
	if (argc == i + 1)
	{
		ptr_dir = opendir(".");
		while ((sdir = readdir(ptr_dir)) != NULL)
			if (sdir->d_name[0] != '.')
				ft_putendl(sdir->d_name);
		return (0);
	}
	else
	{
		//while (argv[i])
		//{
			if (check_directory_name(argv[i]) != 1)
			{
				ft_putendl("ls : No such file or directory");
			}
			else
			{
				ptr_dir = opendir(argv[i]);
				while ((sdir = readdir(ptr_dir)) != NULL)
					if (sdir->d_name[0] != '.')
						ft_putendl(sdir->d_name);
			}
		//	i++;
		//}
	}
	//sstat = (struct stat*)malloc(1 * sizeof(*sstat));
	//stat("~/git_hub/get_next_line/ft_ls/test_dir", sstat);
	//ft_ls("ft_ls");
	return (0);
}