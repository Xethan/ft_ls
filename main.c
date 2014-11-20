/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/20 17:38:02 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	disp_if_needed(t_dirent *sdir, t_options *is_option)
{
	if (sdir->d_name[0] == '.' && is_option->a == 0)
		return ;
	ft_putendl(sdir->d_name);
}

int		opendir_and_list(char *dir_name, t_options *is_option, int disp_name_dir)
{
	DIR			*ptr_dir;
	t_dirent	*sdir;

	if ((ptr_dir = opendir(dir_name)) == NULL)
	{
		perror("ft_ls");
		return (0);
	}
	if (disp_name_dir == DISP_NAME)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	while ((sdir = readdir(ptr_dir)) != NULL)
		disp_if_needed(sdir, is_option);
	return (1);
}

void	do_ls(int argc, char **argv, t_options *is_option)
{
	int		i;

	i = 1;
	if (argc > 1)
		i = check_options(argv, is_option);
	if (argc == i)
		opendir_and_list(".", is_option, DO_NOT_DISP_NAME);
	else if (argc == i + 1)
		opendir_and_list(argv[i], is_option, DO_NOT_DISP_NAME);
	else if (argc > i + 1)
	{
		while (argv[i])
		{
			if (opendir_and_list(argv[i], is_option, DISP_NAME) == 1 && argv[i + 1])
				ft_putchar('\n');
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
	t_options	*is_option;

	is_option = (t_options *)malloc(sizeof(*is_option));
	is_option = init_options_to_zero(is_option);
	do_ls(argc, argv, is_option);
	free(is_option);
	return (0);
}
