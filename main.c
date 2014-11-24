/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/24 12:32:49 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	disp_if_needed(t_dirent *sdir, t_options *is_opt)
{
	if (sdir->d_name[0] == '.' && is_opt->a == 0)
		return ;
	ft_putendl(sdir->d_name);
}

int		opendir_and_list(char *dir_name, t_options *is_opt, int disp_name)
{
	DIR			*ptr_dir;
	t_dirent	*sdir;

	if ((ptr_dir = opendir(dir_name)) == NULL)
	{
		ft_putstr("ft_ls: ");
		perror(dir_name);
		return (0);
	}
	if (disp_name == NAME)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	while ((sdir = readdir(ptr_dir)) != NULL)
		disp_if_needed(sdir, is_opt);
	return (1);
}

void	do_ls(int argc, char **argv, t_options *is_opt)
{
	int			i;
	t_arg_name	*list;

	i = 1;
	if (argc > 1)
		i = check_options(argv, is_opt);
	list = sort_files(argv, is_opt);
	if (argc == i)
		opendir_and_list(".", is_opt, NO_NAME);
	else if (argc == i + 1)
		opendir_and_list(list->arg_name, is_opt, NO_NAME);
	else if (argc > i + 1)
	{
		while (list)
		{
			if (opendir_and_list(list->arg_name, is_opt, NAME) == 1 \
				&& ((list->next && is_opt->r == 0) \
				|| (list->previous && is_opt->r == 1)))
				ft_putchar('\n');
			if (is_opt->r == 1)
				list = list->previous;
			else
				list = list->next;
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
