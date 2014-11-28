/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 12:16:13 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/28 16:21:07 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		disp_if_needed(char *file_name, t_options *is_opt, char *dir_name, t_spaces spaces)
{
	if (file_name[0] == '.' && is_opt->a == 0)
		return ;
	if (is_opt->l == 1)
		do_opt_l(file_name, dir_name, spaces);
	else
		ft_putendl(file_name);
}

t_arglist	*readdir_and_sort_files(DIR *p_dir, t_options *is_opt)
{
	t_dirent	*s_dir;
	t_arglist	**begin_list;
	t_arglist	*list;

	begin_list = (t_arglist **)malloc(sizeof(t_arglist *));
	if ((s_dir = readdir(p_dir)) != NULL)
		*begin_list = lst_str_new(s_dir->d_name);
	while ((s_dir = readdir(p_dir)) != NULL)
	{
		list = *begin_list;
		if (ft_strcmp(s_dir->d_name, list->arg_name) < 0)
			lst_creat_begin(begin_list, s_dir->d_name);
		else
		{
			while (list->next && ft_strcmp(s_dir->d_name, list->next->arg_name) > 0)
				list = list->next;
			lst_creat_after(list, s_dir->d_name);
		}
	}
	if (is_opt->r == 1)
		list = reverse_list(begin_list);
	else
		list = *begin_list;
	return (list);
}

int			opendir_and_list(char *dir_name, t_options *is_opt, int disp_name)
{
	DIR			*p_dir;
	t_arglist	*file_list;
	t_spaces	spaces;

	// Si fichier (stat) --> disp_if_needed
	if ((p_dir = opendir(dir_name)) == NULL)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(dir_name);
		exit(EXIT_FAILURE);
	}
	if (disp_name == NAME)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	file_list = readdir_and_sort_files(p_dir, is_opt);
	spaces.size = 0;
	spaces.links = 0;
	spaces = how_many_spaces(file_list, dir_name, spaces);
	while (file_list)
	{
		disp_if_needed(file_list->arg_name, is_opt, dir_name, spaces);
		file_list = file_list->next;
	}
	/*if (is_opt->R == 1)
	{
		while(file_list)
			file_list = file_list->previous;
	}*/
	//Si -R, revenir au debut, parcourir et si dossier le lister. Condition d'arret : pas de sous-dossier (return 0)
	closedir(p_dir);
	return (1);
}

void		do_ls(int argc, char **argv, t_options *is_opt)
{
	int			i;
	t_arglist	*list;

	i = 1;
	if (argc > 1)
		i = check_options(argv, is_opt);
	list = sort_args(argv, is_opt);
	if (argc == i)
		opendir_and_list(".", is_opt, NO_NAME);
	else if (argc == i + 1)
		opendir_and_list(list->arg_name, is_opt, NO_NAME);
	else if (argc > i + 1)
	{
		while (list)
		{
			if (opendir_and_list(list->arg_name, is_opt, NAME) == 1)
				if (list->next)
					ft_putstr("\n");
			list = list->next;
		}
	}
	//ft_lstdel(&list);
}

int			main(int argc, char **argv)
{
	t_options	*is_option;

	is_option = (t_options *)malloc(sizeof(*is_option));
	is_option = init_options_to_zero(is_option);
	do_ls(argc, argv, is_option);
	free(is_option);
	return (0);
}
